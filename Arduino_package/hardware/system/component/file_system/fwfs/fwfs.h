#ifndef FWFS_H
#define FWFS_H

#define M_NORMAL		0x00
#define M_MANI			0x01
#define M_MANI_UNPT		0x02
#define M_RAW			0x03

#define M_CREATE		0x10
#define M_RDONLY		0x20
#define M_RDWR			0x30

void *pfw_open(const char *name, int mode);
void pfw_close(void *fr);
int pfw_read(void *fr, void *data, int size);
int pfw_seek(void *fr, int offset, int pos);
int pfw_tell(void *fr);
int pfw_write(void *fr, void *data, int size);

int pfw_read_unpt(void *fr, void *data, int size);
int pfw_write_unpt(void *fr, void *data, int size);

void *pfw_open_by_typeid(uint16_t type_id, int mode);
void pfw_list(int mode);

void pfw_init(void);
void pfw_deinit(void);

// API for NOR
unsigned int nor_pfw_get_address(const char *name);

#endif