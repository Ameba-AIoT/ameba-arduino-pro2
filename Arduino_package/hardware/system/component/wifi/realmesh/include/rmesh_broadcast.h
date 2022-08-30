#ifndef _RMESH_BROADCAST_H_
#define _RMESH_BROADCAST_H_

#define RMESH_MAX_SEQ_NUM	65

#define BC_RANDOM_BYTE	4

struct rmesh_bc_seq_item {
	u32 random;
};

struct rmesh_bc_seq_table {
	struct rmesh_bc_seq_item *pitem;
	struct rmesh_bc_seq_item *pnext;
	struct rmesh_bc_seq_item *ppre;
};

int rmesh_bc_seq_check(u8 *data, u32 data_len);
extern bool rmesh_bc_seq_update(u32 seq);
extern void rmesh_bc_seq_init();

extern void rmesh_bc_packet_send(u8 *data, u32 data_len, u32 offset, struct rmesh_hdr *prmesh_hdr);
extern void rmesh_mc_packet_send(u8 *data, u32 data_len, u32 offset, struct rmesh_hdr *prmesh_hdr);

#endif
