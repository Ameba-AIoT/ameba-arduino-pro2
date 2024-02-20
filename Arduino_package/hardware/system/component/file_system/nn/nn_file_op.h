#ifndef _NN_FILE_OP_H_
#define _NN_FILE_OP_H_

#include "fwfs.h"

void nn_load_model_src_sel(uint32_t arduino_model_sel);
void *nn_f_open(char *name, int mode);
void nn_f_close(void *fr);
int nn_f_read(void *fr, void *data, int size);
int nn_f_seek(void *fr, int offset, int pos);
int nn_f_tell(void *fr);

#endif
