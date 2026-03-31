/******************************************************************************
*
* Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>

#include "mmf2_module.h"
#include "module_httpfs.h"
#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <httpd/httpd.h>
#include "fatfs_sdcard_api.h"
#include <wifi_conf.h>
#include "lwip_netconf.h"

//SET FAST_MP4 and FAST_MP4_WITHOUT_FILE to 0 if you want to use snapshot with httpfs
#define FAST_MP4    1
#define FAST_MP4_WITHOUT_FILE 1

#if FAST_MP4
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BE_16(x) ((((uint8_t*)(x))[0] << 8) | ((uint8_t*)(x))[1])
#define BE_32(x) ((((uint8_t*)(x))[0] << 24) | \
		(((uint8_t*)(x))[1] << 16) | \
		(((uint8_t*)(x))[2] << 8) | \
		((uint8_t*)(x))[3])
#define BE_64(x) (((uint64_t)(((uint8_t*)(x))[0]) << 56) | \
		((uint64_t)(((uint8_t*)(x))[1]) << 48) | \
		((uint64_t)(((uint8_t*)(x))[2]) << 40) | \
		((uint64_t)(((uint8_t*)(x))[3]) << 32) | \
		((uint64_t)(((uint8_t*)(x))[4]) << 24) | \
		((uint64_t)(((uint8_t*)(x))[5]) << 16) | \
		((uint64_t)(((uint8_t*)(x))[6]) << 8) | \
		((uint64_t)((uint8_t*)(x))[7]))

#define BE_FOURCC( ch0, ch1, ch2, ch3 )             \
	( (uint32_t)(unsigned char)(ch3) |          \
	  ( (uint32_t)(unsigned char)(ch2) << 8 ) |   \
	  ( (uint32_t)(unsigned char)(ch1) << 16 ) |  \
	  ( (uint32_t)(unsigned char)(ch0) << 24 ) )

#define QT_ATOM BE_FOURCC
/* top level atoms */
#define FREE_ATOM QT_ATOM('f', 'r', 'e', 'e')
#define JUNK_ATOM QT_ATOM('j', 'u', 'n', 'k')
#define MDAT_ATOM QT_ATOM('m', 'd', 'a', 't')
#define MOOV_ATOM QT_ATOM('m', 'o', 'o', 'v')
#define PNOT_ATOM QT_ATOM('p', 'n', 'o', 't')
#define SKIP_ATOM QT_ATOM('s', 'k', 'i', 'p')
#define WIDE_ATOM QT_ATOM('w', 'i', 'd', 'e')
#define PICT_ATOM QT_ATOM('P', 'I', 'C', 'T')
#define FTYP_ATOM QT_ATOM('f', 't', 'y', 'p')

#define CMOV_ATOM QT_ATOM('c', 'm', 'o', 'v')
#define STCO_ATOM QT_ATOM('s', 't', 'c', 'o')
#define CO64_ATOM QT_ATOM('c', 'o', '6', '4')

#define ATOM_PREAMBLE_SIZE 8

/*
 * qt_faststart
 * src_path source mp4 path
 * dest_path dest mp4 path
 *  return 0 success -1 failed
*/
FIL     infile;
FIL     outfile;
unsigned char atom_bytes[ATOM_PREAMBLE_SIZE];

#if FAST_MP4_WITHOUT_FILE
int qt_faststart(char *src_path,
				 uint32_t *ftyp_size,
				 uint32_t *ftyp_buffer,
				 uint32_t *moov_size,
				 uint32_t *moov_buffer,
				 uint32_t *src_start_offset,
				 uint32_t *src_last_offset)
{
	FRESULT res;
	uint32_t atom_type = 0;
	uint32_t atom_size = 0;
	uint32_t last_offset;
	unsigned char *moov_atom;
	unsigned char *ftyp_atom = 0;
	uint32_t moov_atom_size;
	uint32_t ftyp_atom_size = 0;
	uint32_t i, j;
	uint32_t offset_count;
	uint32_t current_offset;
	uint32_t start_offset = 0;
	u32 br = 0;
	int len = 0;

	if (!src_path) {
		printf("src mp4 path is NULL\n");
		return -1;
	}

	res = f_open(&infile, src_path, FA_OPEN_ALWAYS | FA_READ);
	if (res) {
		printf("open file (%s) fail.\n", src_path);
		return -1;
	}

	/* traverse through the atoms in the file to make sure that 'moov' is
	 * at the end */
	while (!f_eof(&infile)) {
		res = f_read(&infile, atom_bytes, ATOM_PREAMBLE_SIZE, (u32 *)&br);
		if (res || f_eof(&infile)) {
			break;
		}

		atom_size = (uint32_t)BE_32(&atom_bytes[0]);
		printf("atom_size = %d\r\n", atom_size);
		atom_type = BE_32(&atom_bytes[4]);
		printf("atom_type = 0x%X\r\n", atom_type);

		if ((atom_type != FREE_ATOM) &&
			(atom_type != JUNK_ATOM) &&
			(atom_type != MDAT_ATOM) &&
			(atom_type != MOOV_ATOM) &&
			(atom_type != PNOT_ATOM) &&
			(atom_type != SKIP_ATOM) &&
			(atom_type != WIDE_ATOM) &&
			(atom_type != PICT_ATOM) &&
			(atom_type != FTYP_ATOM)) {

			printf("encountered non-QT top-level atom (is this a Quicktime file?)\n");
			break;
		}

		/* keep ftyp atom */
		if (atom_type == FTYP_ATOM) {
			ftyp_atom_size = atom_size;
			*ftyp_size = ftyp_atom_size;
			ftyp_atom = malloc(ftyp_atom_size);
			*ftyp_buffer = (uint32_t)ftyp_atom;
			if (!ftyp_atom) {

				printf("could not allocate 0x%llX byte for ftyp atom\n", atom_size);
				f_close(&infile);
				return -1;

			}

			len = f_tell(&infile);
			f_lseek(&infile, len - ATOM_PREAMBLE_SIZE);
			res = f_read(&infile, ftyp_atom, atom_size, (u32 *)&br);
			if (res || f_eof(&infile)) {
				free(ftyp_atom);
				f_close(&infile);
				return -1;
			}

			start_offset = f_tell(&infile);
			*src_start_offset = start_offset;
			printf("start_offset = %d\r\n", start_offset);
			continue;
		}

		/* 64-bit special case */
#if 0
		if (atom_size == 1) {
			res = f_read(&infile, atom_bytes, ATOM_PREAMBLE_SIZE, (u32 *)&br);
			if (res || f_eof(&infile)) {
				break;
			}

			atom_size = BE_64(&atom_bytes[0]);
			len = f_tell(&infile);
			f_lseek(&infile, len + atom_size - ATOM_PREAMBLE_SIZE * 2);
		} else
#endif
		{
			len = f_tell(&infile);
			f_lseek(&infile, len + atom_size - ATOM_PREAMBLE_SIZE);
			if (atom_type == MOOV_ATOM) {
				break;
			}
		}

	}

	if (atom_type != MOOV_ATOM) {
		printf("last atom in file was not a moov atom\n");
		f_close(&infile);
		return -1;
	}

	/* moov atom was, in fact, the last atom in the chunk; load the whole
	 * moov atom */
	len = f_tell(&infile);
	f_lseek(&infile, len - atom_size);
	last_offset = f_tell(&infile);
	moov_atom_size = atom_size;
	*moov_size = moov_atom_size;
	moov_atom = malloc(moov_atom_size);
	*moov_buffer = (uint32_t)moov_atom;

	if (!moov_atom) {
		printf("could not allocate 0x%llX byte for moov atom\n", atom_size);
		f_close(&infile);
		return -1;
	}

	res = f_read(&infile, moov_atom, atom_size, (u32 *)&br);
	if (res) {
		printf("moov_atom read fail!\r\n");
		free(moov_atom);
		f_close(&infile);
		return -1;
	}

	/* this utility does not support compressed atoms yet, so disqualify
	 * files with compressed QT atoms */
	if (BE_32(&moov_atom[12]) == CMOV_ATOM) {
		printf("this utility does not support compressed moov atoms yet\n");
		free(moov_atom);
		f_close(&infile);
		return -1;
	}

	/* close; will be re-opened later */
	f_close(&infile);

	/* crawl through the moov chunk in search of stco or co64 atoms */
	for (i = 4; i < moov_atom_size - 4; i++) {
		atom_type = BE_32(&moov_atom[i]);
		if (atom_type == STCO_ATOM) {
			printf(" patching stco atom...\n");
			atom_size = BE_32(&moov_atom[i - 4]);
			if (i + atom_size - 4 > moov_atom_size) {
				printf(" bad atom size\n");
				free(moov_atom);
				return -1;
			}
			offset_count = BE_32(&moov_atom[i + 8]);
			for (j = 0; j < offset_count; j++) {

				current_offset = BE_32(&moov_atom[i + 12 + j * 4]);
				current_offset += moov_atom_size;
				moov_atom[i + 12 + j * 4 + 0] = (current_offset >> 24) & 0xFF;
				moov_atom[i + 12 + j * 4 + 1] = (current_offset >> 16) & 0xFF;
				moov_atom[i + 12 + j * 4 + 2] = (current_offset >>  8) & 0xFF;
				moov_atom[i + 12 + j * 4 + 3] = (current_offset >>  0) & 0xFF;

			}
			i += atom_size - 4;

		} else if (atom_type == CO64_ATOM) {
			printf(" patching co64 atom...\n");
			atom_size = BE_32(&moov_atom[i - 4]);
			if (i + atom_size - 4 > moov_atom_size) {
				printf(" bad atom size\n");
				free(moov_atom);
				return -1;
			}
			offset_count = BE_32(&moov_atom[i + 8]);
			for (j = 0; j < offset_count; j++) {
				uint64_t current_offset = BE_64(&moov_atom[i + 12 + j * 8]);
				current_offset += moov_atom_size;
				moov_atom[i + 12 + j * 8 + 0] = (current_offset >> 56) & 0xFF;
				moov_atom[i + 12 + j * 8 + 1] = (current_offset >> 48) & 0xFF;
				moov_atom[i + 12 + j * 8 + 2] = (current_offset >> 40) & 0xFF;
				moov_atom[i + 12 + j * 8 + 3] = (current_offset >> 32) & 0xFF;
				moov_atom[i + 12 + j * 8 + 4] = (current_offset >> 24) & 0xFF;
				moov_atom[i + 12 + j * 8 + 5] = (current_offset >> 16) & 0xFF;
				moov_atom[i + 12 + j * 8 + 6] = (current_offset >>  8) & 0xFF;
				moov_atom[i + 12 + j * 8 + 7] = (current_offset >>  0) & 0xFF;
			}
			i += atom_size - 4;
		}
	}


	if (start_offset > 0) {
		last_offset -= start_offset;
		*src_last_offset = last_offset;
	}

	return 0;
}

#else

#define COPY_BUFFER_SIZE 1024
unsigned char copy_buffer[COPY_BUFFER_SIZE]__attribute__((aligned(32)));

int qt_faststart(char *src_path, char *dest_path)
{
	FRESULT res;
	uint32_t atom_type = 0;
	uint32_t atom_size = 0;
	uint32_t last_offset;
	unsigned char *moov_atom;
	unsigned char *ftyp_atom = 0;
	uint32_t moov_atom_size;
	uint32_t ftyp_atom_size = 0;
	uint32_t i, j;
	uint32_t offset_count;
	uint32_t current_offset;
	uint32_t start_offset = 0;
	int bytes_to_copy;
	u32 br = 0;
	u32 bw = 0;
	int len = 0;

	if (!src_path) {
		printf("src mp4 path is NULL\n");
		return -1;
	}

	if (!dest_path) {
		printf("dest mp4 path is NULL\n");
		return -1;
	}

	res = f_open(&infile, src_path, FA_OPEN_ALWAYS | FA_READ);
	if (res) {
		printf("open file (%s) fail.\n", src_path);
		return -1;
	}

	/* traverse through the atoms in the file to make sure that 'moov' is
	 * at the end */
	while (!f_eof(&infile)) {
		res = f_read(&infile, atom_bytes, ATOM_PREAMBLE_SIZE, (u32 *)&br);
		if (res || f_eof(&infile)) {
			break;
		}

		atom_size = (uint32_t)BE_32(&atom_bytes[0]);
		printf("atom_size = %d\r\n", atom_size);
		atom_type = BE_32(&atom_bytes[4]);
		printf("atom_type = 0x%X\r\n", atom_type);

		if ((atom_type != FREE_ATOM) &&
			(atom_type != JUNK_ATOM) &&
			(atom_type != MDAT_ATOM) &&
			(atom_type != MOOV_ATOM) &&
			(atom_type != PNOT_ATOM) &&
			(atom_type != SKIP_ATOM) &&
			(atom_type != WIDE_ATOM) &&
			(atom_type != PICT_ATOM) &&
			(atom_type != FTYP_ATOM)) {

			printf("encountered non-QT top-level atom (is this a Quicktime file?)\n");
			break;
		}

		/* keep ftyp atom */
		if (atom_type == FTYP_ATOM) {

			ftyp_atom_size = atom_size;
			ftyp_atom = malloc(ftyp_atom_size);
			if (!ftyp_atom) {
				printf("could not allocate 0x%llX byte for ftyp atom\n", atom_size);
				f_close(&infile);
				return -1;
			}

			len = f_tell(&infile);
			f_lseek(&infile, len - ATOM_PREAMBLE_SIZE);
			res = f_read(&infile, ftyp_atom, atom_size, (u32 *)&br);
			if (res || f_eof(&infile)) {
				free(ftyp_atom);
				f_close(&infile);
				return -1;
			}

			start_offset = f_tell(&infile);
			printf("start_offset = %d\r\n", start_offset);
			continue;
		}

		/* 64-bit special case */
#if 0
		if (atom_size == 1) {
			res = f_read(&infile, atom_bytes, ATOM_PREAMBLE_SIZE, (u32 *)&br);
			if (res || f_eof(&infile)) {
				break;
			}

			atom_size = BE_64(&atom_bytes[0]);
			len = f_tell(&infile);
			f_lseek(&infile, len + atom_size - ATOM_PREAMBLE_SIZE * 2);

		} else
#endif
		{
			len = f_tell(&infile);
			f_lseek(&infile, len + atom_size - ATOM_PREAMBLE_SIZE);
			if (atom_type == MOOV_ATOM) {

				break;
			}
		}

	}

	if (atom_type != MOOV_ATOM) {
		printf("last atom in file was not a moov atom\n");
		f_close(&infile);
		return -1;
	}

	/* moov atom was, in fact, the last atom in the chunk; load the whole
	 * moov atom */
	len = f_tell(&infile);
	f_lseek(&infile, len - atom_size);
	last_offset = f_tell(&infile);
	moov_atom_size = atom_size;
	moov_atom = malloc(moov_atom_size);

	if (!moov_atom) {
		printf("could not allocate 0x%llX byte for moov atom\n", atom_size);
		f_close(&infile);
		return -1;
	}

	res = f_read(&infile, moov_atom, atom_size, (u32 *)&br);
	if (res) {
		printf("moov_atom read fail!\r\n");
		free(moov_atom);
		f_close(&infile);
		return -1;
	}

	/* this utility does not support compressed atoms yet, so disqualify
	 * files with compressed QT atoms */
	if (BE_32(&moov_atom[12]) == CMOV_ATOM) {
		printf("this utility does not support compressed moov atoms yet\n");
		free(moov_atom);
		f_close(&infile);
		return -1;
	}

	/* close; will be re-opened later */
	f_close(&infile);

	/* crawl through the moov chunk in search of stco or co64 atoms */
	for (i = 4; i < moov_atom_size - 4; i++) {
		atom_type = BE_32(&moov_atom[i]);
		if (atom_type == STCO_ATOM) {
			printf(" patching stco atom...\n");
			atom_size = BE_32(&moov_atom[i - 4]);
			if (i + atom_size - 4 > moov_atom_size) {
				printf(" bad atom size\n");
				free(moov_atom);
				return -1;
			}
			offset_count = BE_32(&moov_atom[i + 8]);
			for (j = 0; j < offset_count; j++) {
				current_offset = BE_32(&moov_atom[i + 12 + j * 4]);
				current_offset += moov_atom_size;
				moov_atom[i + 12 + j * 4 + 0] = (current_offset >> 24) & 0xFF;
				moov_atom[i + 12 + j * 4 + 1] = (current_offset >> 16) & 0xFF;
				moov_atom[i + 12 + j * 4 + 2] = (current_offset >>  8) & 0xFF;
				moov_atom[i + 12 + j * 4 + 3] = (current_offset >>  0) & 0xFF;
			}
			i += atom_size - 4;

		} else if (atom_type == CO64_ATOM) {
			printf(" patching co64 atom...\n");
			atom_size = BE_32(&moov_atom[i - 4]);
			if (i + atom_size - 4 > moov_atom_size) {
				printf(" bad atom size\n");
				free(moov_atom);
				return -1;
			}
			offset_count = BE_32(&moov_atom[i + 8]);
			for (j = 0; j < offset_count; j++) {
				current_offset = BE_64(&moov_atom[i + 12 + j * 8]);
				current_offset += moov_atom_size;
				moov_atom[i + 12 + j * 8 + 0] = (current_offset >> 56) & 0xFF;
				moov_atom[i + 12 + j * 8 + 1] = (current_offset >> 48) & 0xFF;
				moov_atom[i + 12 + j * 8 + 2] = (current_offset >> 40) & 0xFF;
				moov_atom[i + 12 + j * 8 + 3] = (current_offset >> 32) & 0xFF;
				moov_atom[i + 12 + j * 8 + 4] = (current_offset >> 24) & 0xFF;
				moov_atom[i + 12 + j * 8 + 5] = (current_offset >> 16) & 0xFF;
				moov_atom[i + 12 + j * 8 + 6] = (current_offset >>  8) & 0xFF;
				moov_atom[i + 12 + j * 8 + 7] = (current_offset >>  0) & 0xFF;
			}
			i += atom_size - 4;
		}
	}

	/* re-open the input file and open the output file */
	res = f_open(&infile, src_path, FA_OPEN_ALWAYS | FA_READ);
	if (res) {
		printf("open file (%s) fail.\n", src_path);
		free(moov_atom);
		return -1;
	}

	if (start_offset > 0) {
		/* seek after ftyp atom */
		f_lseek(&infile, start_offset);
		last_offset -= start_offset;
	}

	res = f_open(&outfile, dest_path, FA_OPEN_ALWAYS | FA_WRITE);
	if (res) {
		printf("open file (%s) fail.\n", dest_path);
		f_close(&outfile);
		free(moov_atom);
		return -1;
	}

	/* dump the same ftyp atom */
	if (ftyp_atom_size > 0) {
		printf(" writing ftyp atom...\n");
		res = f_write(&outfile, ftyp_atom, ftyp_atom_size, (u32 *)&bw);
		if (res) {
			goto error_out;
		}
	}

	/* dump the new moov atom */
	printf(" writing moov atom...\n");
	res = f_write(&outfile, moov_atom, moov_atom_size, (u32 *)&bw);
	if (res) {
		goto error_out;
	}

	/* copy the remainder of the infile, from offset 0 -> last_offset - 1 */
	printf(" copying rest of file...\n");
	while (last_offset) {
		if (last_offset > COPY_BUFFER_SIZE) {
			bytes_to_copy = COPY_BUFFER_SIZE;
		} else {
			bytes_to_copy = last_offset;
		}

		res = f_read(&infile, copy_buffer, bytes_to_copy, (u32 *)&br);
		if (res || f_eof(&infile)) {
			goto error_out;
		}

		res = f_write(&outfile, copy_buffer, bytes_to_copy, (u32 *)&bw);
		if (res) {
			goto error_out;
		}

		last_offset -= bytes_to_copy;
	}

	f_close(&infile);
	f_close(&outfile);
	free(moov_atom);
	if (ftyp_atom_size > 0) {
		free(ftyp_atom);
	}

	return 0;

error_out:
	f_close(&infile);
	f_close(&outfile);
	free(moov_atom);
	if (ftyp_atom_size > 0) {
		free(ftyp_atom);
	}
	return -1;
}

#endif
#endif

//------------------------------------------------------------------------------
FIL     m_file_fs;
#define FATFS_BUF_SIZE_FS 1024
u8 fatfs_buf_fs[FATFS_BUF_SIZE_FS]__attribute__((aligned(32)));
static fatfs_sd_params_t *fatfs_sd;
static httpfs_params_t *httpfs_params;
int (*cb_response)(void);

static void pb_homepage_cb(struct httpd_conn *conn)
{
	char *user_agent = NULL;

	//set_playback_state();
	cb_response();

	// test log to show brief header parsing
	httpd_conn_dump_header(conn);

	// test log to show extra User-Agent header field
	if (httpd_request_get_header_field(conn, (char *)"User-Agent", &user_agent) != -1) {
		printf("\nUser-Agent=[%s]\n", user_agent);
		httpd_free(user_agent);
	}

	// GET homepage
	if (httpd_request_is_method(conn, (char *)"GET")) {

		DIR m_dir;
		FILINFO m_fileinfo;
		char *filename;
		char path[64];
		char filelist[64];
		int body_length = 0;

		const char *body = \
						   "<HTML><BODY>" \
						   "It Works<BR>" \
						   "<BR>" \
						   "You can test video playback by http://192.168.xxx.xxx/video_get.mp4?filename=xxxx.mp4<BR>" \
						   "Video file list: <BR>";

		const char *body_end = \
							   "</BODY></HTML>";

		body_length += strlen(body);
		body_length += strlen(body_end);

		const char *br = \
						 "<BR>";

#if _USE_LFN
		char fname_lfn[32];
		m_fileinfo.lfname = fname_lfn;
		m_fileinfo.lfsize = sizeof(fname_lfn);
#endif
		//fatfs_sd_get_param(&fatfs_sd);
		strcpy(path, fatfs_sd->drv);
		sprintf(&path[strlen(path)], "%s", httpfs_params->filedir);

		if (f_opendir(&m_dir, path) == 0) {
			while (1) {
				if ((f_readdir(&m_dir, &m_fileinfo) != 0) || m_fileinfo.fname[0] == 0) {
					break;
				}

#if _USE_LFN
				filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
				filename = m_fileinfo.fname;
#endif
				if (*filename == '.' || (filename[0] == '.' && filename[1] == '.')) {
					continue;
				}

				if (!(m_fileinfo.fattrib & AM_DIR)) {
					if (m_fileinfo.fsize) {
						body_length += (strlen(filename) + 4);
					}
				}
			}

			f_closedir(&m_dir);
		}

		httpd_response_write_header_start(conn, (char *)"200 OK", (char *)"text/html", body_length);
		httpd_response_write_header(conn, (char *)"Connection", (char *)"close");
		httpd_response_write_header_finish(conn);
		httpd_response_write_data(conn, (uint8_t *)body, strlen(body));
		if (f_opendir(&m_dir, path) == 0) {
			while (1) {
				if ((f_readdir(&m_dir, &m_fileinfo) != 0) || m_fileinfo.fname[0] == 0) {
					break;
				}

#if _USE_LFN
				filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
				filename = m_fileinfo.fname;
#endif
				if (*filename == '.' || (filename[0] == '.' && filename[1] == '.')) {
					continue;
				}

				if (!(m_fileinfo.fattrib & AM_DIR)) {
					if (m_fileinfo.fsize) {
						memset(filelist, 0x0, 64);
						sprintf(filelist, "%s%s", filename, br);
						httpd_response_write_data(conn, (uint8_t *)filelist, strlen(filelist));
					}
				}
			}

			f_closedir(&m_dir);
		}
		httpd_response_write_data(conn, (uint8_t *)body_end, strlen(body_end));

	} else {
		// HTTP/1.1 405 Method Not Allowed
		httpd_response_method_not_allowed(conn, NULL);
	}

	httpd_conn_close(conn);
}

static void pb_test_get_cb(struct httpd_conn *conn)
{
	// GET /test_post
	if (httpd_request_is_method(conn, (char *)"GET")) {
		char *filename = NULL;

		//set_playback_state();
		cb_response();

		// get 'filename' in query string
		if ((httpd_request_get_query_key(conn, (char *)"filename", &filename) != -1)) {

			printf("filename = %s\r\n", filename);
			size_t read_size;
			int send_size = 0;
			uint8_t buf[50];
			size_t content_len = conn->request.content_len;

			FRESULT res;
			int br;
			char path[64];
			//char sd_fn[64] = "20190121_205006_8.mp4";
			//fatfs_sd_get_param(&fatfs_sd);
			strcpy(path, fatfs_sd->drv);
			sprintf(&path[strlen(path)], "%s", httpfs_params->filedir);
			sprintf(&path[strlen(path)], "/%s", filename);

#if FAST_MP4
#if FAST_MP4_WITHOUT_FILE
			int ret = 0;
			uint32_t ftyp_size;
			uint32_t ftyp_buffer = 0;
			uint32_t moov_size;
			uint32_t moov_buffer = 0;
			uint32_t src_start_offset;
			uint32_t src_last_offset;
			int bytes_to_copy = 0;

			ret =  qt_faststart(path,
								&ftyp_size,
								&ftyp_buffer,
								&moov_size,
								&moov_buffer,
								&src_start_offset,
								&src_last_offset);
			if (ret == 0) {
				res = f_open(&m_file_fs, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
				if (res) {
					if (ftyp_buffer) {
						free((void *)ftyp_buffer);
					}
					if (moov_buffer) {
						free((void *)moov_buffer);
					}
					printf("open file (%s) fail.\n", path);
					goto httpd_conn_end;
				}
			} else {
				if (ftyp_buffer) {
					free((void *)ftyp_buffer);
				}
				if (moov_buffer) {
					free((void *)moov_buffer);
				}
				printf("qt_faststart (%s) fail.\n", path);
				goto httpd_conn_end;
			}
#else
			int ret = 0;
			char temppath[64];
			strcpy(temppath, fatfs_sd->drv);
			sprintf(&temppath[strlen(temppath)], "%s", httpfs_params->filedir);
			sprintf(&temppath[strlen(temppath)], "/temp_%s", "playback.mp4");
			ret = qt_faststart(path, temppath);
			if (ret == 0) {
				res = f_open(&m_file_fs, temppath, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
				if (res) {
					printf("open file (%s) fail.\n", temppath);
					goto httpd_conn_end;
				}
			} else {
				printf("qt_faststart (%s) fail.\n", path);
				goto httpd_conn_end;
			}
#endif
#else
			res = f_open(&m_file_fs, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
			if (res) {
				printf("open file (%s) fail.\n", filename);
				goto httpd_conn_end;
			}
#endif
#if FAST_MP4_WITHOUT_FILE
			read_size = ftyp_size + moov_size + src_last_offset;
			printf("file size = %d\r\n", read_size);
#else
			// read HTTP body
			//read_size = m_file_fs.fsize;
			read_size = f_size(&m_file_fs);
			printf("file size = %d\r\n", read_size);
#endif
			// write HTTP response
			httpd_response_write_header_start(conn, (char *)"200 OK", (char *)"text/plain", 0);
			httpd_response_write_header(conn, (char *)"Connection", (char *)"close");
			httpd_response_write_header_finish(conn);
			//memset(buf, 0, sizeof(buf));
			//sprintf((char*)buf, "%d bytes from POST: ", read_size);
			//httpd_response_write_data(conn, buf, strlen((char const*)buf));
#if FAST_MP4_WITHOUT_FILE

			if (src_start_offset > 0) {
				/* seek after ftyp atom */
				f_lseek(&m_file_fs, src_start_offset);
			}

			/* dump the same ftyp atom */
			if (ftyp_size > 0) {

				printf(" writing ftyp atom...\n");

				int send_timeout = 3000;
				if (conn->sock != -1) {
					setsockopt(conn->sock, SOL_SOCKET, SO_SNDTIMEO, &send_timeout, sizeof(send_timeout));
				}
				ret = httpd_response_write_data(conn, (void *)ftyp_buffer, ftyp_size);
				if (ret <= 0) {
					printf("ret = %d\r\n", ret);
					res = f_close(&m_file_fs);
					if (res) {
						printf("close file (%s) fail.\n", filename);
					}
					printf("f_close\n");
					printf("\n");
					free((void *)ftyp_buffer);
					free((void *)moov_buffer);
					goto httpd_conn_end;
				}
			}

			/* dump the new moov atom */
			printf(" writing moov atom...\n");

			int send_timeout = 3000;
			if (conn->sock != -1) {
				setsockopt(conn->sock, SOL_SOCKET, SO_SNDTIMEO, &send_timeout, sizeof(send_timeout));
			}
			ret = httpd_response_write_data(conn, (void *)moov_buffer, moov_size);
			if (ret <= 0) {
				printf("ret = %d\r\n", ret);
				res = f_close(&m_file_fs);
				if (res) {
					printf("close file (%s) fail.\n", filename);
				}
				printf("f_close\n");
				printf("\n");
				free((void *)ftyp_buffer);
				free((void *)moov_buffer);
				goto httpd_conn_end;
			}

			free((void *)ftyp_buffer);
			free((void *)moov_buffer);

			/* copy the remainder of the infile, from offset 0 -> last_offset - 1 */
			printf(" copying rest of file...\n");
			while (src_last_offset) {

				if (src_last_offset > 1024) {
					bytes_to_copy = 1024;
				} else {
					bytes_to_copy = src_last_offset;
				}

				res = f_read(&m_file_fs, fatfs_buf_fs, bytes_to_copy, (u32 *)&br);
				if (res) {
					f_lseek(&m_file_fs, 0);
					printf("Read error.\n");
					break;
				} else {
					int send_timeout = 3000;
					if (conn->sock != -1) {
						setsockopt(conn->sock, SOL_SOCKET, SO_SNDTIMEO, &send_timeout, sizeof(send_timeout));
					}
					ret = httpd_response_write_data(conn, fatfs_buf_fs, br);
					if (ret <= 0) {
						printf("ret = %d\r\n", ret);
						break;
					}
				}

				src_last_offset -= bytes_to_copy;
			}

			res = f_close(&m_file_fs);
			if (res) {
				printf("close file (%s) fail.\n", filename);
			}
			printf("f_close\n");
			printf("\n");


#else
			send_size = 0;
			while (1) {
				res = f_read(&m_file_fs, fatfs_buf_fs, 1024, (u32 *)&br);
				if (res) {
					f_lseek(&m_file_fs, 0);
					printf("Read error.\n");
					res = f_close(&m_file_fs);
					break;
				}

				send_size += br;
				printf("Read %d bytes.\r\n", send_size);

				if (br == 0) {
					// close source file
					res = f_close(&m_file_fs);
					if (res) {
						printf("close file (%s) fail.\n", filename);
					}
					printf("f_close\n");
					printf("\n");

					break;
				} else {
					int ret = 0;
					int send_timeout = 3000;
					if (conn->sock != -1) {
						setsockopt(conn->sock, SOL_SOCKET, SO_SNDTIMEO, &send_timeout, sizeof(send_timeout));
					}
					ret = httpd_response_write_data(conn, fatfs_buf_fs, br);
					if (ret <= 0) {
						printf("ret = %d\r\n", ret);
						res = f_close(&m_file_fs);
						if (res) {
							printf("close file (%s) fail.\n", filename);
						}
						printf("f_close\n");
						printf("\n");

						break;
					}
				}
			}
#endif

		} else {
			// HTTP/1.1 400 Bad Request
			httpd_response_bad_request(conn, (char *)"Bad Request - test1 or test2 not in query string");
		}

		if (filename) {
			httpd_free(filename);
		}
	} else {
		// HTTP/1.1 405 Method Not Allowed
		httpd_response_method_not_allowed(conn, NULL);
	}

httpd_conn_end:
	httpd_conn_close(conn);
}

static void example_httpd_thread(void *param)
{
	while (!((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)LwIP_GetIP(0) != IP_ADDR_INVALID))) {
		vTaskDelay(100);
	}

	//httpd_reg_page_callback("/", pb_homepage_cb);
	//httpd_reg_page_callback("/index.htm", pb_homepage_cb);
	//httpd_reg_page_callback("/video_get.mp4", pb_test_get_cb);

	if (httpd_start(80, 5, 4096, HTTPD_THREAD_SINGLE, HTTPD_SECURE_NONE) != 0) {
		printf("ERROR: httpd_start");
		httpd_clear_page_callbacks();
	}

	vTaskDelete(NULL);
}

int httpfs_control(void *p, int cmd, int arg)
{
	httpfs_ctx_t *ctx = (httpfs_ctx_t *)p;

	switch (cmd) {
	case CMD_HTTPFS_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(httpfs_params_t));
		httpfs_params = &ctx->params;
		break;
	case CMD_HTTPFS_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(httpfs_params_t));
		break;
	case CMD_HTTPFS_APPLY:
		httpd_reg_page_callback((char *)"/", pb_homepage_cb);
		httpd_reg_page_callback((char *)"/index.htm", pb_homepage_cb);
		httpd_reg_page_callback(ctx->params.request_string, pb_test_get_cb);
		break;
	case CMD_HTTPFS_STREAM_STOP:
		httpd_clear_page_callbacks();
		break;
	case CMD_HTTPFS_SET_RESPONSE_CB:
		ctx->cb_response = (int (*)(void))arg;
		cb_response = ctx->cb_response;
		break;
	}
	return 0;
}

int httpfs_handle(void *ctx, void *input, void *output)
{
	return 0;
}

void *httpfs_destroy(void *p)
{
	httpd_stop();
	httpfs_ctx_t *ctx = (httpfs_ctx_t *)p;
	if (ctx && ctx->up_sema) {
		rtw_free_sema(&ctx->up_sema);
	}
	if (ctx && ctx->task) {
		vTaskDelete(ctx->task);
	}
	if (ctx)	{
		free(ctx);
	}
	return NULL;
}

void *httpfs_create(void *parent)
{
	httpfs_ctx_t *ctx = malloc(sizeof(httpfs_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(httpfs_ctx_t));
	ctx->parent = parent;

	if (fatfs_sd_init() < 0) {
		goto httpfs_create_fail;
	}
	fatfs_sd_get_param(&ctx->fatfs_params);
	fatfs_sd = &ctx->fatfs_params;

	rtw_init_sema(&ctx->up_sema, 0);

	if (xTaskCreate(example_httpd_thread, ((const char *)"example_httpd_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate(example_httpd_thread) failed", __FUNCTION__);
		goto httpfs_create_fail;
	}

	return ctx;

httpfs_create_fail:
	httpfs_destroy((void *)ctx);
	return NULL;
}

void *httpfs_new_item(void *p)
{
	return NULL;
}

void *httpfs_del_item(void *p, void *d)
{
	return NULL;
}

mm_module_t httpfs_module = {
	.create = httpfs_create,
	.destroy = httpfs_destroy,
	.control = httpfs_control,
	.handle = httpfs_handle,

	.new_item = httpfs_new_item,
	.del_item = httpfs_del_item,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_MASK_SRC,
	.name = "HTTPFS"
};
