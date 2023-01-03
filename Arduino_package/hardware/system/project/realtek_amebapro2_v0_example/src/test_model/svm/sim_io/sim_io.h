#ifndef _SIM_IO_H_
#define _SIM_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FOR_FREERTOS
#ifdef FOR_FREERTOS
#include <stdint.h>
#include <stdio.h>

typedef struct sim_file_s SIM_FILE;

int sim_getc(SIM_FILE *in);
int sim_fgetc(SIM_FILE *in);
char *sim_fgets(char *str, int size, SIM_FILE *stream);
SIM_FILE *sim_fopen(const char *path, const char *mode);
int sim_fclose(SIM_FILE *file);
int sim_feof(SIM_FILE *file);
int sim_fscanf(SIM_FILE *file, const char *format, ...);
int sim_fprintf(SIM_FILE *file, const char *format, ...);
size_t sim_fread(void *ptr, size_t size, size_t nitems, SIM_FILE *file);
size_t sim_fwrite(void *ptr, size_t size, size_t nitems, SIM_FILE *file);
int sim_ferror(SIM_FILE *stream);
int sim_fseek(SIM_FILE *stream, long offset, int whence);
long sim_ftell(SIM_FILE *stream);


#else

#define SIM_FILE				        FILE
#define sim_getc(f)				        getc(f)
#define sim_fgetc(f)					fgetc(f)
#define sim_fgets(a,b,c)		        fgets(a,b,c)
#define sim_fopen(path, mode)	        fopen(path,mode)
#define sim_fclose(a)			        fclose(a)
#define sim_feof(a)				        feof(a)
#define sim_fscanf(a, b, ...)	        fscanf(a, b, __VA_ARGS__)
#define sim_fprintf(a, b, ...)          fprintf(a, b, __VA_ARGS__)
#define sim_fread(a,b,c,d)				fread(a,b,c,d)
#define sim_fwrite(a,b,c,d)				fwrite(a,b,c,d)
#define sim_ferror(a)					ferror(a)
#define sim_fseek(a,b,c)				fseek(a,b,c)
#define sim_ftell(a)					ftell(a)

#endif

#ifdef __cplusplus
};
#endif

#endif

