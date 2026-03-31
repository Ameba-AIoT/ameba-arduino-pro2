#include "sim_io.h"

#define SUPPORT_FAST_LZ

#ifdef FOR_FREERTOS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef SUPPORT_FAST_LZ
#include <fastlz/fastlz.h>
#endif

#include "svm_model.h"

#define align4(n)   (((n+3)>>2)<<2)

typedef struct mem_t_ {
	const char *path;
	const uint8_t *data;
	uint32_t size;
} mem_t;

mem_t mem_item[] = {
#ifdef SUPPORT_FAST_LZ
	{"svm_model", svm_model_l16_lz, sizeof(svm_model_l16_lz)},

#else
	{"svm_model", svm_model_v1, sizeof(svm_model_v1)},
#endif
	{0, 0, 0}
};

void read32(const uint8_t **p, const uint32_t *size)
{
	memcpy((void *)size, (void *)*p, 4);
	*p += sizeof(uint32_t);
}

void mseek(const uint8_t **p, uint32_t size)
{
	*p += size;
}

typedef struct sim_file_s {
	uint8_t *data;
	uint32_t datalen;
	uint32_t cursor;
} sim_file_t;

static void mem_open(const char *path, sim_file_t *t)
{
	memset(t, 0, sizeof(sim_file_t));
	mem_t *item = mem_item;
	for (;;) {
		if (item->path == 0) {
			break;
		}

		if (strcmp(path, item->path) == 0) {
			t->data = (uint8_t *)item->data;
			t->datalen = (uint32_t)item->size;
			return;
		}
		item++;
	}
}

SIM_FILE *sim_fopen(const char *path, const char *mode)
{
	sim_file_t *t = malloc(sizeof(sim_file_t));
	memset(t, 0, sizeof(sim_file_t));
	if (mode[0] == 'r') {
		mem_open(path, t);
		if (t->data != 0) {
#ifdef SUPPORT_FAST_LZ
			uint32_t outlen;
			//printf("path=%s, origin %p\n", path, t->data);
			read32((const uint8_t **)&t->data, &outlen);
			//printf("outlen:%lu\r\n", outlen);
			uint8_t *in = t->data;
			uint32_t inlen = t->datalen - sizeof(uint32_t);
			uint8_t *out = (uint8_t *)malloc(outlen);
			t->datalen = fastlz_decompress(in, inlen, out, outlen);
			if (t->datalen != outlen) {
				printf("decompress lz data filaed. %ld %ld\r\n", t->datalen, outlen);
				t->data = NULL;
				t->datalen = 0;
			} else {
				t->data = out;
			}
#endif
			return t;
		}
	} else {
		// write, just return dummy
		return t;
	}
	return NULL;
}

long sim_ftell(SIM_FILE *t)
{
	return t->cursor;
}

int sim_fclose(SIM_FILE *t)
{
	if (t) {
#ifdef SUPPORT_FAST_LZ
		free(t->data);
#endif
		free(t);
	}
	return 0;
}

size_t sim_fread(void *ptr, size_t size, size_t nitems, SIM_FILE *t)
{
	size_t s = size * nitems;
	if (s + t->cursor >= t->datalen) {
		s = t->datalen - t->cursor;
	}
	memcpy(ptr, &t->data[t->cursor], s);
	t->cursor += s;

	return s;
}

size_t sim_fwrite(void *ptr, size_t size, size_t nitems, SIM_FILE *t)
{
	return -1; // error
}

int sim_ferror(SIM_FILE *stream)
{
	return 0;
}

int sim_getc(SIM_FILE *t)
{
	return (t->cursor < t->datalen) ? (int) t->data[t->cursor++] : EOF;
}

int sim_fgetc(SIM_FILE *t)
{
	return sim_getc(t);
}

char *sim_fgets(char *str, int size, SIM_FILE *t)
{
	int ch;
	char *p = str;

	while ((ch = sim_getc(t)) != '\n' && ch != EOF) {
		*str++ = (char) ch;
	}

	if (ch == '\n') {
		*str++ = (char) '\n';
	} else if (ch == EOF) {
		if (p == str) {
			return NULL;
		} else {
			*str++ = (char) '\n';
		}
	}

	*str = '\0'; // terminate
	return p;
}

static char *sim_fgets_v2(char *str, int size, SIM_FILE *t)
{
	int ch;
	char *p = str;

	while ((ch = sim_getc(t)) != '\n' && ch != ' ' && ch != EOF) {
		*str++ = (char) ch;
	}

	*str = '\0'; // terminate
	return p;
}

int sim_fscanf(SIM_FILE *t, const char *format, ...)
{
	char buf[256];

	sim_fgets_v2(buf, sizeof(buf), t);
	va_list args;
	va_start(args, format);
	int rc = vsscanf(buf, format, args);
	va_end(args);
	return rc;
}

int sim_fprintf(SIM_FILE *t, const char *format, ...)
{
	return 0;
}

int sim_feof(SIM_FILE *t)
{
	return (t->data && (t->cursor < t->datalen)) ? 0 : 1;
}

int sim_fseek(SIM_FILE *t, long offset, int whence)
{
	switch (whence) {
	case SEEK_SET:
		t->cursor = offset;
		break;
	case SEEK_CUR:
		t->cursor += offset;
		break;
	case SEEK_END:
		t->cursor = t->datalen - offset;
		break;
	}

	if (t->cursor >= t->datalen) {
		t->cursor = t->datalen;
	}

	return t->cursor;
}

#endif
