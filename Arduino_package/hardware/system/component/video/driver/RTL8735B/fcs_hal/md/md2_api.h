#ifndef MD2_API_H
#define MD2_API_H

int md_get_enable();
int md_set(int opt, uint32_t *p);
int md_start(void);
int md_stop(void);

#endif	// MD2_API_H
