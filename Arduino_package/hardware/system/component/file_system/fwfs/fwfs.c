/*
 * Get firmware from flash
 * only support read operation
 */
#include <stdio.h>
#include <stdint.h>
#include "fwfs.h"
#include <hal_cache.h>
#include "snand_api.h"
#include "flash_api.h"
#include "sys_api.h"
#include "device_lock.h"
#include "log_service.h"
#include "platform_opts.h"

//
#define DFT_NOR_USER_SPACE	0x8000
#define MAX_NOR_SIZE	16*1024*1024

#define NAND_FW_MAX_RECS 32						// 32 recs => 1 recs indicate 48 blocks, max firmare size is 32*48*128KB = 192MB
#define NAND_SPARE_SIZE	snand_spare_size		// nand spare area size in byte, 

#define FWFS_MANIFEST_SIZE	4096

#define MAX_BLK_IN_FW_AREA	(USER_DATA_BASE/128/1024) //(15*1024/128)			// 15MB, adjust in platform_opts.h

#define PTABLE_PAGE_NUM	4

#define DBG_LEVEL	LOG_ERR

#define LOG_OFF		4
#define LOG_ERR		3
#define LOG_MSG		2
#define LOG_INF		1
#define LOG_ALL		0

#define dprintf(level, ...) if(level >= DBG_LEVEL) printf(__VA_ARGS__)

static const char *manifest_valid_label = "RTL8735B";

// implement in sys_api.c but not declare in sys_api.h
extern uint8_t sys_get_boot_sel(void);

// firmware prepend manifest before raw binary and align to 4K
typedef struct manifest_s {
	uint8_t  lbl[8];
	uint16_t size;
	uint16_t vrf_alg;
	uint32_t enc_rmp_base_addr;
	uint8_t  resv2[16];
	uint8_t  sec_enc_record[8][32];
	// -- TLV format start from here
	uint8_t  tlv_start[0];
	uint8_t  pk[388];
	uint8_t  type_id[8];
	uint8_t  version[36];
	uint8_t  timestamp[12];
	uint8_t  imgsz[8];
	uint8_t  encalg[8];
	uint8_t  enckn[36];
	uint8_t  encks[36];
	uint8_t  enciv[20];
	uint8_t  hshalg[8];
	uint8_t  hshkn[36];
	uint8_t  hshks[36];
	uint8_t  ie_resv[36];
	uint8_t  hash[36];
	uint8_t  tlv_end[0];
	// -- TLV format end here
	uint8_t  signature[384];
} manifest_t;

typedef struct key_cert_rec_s {
	uint32_t start_addr;
	uint32_t length;
	uint16_t type_id;
	uint8_t resv[5];
	uint8_t valid;
} key_cert_rec_t;

typedef struct key_cert_tbl_s {
	uint16_t type_id;
	uint16_t vrf_alg;
	uint8_t resv[12];
	key_cert_rec_t rec[2];
} key_cert_tbl_t;

typedef struct manifest_unpt_s {
	uint32_t sensor_id_id_size;
	uint8_t sensor_id;
	uint8_t sensor_id_padding[3];
	uint32_t sensor_id_crc;
	uint32_t unpt_ie_resv_id_size;
	uint8_t unpt_ie_resv[0x7ec];
	uint32_t unpt_ie_crc;
} manifest_unpt_t;

enum tlv_id {
	ID_PK = 1,
	ID_VERSION,
	ID_IMGSZ,
	ID_TYPE_ID,
	ID_ENCALG,
	ID_ENCKN,
	ID_ENCKS,
	ID_ENCIV,
	ID_HSHALG,
	ID_HSHKN,
	ID_HSHKS,
	ID_HASH,
	ID_TIMST,
	ID_VID,
	ID_PID,
	ID_IMGLST,
	ID_DEP,
	ID_RMATK,
	ID_BATLV,
	ID_ACPW,
	ID_IE_RESV
};

typedef struct tlv_s {
	uint32_t id_size;
	uint8_t data[384];	// because max data is 384 bytes, valid data length depend on id_size
} tlv_t;

typedef struct img_hdr_s {
	uint32_t imglen;
	uint32_t nxtoffset;
	uint16_t type_id;
	uint16_t nxt_type_id;
	uint8_t  sec_enc_ctrl;
	uint8_t  resv234[3 + 4 + 4];
	uint32_t str_tbl;
	uint8_t  resv5678[4 + 32 + 32 + 32];
} img_hdr_t;

int tlv_get_value(uint8_t *tlv, uint8_t *tlv_end, int id, uint8_t *value)
{
	uint8_t *curr = tlv;

	int found = -1;
	while (curr < tlv_end) {
		tlv_t *ie = (tlv_t *)curr;
		int cid = ie->id_size & 0xff;
		int csize = (ie->id_size >> 8) & 0xffffff;

		if (cid == id) {
			found = 0;
			memcpy(value, ie->data, csize);
			break;
		} else {
			curr = curr + ((csize + 3) & (~3)) + 4;    // tlv header size (4) + data size (align to 4)
		}
	}

	if (found == -1) {
		dprintf(LOG_INF, "TLV not found");
	}
	return found;
}
/*
typedef struct nand_fci_s {
	uint32_t blk_cnt;
	uint32_t page_per_blk;
	uint32_t page_size;
	uint32_t spare_size;
	uint8_t  resv1[0x10];
	uint32_t part_tbl_start;
	uint32_t part_tbl_range_size;
	uint32_t vrf_alg;
	uint8_t  resv2[0x2];
	uint32_t bbt_start;
	uint32_t bbt_range_size;
} nand_fci_t;
*/

typedef struct nand_fci_s {
	uint32_t blk_cnt;
	uint32_t page_per_blk;
	uint32_t page_size;
	uint32_t spare_size;
	uint8_t  resv1[0x8];
	uint32_t bbt_start;
	uint32_t bbt_range_size;
	uint32_t part_tbl_start;
	uint32_t part_tbl_range_size;
	uint16_t vrf_alg;
	uint8_t  resv2[0x6];
	uint32_t magic_num;		// 0xff35ff876
} nand_fci_t;

typedef struct nand_part_rec_s {
	uint32_t magic_num;
	uint16_t type_id;
	uint16_t blk_cnt;
	uint16_t serial_num;
	uint8_t  resv[0x16];
	uint16_t vmap[48];
} nand_part_rec_t;

struct nand_spare_v0_s {
	uint32_t magic_num;
	uint16_t type_id;
} __attribute__((packed));

struct nand_spare_v1_s {
	uint8_t  type_id;
	uint16_t crc;
} __attribute__((packed));

struct nand_spare_s {
	uint8_t  bad_blk_tag;
	union {
		struct nand_spare_v0_s v0;
		struct nand_spare_v1_s v1;
	};
};

typedef struct nand_spare_s nand_spare_t;

typedef struct partition_s {
	nand_fci_t fci;

	nand_part_rec_t *part_rec;
	int part_blk_idx;
	int dirty;
} partition_t;

static partition_t g_partition;
static int g_pfw_inited = 0;
static snand_t flash;

// default page size and page per block
static int snand_blksize = 2048 * 64;
static int snand_pgsize = 2048;
static int snand_ppb = 64;
static int snand_spare_version = 1;
static int snand_spare_size = 32;

void nand_pfw_scan_badblock(int max_block_idx);
int nand_pfw_update_ptable(int, int, int);
void nand_pfw_update_vmap_blk_cnt(void *fr);

static char print_buf[32];

void pfw_dump_mem(uint8_t *buf, int size)
{
	int size16 = size & (~15);
	int size_r = size - size16;
	//uint8_t *base = buf;
	printf("Address  :  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F | Ascii            |\n\r");
	printf("-----------------------------------------------------------+----------------- |\n\r");
	for (int i = 0; i < size16; i += 16) {
		printf("%08x :", i);
		for (int x = 0; x < 16; x++) {
			printf(" %02x", buf[i + x]);
		}
		printf(" | ");

		memset(print_buf, 0, 32);
		for (int c = 0; c < 16; c++) {
			//printf("%c", (buf[i + c] >= 0x20 &&  buf[i + c] <= 0x7e)?(char)buf[i + c]:'.');

			if (buf[i + c] >= 0x20 &&  buf[i + c] <= 0x7e) {
				sprintf(&print_buf[c], "%c", (char)buf[i + c]);
			} else {
				sprintf(&print_buf[c], ".");
			}
		}
		printf("%s", print_buf);
		printf(" | \n\r");
	}

	if (size_r) {
		printf("%08x :", size16);
		for (int x = 0; x < size_r; x++) {
			printf(" %02x", buf[size16 + x]);
		}
		for (int x = size_r; x < 16; x++) {
			printf("   ");
		}
		printf(" | ");

		memset(print_buf, 0, 32);
		for (int c = 0; c < size_r; c++) {
			if (buf[size16 + c] >= 0x20 &&  buf[size16 + c] <= 0x7e) {
				sprintf(&print_buf[c], "%c", (char)buf[size16 + c]);
			} else {
				sprintf(&print_buf[c], ".");
			}
		}
		for (int c = size_r; c < 16; c++) {
			sprintf(&print_buf[c], " ");
		}
		printf("%s", print_buf);
		printf(" | \n\r");
	}
}

#define PARTAB_TYPE_ID (((snand_spare_version)==0)?0xD9C4:0xC4)

int nand_pfw_get_typeid(nand_spare_t *spare)
{
	if (snand_spare_version == 0) {
		return (int)spare->v0.type_id;
	} else {
		return (int)spare->v1.type_id;
	}
}

int nand_pfw_get_spare_version(nand_spare_t *spare)
{
	if (spare->v0.magic_num == 0xff35ff87) {
		snand_spare_version = 0;
	} else {
		snand_spare_version = 1;
	}
	return snand_spare_version;
}

void nand_pfw_init(void)
{
	if (g_pfw_inited == 1)	{
		return;
	}

	uint8_t *tmp = (uint8_t *)malloc(snand_pgsize * PTABLE_PAGE_NUM);

	if (!tmp) {
		dprintf(LOG_ERR, "out of resource\n\r");
		return;
	}

	snand_init(&flash);


	nand_fci_t *fci  = NULL;
	//read partition_table block16-23
	// read first page of nand control block
	for (int i = 0; i < 8; i++) {
		snand_page_read(&flash, i * snand_ppb, snand_pgsize + NAND_SPARE_SIZE, tmp);
		//pfw_dump_mem(tmp, 2048+32);
		fci = (nand_fci_t *)tmp;
		nand_spare_t *spare = (nand_spare_t *)&tmp[snand_pgsize];
		//pfw_dump_mem(&tmp[snand_pgsize], 32);
		dprintf(LOG_INF, "bad blk tag %x\n\r", spare->bad_blk_tag);
		if (spare->bad_blk_tag == 0xff) {
			nand_pfw_get_spare_version(spare);
			//pfw_dump_mem(spare, 32);
			break;
		} else {
			fci = NULL;
		}
	}
	if (fci == NULL) {
		dprintf(LOG_ERR, "No Flash control infomation\n\r");
		goto pfw_init_fail;
	}

	g_partition.dirty = 0;

	// fci sanity check
	if ((fci->page_size != 512) && (fci->page_size != 2048) && (fci->page_size != 4096) && (fci->page_size != 8192)) {
		fci->page_size = 2048;
	}

	if (fci->page_per_blk != 32 && fci->page_per_blk != 64 && fci->page_per_blk != 128 && fci->page_per_blk != 256) {
		fci->page_per_blk = 64;
	}

	/* if (fci->spare_size < 32 || fci->spare_size > 224) {
		fci->spare_size = 32;
	} */
	//snand_spare_size = fci->spare_size; //Work around to fix the issue that it will assign the wrong size form firmware.

	memcpy(&g_partition.fci, fci, sizeof(nand_fci_t));
	//pfw_dump_mem(&g_partition.fci, sizeof(nand_fci_t));
	dprintf(LOG_INF, "fci part tbl start   %lx\n\r", fci->part_tbl_start);
	dprintf(LOG_INF, "fci part tbl dup cnt %lx\n\r", fci->part_tbl_range_size);

	snand_blksize = fci->page_per_blk * fci->page_size;
	snand_pgsize = fci->page_size;
	snand_ppb    = fci->page_per_blk;

	dprintf(LOG_INF, "update page size %d  page per block %d\n\r", snand_pgsize, snand_ppb);
	// read partition table

	if (IS_CUT_B(hal_sys_get_rom_ver())) {  //B-cut partition table block 20-23
		uint8_t *buf = (uint8_t *)malloc(snand_pgsize + NAND_SPARE_SIZE);
		if (!buf) {
			dprintf(LOG_ERR, "out of resource\n\r");
			goto pfw_init_fail;
		}
		for (int i = 0; i < 4 ; i++) { //Check the 20-23 block for partition table
			snand_page_read(&flash, (fci->part_tbl_start + 4 + i) * snand_ppb, snand_pgsize + NAND_SPARE_SIZE, buf);
			nand_spare_t *spare = (nand_spare_t *)(buf + snand_pgsize);
			if (spare->bad_blk_tag == 0xff && nand_pfw_get_typeid(spare) == PARTAB_TYPE_ID) {
				fci->part_tbl_start += 4;
				fci->part_tbl_range_size -= 4;
				dprintf(LOG_INF, "It is new partition version %d\n\r", fci->part_tbl_start);
				break;
			} else if (spare->bad_blk_tag == 0xff) {
				dprintf(LOG_INF, "It is old partition version %d\n\r", fci->part_tbl_start);
				break;
			} else {
				dprintf(LOG_ERR, "Find next block %d\n\r", fci->part_tbl_start + 4 + i);
			}
		}
		if (buf) {
			free(buf);
		}
	}

	for (int i = fci->part_tbl_start; i < fci->part_tbl_start + fci->part_tbl_range_size; i++) {
		snand_page_read(&flash, i * snand_ppb, snand_pgsize + NAND_SPARE_SIZE, tmp);
		nand_spare_t *spare = (nand_spare_t *)&tmp[snand_pgsize];
		//pfw_dump_mem(tmp, 2048);
		//pfw_dump_mem(&tmp[2048], 32);
		//dprintf(LOG_INF, "bad blk tag %x\n\r", spare->bad_blk_tag);
		//dprintf(LOG_INF, "type id     %x\n\r", spare->type_id);
		if (spare->bad_blk_tag == 0xff && nand_pfw_get_typeid(spare) == PARTAB_TYPE_ID) {	// partition table id = 0xC4 or 0xD9C4, bad block tag = 0xff (health block)
			int ri = snand_pgsize;
			int si = 1;
			g_partition.part_blk_idx = i;
			while (ri < snand_pgsize * PTABLE_PAGE_NUM) {
				snand_page_read(&flash, i * snand_ppb + si, snand_pgsize, &tmp[ri]);
				ri += snand_pgsize;
				si++;
			}
			break;
		}
	}

	// dump partition
	//pfw_dump_mem(tmp, 2048);

	g_partition.part_rec = (nand_part_rec_t *)tmp;

	g_pfw_inited = 1;
	nand_pfw_scan_badblock(MAX_BLK_IN_FW_AREA);

	return;
pfw_init_fail:
	if (tmp) {
		free(tmp);
	}
	return;
}

void nand_pfw_deinit(void)
{
	if (g_pfw_inited && g_partition.part_rec) {
		free(g_partition.part_rec);
	}

	g_pfw_inited = 0;
}


// CRC parameters (default values are for CRC-32):
static int order = 16;
static unsigned long polynom = 0x8005;
static unsigned long crcxor = 0x0;
static int refin = 1;
static int refout = 1;
unsigned long crcmask;
unsigned long crchighbit;
unsigned long crcinit_direct = 0;

static unsigned long reflect(unsigned long crc, int bitnum)
{
	// reflects the lower 'bitnum' bits of 'crc'
	unsigned long i, j = 1, crcout = 0;
	for (i = (unsigned long)1 << (bitnum - 1); i; i >>= 1) {
		if (crc & i) {
			crcout |= j;
		}
		j <<= 1;
	}
	return (crcout);
}
unsigned long crc16(unsigned char *p, unsigned long len)
{
	// fast bit by bit algorithm without augmented zero bytes.
	// does not use lookup table, suited for polynom orders between 1...32.
	unsigned long i, j, c, bit;
	unsigned long crc = crcinit_direct;
	crcmask = (((1 << (15)) - 1) << 1) | 1;
	crchighbit = (1 << 15);
	for (i = 0; i < len; i++) {
		c = p[i];
		if (refin) {
			c = reflect(c, 8);
		}
		for (j = 0x80; j; j >>= 1) {
			bit = crc & crchighbit;
			crc <<= 1;
			if (c & j) {
				bit ^= crchighbit;
			}
			if (bit) {
				crc ^= polynom;
			}
		}
	}
	if (refout) {
		crc = reflect(crc, order);
	}
	crc ^= crcxor;
	crc &= crcmask;
	return (crc);
}

typedef struct part_id_map_s {
	uint16_t type_id;
	const char *name;
} part_id_map_t;

static part_id_map_t id_map[] = {
	{0xF8E0, "INI_VAL"},
	{0xF1C1, "KEY_CER_TBL"},
	{0xE9C2, "KEY_CER1"},
	{0xE1C3, "KEY_CER2"},
	{0xD9C4, "PT"},
	{0xD1C5, "BL_PRI"},
	{0xC9C6, "BL_SEC"},
	{0xC1C7, "FW1"},
	{0xB9C8, "FW2"},
	{0xB1C9, "MP"},
	{0xA9CA, "SYSDATA"},
	{0xA1CB, "WLAN_CAL"},
	{0x99CC, "USER"},
	{0x91CD, "IMG_UPDATE"},
	{0x89CE, "ISP_IQ"},
	{0x81CF, "NN_MDL"},
	{0x79D0, "NAND_CTRL"},
	{0x71D1, "NAND_BBT"},
	{0x69D2, "FCSDATA"},
	//-------------------------------- defined by sw
	{0x78D1, "UDATA"},
	{0xBADB, "BAD_BLOCK"}
};

const char *__get_pt_name(uint16_t type_id)
{
	for (int i = 1; i < sizeof(id_map) / sizeof(id_map[0]); i++) {
		if (id_map[i].type_id == type_id) {
			return id_map[i].name;
		}
	}
	return id_map[0].name;
}

uint16_t __get_pt_type_id(const char *name)
{
	for (int i = 1; i < sizeof(id_map) / sizeof(id_map[0]); i++) {
		if (strcmp(id_map[i].name, name) == 0) {
			return id_map[i].type_id;
		}
	}
	return 0xffff;
}

nand_part_rec_t *pfw_search_next(nand_part_rec_t *curr)
{
	nand_part_rec_t *next = NULL;
	while (curr->magic_num != 0xffffffff) {
		int offset = 1;
		next = &curr[offset];
		if (next->magic_num == 0xff35ff87) {
			return next;
		}
		curr = next;
	}

	return NULL;
}

nand_part_rec_t *pfw_search_next_type_id(nand_part_rec_t *curr, uint16_t type_id)
{
	nand_part_rec_t *next = NULL;
	while (curr->magic_num != 0xffffffff) {
		int offset = 1;
		next = &curr[offset];
		if (next->magic_num == 0xff35ff87) {
			if (next->type_id == type_id) {
				return next;
			}
		}
		curr = next;
	}

	return NULL;
}

nand_part_rec_t *pfw_search_type_id(uint16_t type_id)
{
	nand_part_rec_t *rec = g_partition.part_rec;
	if (g_pfw_inited == 0) {
		return NULL;
	}

	int i = 0;
	while (rec[i].magic_num != 0xffffffff) {
		if (rec[i].magic_num == 0xff35ff87) {

			if (rec[i].type_id == type_id) {
				return &rec[i];
			}
			i++;
		} else {
			i++;
		}
	}
	return NULL;
}

nand_part_rec_t *nand_pfw_get_free_rec(void)
{
	nand_part_rec_t *curr = g_partition.part_rec;
	while (curr->magic_num != 0xffffffff) {
		curr = &curr[1];
	}

	return curr;
}

nand_part_rec_t *nand_pfw_extend_rec(nand_part_rec_t *curr)
{
	// calculate curr[1] to final record number
	// move curr[1] to curr[2]
	nand_part_rec_t *base = curr;
	int cnt = 0;
	while (curr->magic_num != 0xffffffff) {
		curr = &curr[1];
		cnt++;
	}

	if ((uint32_t)base + sizeof(nand_part_rec_t) * (cnt + 1) > (uint32_t)g_partition.part_rec + 2048) {
		return NULL;
	}

	memmove(&base[2], &base[1], sizeof(nand_part_rec_t)*cnt);
	memset(&base[1], 0xff, sizeof(nand_part_rec_t));

	return &base[1];
}

int nand_pfw_check_badblock(int blk_idx)
{
	nand_part_rec_t *bad_rec = pfw_search_type_id(0xBADB);

	while (bad_rec) {
		for (int i = 0; i < bad_rec->blk_cnt; i++) {
			if (bad_rec->vmap[i] == blk_idx) {
				return 1;
			}
		}
		bad_rec = pfw_search_next_type_id(bad_rec, 0xBADB);
	}
	return 0;
}

void nand_pfw_add_badblock(int bad_idx)
{
	nand_part_rec_t *bad_rec = pfw_search_type_id(0xBADB);
	// get badblock record from partition table
	if (bad_rec == NULL) {
		bad_rec = nand_pfw_get_free_rec();
		bad_rec->magic_num = 0xff35ff87;
		bad_rec->type_id = 0xBADB;
		bad_rec->blk_cnt = 0;
		bad_rec->serial_num = 0;
	}

	// should i need to check is in list? seem trivial check
	if (nand_pfw_check_badblock(bad_idx) == 0) {
		bad_rec->vmap[bad_rec->blk_cnt] = bad_idx;
		bad_rec->blk_cnt++;
		g_partition.dirty = 1;
	}
}

int nand_pfw_mark_badblock(int bad_idx)
{
	uint8_t *tmp = malloc(snand_pgsize + 32);
	if (!tmp) {
		return -1;
	}
	dprintf(LOG_INF, "mark block %d as bad\n\r", bad_idx);
	memset(tmp, 0x0, snand_pgsize + 32);

	snand_erase_block(&flash, bad_idx * snand_ppb);
	snand_page_write(&flash, bad_idx * snand_ppb, snand_pgsize + 32, tmp);

	free(tmp);

	nand_pfw_add_badblock(bad_idx);

	return 0;
}

void nand_pfw_scan_badblock(int max_block_idx)
{
	// check bad block scan result existing
	if (pfw_search_type_id(0xBADB) != NULL) {
		return;
	}

	uint8_t *tmp = (uint8_t *)malloc(snand_pgsize * 4);

	if (!tmp) {
		dprintf(LOG_ERR, "out of resource\n\r");
		return;
	}

	dprintf(LOG_INF, "scan bad block\n\r");	//include partition table
	for (int i =  g_partition.fci.part_tbl_start; i < max_block_idx; i++) {
		snand_page_read(&flash, i * snand_ppb, snand_pgsize + NAND_SPARE_SIZE, tmp);
		nand_spare_t *spare = (nand_spare_t *)&tmp[snand_pgsize];
		if (spare->bad_blk_tag != 0xff) {
			dprintf(LOG_INF, "found bad block %d\n\r", i);
			nand_pfw_add_badblock(i);
		}
	}

	free(tmp);
}

void nand_pfw_badblock_sim_op(int op, int blk_idx)
{
	switch (op) {
	case 0:
		snand_erase_block(&flash, blk_idx * snand_ppb);
		break;
	case 1:
		if (1) {
			uint8_t *tmp = malloc(snand_pgsize + 32);
			if (!tmp) {
				return;
			}
			dprintf(LOG_INF, "sim op : mark block %d as bad\n\r", blk_idx);
			memset(tmp, 0x0, snand_pgsize + 32);

			snand_erase_block(&flash, blk_idx * snand_ppb);
			snand_page_write(&flash, blk_idx * snand_ppb, snand_pgsize + 32, tmp);

			free(tmp);
		}
		break;
	}
}

void pfw_list2(int mode)
{
	nand_part_rec_t *rec = g_partition.part_rec;

	(void)mode;

	if (g_pfw_inited == 0) {
		return;
	}
	// dump partition items
	int i = 0;
	dprintf(LOG_INF, "%4s%8s%8s\t%s\n\r", "rec", "type_id", "blk_cnt", "name");
	while (rec[i].magic_num != 0xffffffff) {
		if (rec[i].magic_num == 0xff35ff87) {
			dprintf(LOG_INF, "%4d%8x%8d\t%s\n\r", i, rec[i].type_id, rec[i].blk_cnt, __get_pt_name(rec[i].type_id));

			if (rec[i].blk_cnt > 48) {
				i = i + ((rec[i].blk_cnt - 48) + 63) / 64;
			}
			i++;
		} else {
			i++;
		}
	}
}

void nand_pfw_list(int mode)
{
	nand_part_rec_t *rec = g_partition.part_rec;
	nand_part_rec_t *base = g_partition.part_rec;
	nand_part_rec_t *next = NULL;

	if (g_pfw_inited == 0) {
		return;
	}
	// dump partition items
	if (mode == 1) {
		printf("%4s%8s%8s\t%8s\t%8s\n\r", "rec", "type_id", "blk_cnt", "name", "vmap");
	} else {
		printf("%4s%8s%8s\t%8s\n\r", "rec", "type_id", "blk_cnt", "name");
	}

	while (rec != NULL) {
		next = NULL;
		uint16_t type_id = rec->type_id;
		uint16_t blk_cnt = rec->blk_cnt;
		int search_cnt = 0;

		if (rec->blk_cnt == 48) {
			do {
				next = pfw_search_next_type_id(rec, type_id);
				if (next) {
					if (next->serial_num == rec->serial_num + 1) {
						blk_cnt += next->blk_cnt;
					}
					rec = next;

					// prevent dead lock when record broken
					search_cnt++;
					if (search_cnt > NAND_FW_MAX_RECS) {
						break;
					}
				}
			} while (next != NULL && (next->blk_cnt == 48));
		}

		printf("%4d%8x%8d\t%8s\t", ((int)rec - (int)base) / sizeof(nand_part_rec_t), type_id, blk_cnt, __get_pt_name(type_id));

		if (mode == 1) {
			for (int i = 0; i < rec->blk_cnt; i++) {
				printf("%03d ", rec->vmap[i]);
			}
		}
		printf("\n\r");

		rec = pfw_search_next(rec);
	}
}

typedef struct nand_cache_s {
	uint8_t blk[128 * 1024];
	int blk_virt;
	int blk_real;
	int blk_inuse;
} nand_cache_t;


typedef struct fw_rec_s {
	uint8_t tmp_page[4096 + 64];
	// block cache
	nand_cache_t cache;

	int tmp_page_index;
	int tmp_page_valid;
	nand_part_rec_t *part_recs[NAND_FW_MAX_RECS];
	int part_recs_cnt;
	nand_part_rec_t *part_rec;

	int curr_pos;
	uint16_t type_id;
	int mode;

	int manifest_valid;
	int content_len;
	int raw_offset;
} fw_rec_t;

/* open partiion talbe item */
int nand_pfw_read(void *fr, void *data, int size);
int nand_pfw_seek(void *fr, int offset, int pos);
int nand_pfw_flush_cache(void *fr, int update_ptbl);

void *nand_pfw_open_by_typeid(uint16_t type_id, int mode)
{
	// init firmware systemp
	nand_pfw_init();

	// open partition items by type
	fw_rec_t *fr = (fw_rec_t *)malloc(sizeof(fw_rec_t));
	if (!fr)	{
		return NULL;
	}

	memset(fr, 0, sizeof(fw_rec_t));

	fr->mode = mode;
	fr->type_id = type_id;

	nand_part_rec_t *tmp_rec = pfw_search_type_id(type_id);
	nand_part_rec_t *next_rec = NULL;
	if (tmp_rec != NULL) {
		do {
			fr->part_recs[fr->part_recs_cnt] = tmp_rec;
			fr->part_recs_cnt ++;
			do {
				next_rec = pfw_search_next_type_id(tmp_rec, type_id);
			} while ((next_rec != NULL) && (next_rec->serial_num != tmp_rec->serial_num + 1));

			tmp_rec = next_rec;
		} while (tmp_rec != NULL);
	} else {
		if (((mode & M_CREATE) && (type_id == 0x78D1)) ||
			((mode & (M_CREATE | M_RAW)) && (type_id != 0x78D1))) {
			dprintf(LOG_INF, "create new user parition\n\r");
			// only support create user type format
			nand_part_rec_t *new_rec = nand_pfw_get_free_rec();
			new_rec->magic_num = 0xff35ff87;
			new_rec->type_id = type_id;
			new_rec->blk_cnt = 0;
			new_rec->serial_num = 0;
			fr->part_recs[0] = new_rec;
			fr->part_recs_cnt = 1;
		} else {
			dprintf(LOG_ERR, "cannot open file\n\r");
		}
	}
	// use first record as default record
	fr->part_rec = fr->part_recs[0];

	if (!fr->part_rec || (fr->part_recs_cnt == 0)) {
		free(fr);
		return NULL;
	}

	// default content length = record block count * block size
	fr->content_len = ((fr->part_recs_cnt - 1) * 48 + fr->part_recs[fr->part_recs_cnt - 1]->blk_cnt) * snand_blksize;

	dprintf(LOG_INF, "open: part_rec %lx, part_recs_cnt %d, type_id %x\n\r", (uint32_t)fr->part_rec, fr->part_recs_cnt, type_id);

	if (fr->content_len > 0) {
		// read 4k
		uint8_t *tmp = malloc(4096 + sizeof(img_hdr_t));
		if (!tmp) {
			free(fr);
			return NULL;
		}

		nand_pfw_read(fr, tmp, 4096 + sizeof(img_hdr_t));
		nand_pfw_seek(fr, 0, SEEK_SET);

		//pfw_dump_mem(tmp, 64);

		manifest_t *mani = (manifest_t *)tmp;
		if (((mode & 0xf) == M_NORMAL) && (memcmp(mani->lbl, manifest_valid_label, 8) == 0)) {
			img_hdr_t *imghdr = (img_hdr_t *)&tmp[4096];
			fr->manifest_valid = 1;
			//fr->content_len = tlv_get_value(mani->tlv_start, mani->tlv_end, ID_IMGSZ, &fr->content_len);
			fr->content_len = imghdr->imglen;
			fr->raw_offset = 4096 + sizeof(img_hdr_t);
		} else {
			fr->manifest_valid = 0;
			//fr->content_len = fr->part_rec->blk_cnt * snand_blksize;
			fr->content_len = ((fr->part_recs_cnt - 1) * 48 + fr->part_recs[fr->part_recs_cnt - 1]->blk_cnt) * snand_blksize;
			fr->raw_offset = 0;
		}

		free(tmp);
	} else {
		// create manifest
		if ((mode & 0xf) == M_NORMAL) {
			dprintf(LOG_ERR, "use M_RAW for create uesr partition\n\r");
			free(fr);
			return NULL;
		}
	}
	//dprintf(LOG_INF, "raw offset %d\n\r", fr->raw_offset);

	// clean tmp page and reset position, curr_pos increased by nand_pfw_read and need reset to 0
	fr->tmp_page_valid = 0;
	fr->tmp_page_index = 0;
	fr->curr_pos = 0;

	return fr;
}

typedef struct fwfs_file_s {
	char filename[32 + 8];
	int filelen;
	int offset;
} fwfs_file_t;

typedef struct fwfs_folder_s {
	char tag[12];
	int file_cnt;
	fwfs_file_t files[32];
} fwfs_folder_t;

void *nand_pfw_open(const char *name, int mode)
{
	char name_dup[strlen(name) + 2];
	name_dup[strlen(name) + 1] = 0;
	strncpy(name_dup, name, strlen(name) + 1);

	char *file_name = name_dup;

	char *type_name = strsep(&file_name, "/");

	dprintf(LOG_INF, "type_name %s, file_name %s\n\r", type_name, file_name);

	uint16_t type_id = __get_pt_type_id(type_name);
	if (type_id == 0xffff)	{
		return NULL;
	}

	//dprintf(LOG_INF, "open fw partition %s type id %x\n\r", name, type_id);

	fw_rec_t *fr = nand_pfw_open_by_typeid(type_id, mode);

	if (mode == M_NORMAL && file_name != NULL) {
		// search filename and update file size and raw offset
		fwfs_folder_t *tmp = malloc(sizeof(fwfs_folder_t));
		if (!tmp) {
			free(fr);
			return NULL;
		}

		nand_pfw_read(fr, tmp, sizeof(fwfs_folder_t));
		nand_pfw_seek(fr, 0, SEEK_SET);
		if (strcmp(tmp->tag, "FWFSDIR") == 0) {
			for (int i = 0; i < tmp->file_cnt; i++) {
				if (strcmp(file_name, tmp->files[i].filename) == 0) {
					dprintf(LOG_INF, "file %s, len %d\n\r", tmp->files[i].filename, tmp->files[i].filelen);
					fr->content_len = tmp->files[i].filelen;
					fr->raw_offset += tmp->files[i].offset;
					break;
				}
			}
		}

		free(tmp);
	}
	return fr;
}

int nand_pfw_tell(void *fr)
{
	if (!fr)	{
		return -1;
	}
	fw_rec_t *r = (fw_rec_t *)fr;

	return r->curr_pos;
}

void nand_pfw_close(void *fr)
{
	fw_rec_t *r = (fw_rec_t *)fr;

	if (fr)	{
		nand_pfw_flush_cache(fr, 0);
		nand_pfw_update_vmap_blk_cnt(fr);
		nand_pfw_update_ptable(g_partition.part_blk_idx, g_partition.fci.part_tbl_start + g_partition.fci.part_tbl_range_size, 0);

		if (IS_CUT_B(hal_sys_get_rom_ver())) {
			if ((r->type_id == 0xD1C5) || (r->type_id == 0xC9C6)) {
				printf("update boot partition\n\r");
				nand_pfw_update_ptable(16, 20, 1);
			}
		}

		// close opend partition item
		free(fr);
	}
}

int nand_pfw_read_normal(void *fr, void *data, int size)
{
	uint8_t *data8 = (uint8_t *)data;

	if (!fr)	{
		return -1;
	}

	fw_rec_t *r = (fw_rec_t *)fr;
	// read data from parition item


	int curr_pos = r->curr_pos + r->raw_offset;
	int blksize = snand_blksize;
	int pgsize = snand_pgsize;
	int ppb = snand_ppb;

	//dprintf(LOG_INF, "read fw size %d @ %x+%x\n\r", size, r->curr_pos), r->raw_offset;
	//dprintf(LOG_INF, "fwrd: >>> curr pos %x\n\r", curr_pos );
	// convert pos to block/page/byte
	int blkk_idx = curr_pos / blksize;
	int blkk_res = curr_pos - blkk_idx * blksize;
	int page_idx = blkk_res / pgsize;
	int byte_idx = blkk_res - page_idx * pgsize;

	int rest_size = r->content_len - r->curr_pos;

	if (rest_size <= 0) {
		return EOF;
	}
	if (size > rest_size) {
		size = rest_size;
	}

	//dprintf(LOG_INF, "fwrd: blk %x page %x byte %x rec %x\n\r", blkk_idx, page_idx, byte_idx, r);
	//
	if (r->tmp_page_valid && r->tmp_page_index == page_idx) {
		int op_size = 0;
		int valid_size = 2048 - byte_idx;

		//dprintf(LOG_INF, "fwrd: read from tmp buffer, valid size %x, needed size %x\n\r", valid_size, size);
		if (valid_size >= size) {
			op_size = size;
		} else {
			op_size = valid_size;
		}

		valid_size -= op_size;
		if (valid_size == 0) {
			r->tmp_page_valid = 0;
		}

		//dprintf(LOG_INF, "fwrd: read from tmp buffer, op_size %x dst %x src %x\n\r", op_size, data8, &r->tmp_page[byte_idx]);
		memcpy(data8, &r->tmp_page[byte_idx], op_size);

		r->curr_pos += op_size;

		size -= op_size;
		data8 += op_size;
	}

	//dprintf(LOG_INF, "fwrd: rest size to read %x\n\r", size);

	if (((uint32_t)data8 & 0x1f) == 0) {

		while (size >= 2048) {

			curr_pos = r->curr_pos + r->raw_offset;
			blkk_idx = curr_pos / blksize;
			blkk_res = curr_pos - blkk_idx * blksize;
			page_idx = blkk_res / pgsize;
			byte_idx = blkk_res - page_idx * pgsize;

			r->part_rec = r->part_recs[blkk_idx / 48];
			int real_blk_idx = r->part_rec->vmap[blkk_idx % 48];

			snand_page_read(&flash, real_blk_idx * ppb + page_idx, 2048, (void *)data8);
			r->curr_pos += 2048;
			size -= 2048;
			data8 += 2048;
		}
	}

	while (size > 0) {
		int op_size = 0;

		curr_pos = r->curr_pos + r->raw_offset;
		blkk_idx = curr_pos / blksize;
		blkk_res = curr_pos - blkk_idx * blksize;
		page_idx = blkk_res / pgsize;
		byte_idx = blkk_res - page_idx * pgsize;

		int real_blk_idx = 0;

		r->part_rec = r->part_recs[blkk_idx / 48];

		real_blk_idx = r->part_rec->vmap[blkk_idx % 48];
		//dprintf(LOG_INF, "fwrd: logical blk %x physical blk %x\n\r", blkk_idx, real_blk_idx);
		//dprintf(LOG_INF, "fwrd: blk %x phyb %x page %x byte %x rec %x\n\r", blkk_idx, real_blk_idx, page_idx, byte_idx, r);

		op_size = size;

		snand_page_read(&flash, real_blk_idx * ppb + page_idx, 2048, r->tmp_page);

		if (size >= 2048) {
			op_size = 2048;
			//snand_page_read(&flash, real_blk_idx * ppb + page_idx, 2048, data8);
		} else {
			//snand_page_read(&flash, real_blk_idx * ppb + page_idx, 2048, r->tmp_page);
			//memcpy(data8, r->tmp_page, size);
			r->tmp_page_valid = 1;
			r->tmp_page_index = page_idx;

			op_size = size;
		}
		memcpy(data8, &r->tmp_page[byte_idx], op_size);

		r->curr_pos += op_size;

		size -= op_size;
		data8 += op_size;
	}

	return (int)data8 - (int)data;
	//dprintf(LOG_INF, "fwrd: <<< curr pos %x\n\r", r->curr_pos );
}

int nand_pfw_update_ptable(int part_blk_idx, int end_idx, int force)
{
	nand_part_rec_t *part_rec = g_partition.part_rec;
	//int part_blk_idx = g_partition.part_blk_idx;

	uint8_t *tmp = malloc(snand_pgsize + 32);
	if (!tmp)	{
		return -1;
	}

	// check what condition it will use 2nd parition block
	// if parition blk 1 is wrong data and rom code can read 2nd blk as backup,
	// need change erase and write strategy, for example, write to 2nd blk then erase 1st
	// currently, use erase, write and check

	// erase partition table

	if (force == 0 && g_partition.dirty == 0) {
		free(tmp);
		return 0;
	}

	dcache_clean_by_addr((uint32_t *)part_rec, PTABLE_PAGE_NUM * snand_ppb);

	// dump partition
	//pfw_dump_mem((uint8_t*)part_rec, 2048);

	int es_status, wr_status, rd_status, cmp_status;
#if 1
	do {
		int retry = 3;
		do {
			es_status = snand_erase_block(&flash, part_blk_idx * snand_ppb);
			// write partition table
			for (int i = 0; i < PTABLE_PAGE_NUM; i++) {
				uint8_t *part_u8 = (uint8_t *)part_rec;
				nand_spare_t *spare = (nand_spare_t *)&tmp[snand_pgsize];
				memcpy(tmp, &part_u8[i * snand_pgsize], snand_pgsize);
				memset(spare, 0xff, NAND_SPARE_SIZE);
				uint32_t crc = crc16(tmp, snand_pgsize);
				spare->v1.crc = (uint16_t)(crc & 0xffff);
				spare->v1.type_id = PARTAB_TYPE_ID;

				dprintf(LOG_INF, "ptable write to blk %d\n\r", part_blk_idx);
				wr_status = snand_page_write(&flash, part_blk_idx * snand_ppb + i, snand_pgsize + 32, tmp);
				rd_status = snand_page_read(&flash, part_blk_idx * snand_ppb + i, snand_pgsize, tmp);
				cmp_status = memcmp(&part_u8[i * snand_pgsize], tmp, snand_pgsize);
				if (cmp_status != 0) {
					break;
				}
			}
			retry--;
		} while (cmp_status != 0 && retry > 0);

		if (cmp_status != 0) {
			//dprintf(LOG_INF, "fatal : fail to update current partition table, status cmp/es/wr/rd = %d/%d/%d/%d\n\r", cmp_status, es_status, wr_status, rd_status);
			//while(1);
			dprintf(LOG_INF, "badblock : fail to update current partition table, status cmp/es/wr/rd = %d/%d/%d/%d\n\r", cmp_status, es_status, wr_status, rd_status);
			nand_pfw_mark_badblock(part_blk_idx);

			while (nand_pfw_check_badblock(++part_blk_idx) != 0) {
				dprintf(LOG_INF, "change partition block to %d\n\r", part_blk_idx);
				if (part_blk_idx >= end_idx) {
					dprintf(LOG_INF, "all partition block broken\n\r");
					return -1;
				}
			}
			// not update if force mode
			if (force == 0)	{
				g_partition.part_blk_idx = part_blk_idx;
			}
		}
	} while (cmp_status != 0);
#else	// seem not support
	int part_start_idx = g_partition.fci.part_tbl_start;
	int part_dup_cnt = g_partition.fci.part_tbl_range_size;
	int part_new_idx;
	do {
		// search new partition table block
		for (part_new_idx = part_start_idx; part_new_idx < part_start_idx + part_dup_cnt; part_new_idx++)
			if (part_new_idx != part_blk_idx && nand_pfw_check_badblock(part_new_idx) == 0) {
				break;
			}
		dprintf(LOG_INF, "new partition block %d, old %d\n\r", part_new_idx, part_blk_idx);

		int retry = 3;
		do {
			es_status = snand_erase_block(&flash, part_new_idx * snand_ppb);
			// write partition table
			wr_status = snand_page_write(&flash, part_new_idx * snand_ppb, snand_pgsize, (uint8_t *)part_rec);
			rd_status = snand_page_read(&flash, part_new_idx * snand_ppb, snand_pgsize, tmp);
			retry--;
		} while ((cmp_status = memcmp(part_rec, tmp, snand_pgsize)) != 0 && retry > 0);

		if (cmp_status != 0) {
			// mark bad block
			dprintf(LOG_INF, "badblock : fail to update current partition table, status cmp/es/wr/rd = %d/%d/%d/%d\n\r", cmp_status, es_status, wr_status, rd_status);
			nand_pfw_mark_badblock(part_new_idx);
		}
	} while (cmp_status != 0);

	// erase old partition
	es_status = snand_erase_block(&flash, g_partition.part_blk_idx * snand_ppb);

	// update this for everytime write ptable in new block, else only write to fix block otherwire than original one
	if (force == 0) {
		g_partition.part_blk_idx = part_new_idx;
	}
#endif

	if (force == 0) {
		g_partition.dirty = 0;
	}

	free(tmp);
	return 0;
}

static uint8_t nand_blk_static[MAX_BLK_IN_FW_AREA];
int nand_pfw_find_free_block(int orig_idx)
{
	// current vmap to generate usage log and get max block index
	// only use max rec block index + 1 until MAX_BLK_IN_FW_AREA reached
	int max_used_blk_idx = MAX_BLK_IN_FW_AREA;
	int new_blk_idx = orig_idx;
	nand_part_rec_t *rec = g_partition.part_rec;
	//nand_part_rec_t *next = NULL;

	// search after partition table, NOTE: partition table area bad block also store in badblock record
	int valid_start_idx = g_partition.fci.part_tbl_start + g_partition.fci.part_tbl_range_size;
	int valid_min_blk_idx = MAX_BLK_IN_FW_AREA;

	memset(nand_blk_static, 0, MAX_BLK_IN_FW_AREA);
	while (rec != NULL) {
		for (int i = 0; i < rec->blk_cnt; i++) {
			nand_blk_static[rec->vmap[i]] = 1;
		}
		rec = pfw_search_next(rec);
	}

	for (int i = 0; i < MAX_BLK_IN_FW_AREA; i += 16) {
		for (int x = 0; x < 16; x++) {
			dprintf(LOG_MSG,  "%d ", nand_blk_static[i + x]);
		}
		dprintf(LOG_MSG, "\n\r");
	}

	for (int i = valid_start_idx; i < MAX_BLK_IN_FW_AREA - 1; i++) {
		if (nand_blk_static[i] == 0) {
			valid_min_blk_idx = i;
			break;
		}
	}
	dprintf(LOG_MSG, "valid min %d\n\r", valid_min_blk_idx);

	for (int i = MAX_BLK_IN_FW_AREA - 1; i >= valid_start_idx; i--) {
		if (nand_blk_static[i] == 1) {
			max_used_blk_idx = i;
			break;
		}
	}

	dprintf(LOG_MSG, "used max %d\n\r", max_used_blk_idx);

	new_blk_idx = max_used_blk_idx + 1;
	while (nand_pfw_check_badblock(new_blk_idx)) {
		new_blk_idx++;
	}

	if (max_used_blk_idx >= (MAX_BLK_IN_FW_AREA - 1)) {
		new_blk_idx = valid_min_blk_idx;
	}

	dprintf(LOG_INF, "orig blk %d, new blk %d\n\r", orig_idx, new_blk_idx);

	if (new_blk_idx > (MAX_BLK_IN_FW_AREA - 1)) {
		dprintf(LOG_ERR, "out of firmware space\n\r");
		new_blk_idx = -1;
	}
	// max 16MB --> 16*8block = 128block is max
	return new_blk_idx;
}

static int snand_block_write(snand_t *obj, uint32_t *address, uint32_t Length, uint8_t *data)
{
	int op_block = *address / snand_ppb;
	int blk_retry = 3;
	int rd_status = 0;
	int wr_status = 0;
	int es_status = 0;
	int cmp_status = 0;

	uint8_t *tmp = malloc(snand_pgsize);
	if (!tmp)	{
		return -1;
	}

	dcache_clean_by_addr((uint32_t *)data, Length);
	do {
		do {
			es_status = snand_erase_block(&flash, *address);

			for (int i = 0; i < snand_ppb; i++) {


				wr_status = snand_page_write(obj, *address + i, snand_pgsize, &data[i * snand_pgsize]);
				rd_status = snand_page_read(obj, *address + i, snand_pgsize, tmp);
				cmp_status = memcmp(tmp, &data[i * snand_pgsize], snand_pgsize);

				// bad block, exit this loop
				if (cmp_status != 0) {
					break;
				}
			}
			blk_retry--;
		} while (cmp_status != 0 && blk_retry > 0);

		if (cmp_status != 0) {
			// mark current op_block as bad block
			nand_pfw_mark_badblock(op_block);
			// find new block
			op_block = nand_pfw_find_free_block(op_block);
			if (op_block < 0) {
				dprintf(LOG_ERR, "fatal, out of resource\n\r");
				free(tmp);
				return -1;
			}
			*address = op_block * snand_ppb;
		}
	} while (cmp_status != 0);

	if (cmp_status != 0) {
		dprintf(LOG_ERR, "fatal : fail to write block, status cmp/es/wr/rd = %d/%d/%d/%d\n\r", cmp_status, es_status, wr_status, rd_status);
		return -1;
	}

	free(tmp);
	dprintf(LOG_INF, "nand block write success\n\r");
	return 0;
}

// sum all block count and update to every record
void nand_pfw_update_vmap_blk_cnt(void *fr)
{
	fw_rec_t *r = (fw_rec_t *)fr;

	int blk_cnt = 0;
	for (int i = 0; i < NAND_FW_MAX_RECS; i++) {
		if (r->part_recs[i] != NULL) {
			if (blk_cnt < r->part_recs[i]->blk_cnt) {
				blk_cnt = r->part_recs[i]->blk_cnt;
			}
		}
	}

	for (int i = 0; i < NAND_FW_MAX_RECS; i++) {
		if (r->part_recs[i] != NULL) {
			r->part_recs[i]->blk_cnt = blk_cnt;
		}
	}
}

int nand_pfw_flush_cache(void *fr, int update_ptbl)
{
	fw_rec_t *r = (fw_rec_t *)fr;
	int new_blk;

	if (r->cache.blk_inuse != 0) {
		// cache is new block
		if (r->cache.blk_real == 0xffff) {
			nand_part_rec_t *part_rec = r->part_recs[r->cache.blk_virt / 48];
			//part_rec->blk_cnt++;
			if (r->cache.blk_virt + 1 > part_rec->blk_cnt) {
				part_rec->blk_cnt = r->cache.blk_virt + 1;
			}
			r->content_len += snand_blksize;
		}
		// flush current cache
		dprintf(LOG_INF, "start flush cache\n\r");
		int status;
		do {
			new_blk = nand_pfw_find_free_block(r->cache.blk_real);
			if (new_blk < 0) {
				return -1;
			}
			// block write to new
			//snand_erase_block(&flash, r->cache.blk_real*snand_ppb);
			uint32_t address = new_blk * snand_ppb;
			status = snand_block_write(&flash, &address, snand_blksize, r->cache.blk);
			new_blk = address / snand_ppb;
			dprintf(LOG_INF, "write to block %d, old blk %d\n\r", new_blk, r->cache.blk_real);
			if (status < 0) {
				dprintf(LOG_INF, "fatal : seems all bad block\n\r");
				return -1;
			}
		} while (status < 0);

		if (new_blk != r->cache.blk_real) {
			dprintf(LOG_INF, "update parition table\n\r");

			nand_part_rec_t *part_rec = r->part_recs[r->cache.blk_virt / 48];
			part_rec->vmap[r->cache.blk_virt % 48] = new_blk;
			g_partition.dirty = 1;

			/*
			for(int i=0;i<part_rec->blk_cnt;i++)
				printf("%03d ", part_rec->vmap[i]);
			printf("\n\r");
			*/
			// write parition table
			if (update_ptbl) {
				nand_pfw_update_vmap_blk_cnt(fr);
				nand_pfw_update_ptable(g_partition.part_blk_idx, g_partition.fci.part_tbl_start + g_partition.fci.part_tbl_range_size, 0);

				if (IS_CUT_B(hal_sys_get_rom_ver())) {
					if ((r->type_id == 0xD1C5) || (r->type_id == 0xC9C6)) {
						printf("update boot partition\n\r");
						nand_pfw_update_ptable(16, 20, 1);
					}
				}
			}
		}

		r->cache.blk_inuse = 0;
	}
	return 0;
}

int nand_pfw_update_cache(void *fr, int blk_real, int blk_virt)
{
	//int blksize = snand_blksize;
	int pgsize = snand_pgsize;
	int ppb = snand_ppb;

	fw_rec_t *r = (fw_rec_t *)fr;

	if (r->cache.blk_inuse == 0) {
		// backup block data
		r->cache.blk_real = blk_real;
		r->cache.blk_virt = blk_virt;
		for (int i = 0; i < ppb; i++) {
			snand_page_read(&flash, blk_real * ppb + i, pgsize, &r->cache.blk[i * pgsize]);
		}
		r->cache.blk_inuse = 1;
	}
	return 0;
}

int nand_pfw_update_flash(void *fr, void *data, int size)
{
	uint8_t *data8 = (uint8_t *)data;

	if (!fr)	{
		return -1;
	}

	fw_rec_t *r = (fw_rec_t *)fr;

	int blksize = snand_blksize;
	int pgsize = snand_pgsize;
	int ppb = snand_ppb;

	dprintf(LOG_INF, "curr post %x\n\r", r->curr_pos);

	while (size > 0) {
		// get position
		int curr_pos = r->curr_pos + r->raw_offset;
		int blkk_idx = curr_pos / blksize;
		int blkk_res = curr_pos - blkk_idx * blksize;
		int page_idx = blkk_res / pgsize;
		int byte_idx = blkk_res - page_idx * pgsize;
		int real_blk_idx = 0;

		dprintf(LOG_INF, "blkk_idx %d, page_idx %d, byte_idx %d\n\r", blkk_idx, page_idx, byte_idx);

		r->part_rec = r->part_recs[blkk_idx / 48];
		if (r->part_rec) {	// existing block
			int vmap_idx = blkk_idx % 48;
			dprintf(LOG_INF, "vmap_idx %d, rec blk count %d\n\r", vmap_idx, r->part_rec->blk_cnt);
			if (vmap_idx <= (r->part_rec->blk_cnt - 1)) {
				real_blk_idx = r->part_rec->vmap[vmap_idx];
			} else {
				real_blk_idx = 0xffff;    // don't care vmap value
			}
			/*
			if (real_blk_idx == 0xffff) {	// new allocated block
				// will not exceed 48
				r->part_rec->blk_cnt++;
				r->content_len += blksize;
			}
			*/
		} else {
			// find new block and add to partition table
			// only support create user type format
			dprintf(LOG_INF, "create new user partition\n\r");
			r->part_recs[blkk_idx / 48] = nand_pfw_extend_rec(r->part_recs[(blkk_idx - 47) / 48]);
			if (r->part_recs[blkk_idx / 48] == NULL) {
				dprintf(LOG_ERR, "out of fw space\n\r");
				return -1;
			}
			//r->part_recs[blkk_idx / 48] = nand_pfw_get_free_rec();
			r->part_rec = r->part_recs[blkk_idx / 48];

			r->part_rec->serial_num = blkk_idx / 48;
			r->part_rec->magic_num = 0xff35ff87;
			r->part_rec->type_id = r->part_recs[0]->type_id;
			r->part_rec->blk_cnt = 0;
			r->part_recs_cnt++;
			r->content_len = 0;
			real_blk_idx = 0xffff;
		}

		dprintf(LOG_INF, "data blk idx %d, virt blk %d, cache blk idx %d, cache virt blk %d\n\r", real_blk_idx, blkk_idx, r->cache.blk_real, r->cache.blk_virt);
		if ((r->cache.blk_real != real_blk_idx) || (r->cache.blk_virt != blkk_idx)) {
			// flush current cache
			dprintf(LOG_INF, ">>> cache flush to nand\n\r");
			if (nand_pfw_flush_cache(fr, 0) < 0) {
				return -1;
			}
		}

		if (r->cache.blk_inuse == 0) {
			r->cache.blk_real = real_blk_idx;
			r->cache.blk_virt = blkk_idx;
			// backup block data
			if (real_blk_idx != 0xffff) {
				dprintf(LOG_INF, ">>> cache update, blk real %d, blk virt %d\n\r", real_blk_idx, blkk_idx);
				for (int i = 0; i < ppb; i++) {
					snand_page_read(&flash, real_blk_idx * ppb + i, pgsize, &r->cache.blk[i * pgsize]);
				}
				dprintf(LOG_INF, "data 64 byte in cache head\n\r");
				//pfw_dump_mem(r->cache.blk, 64);
			} else {
				// new block case
				memset(r->cache.blk, 0xff, ppb * pgsize);
			}
			r->cache.blk_inuse = 1;

			dprintf(LOG_INF, "D0 : cached blk real %d, virt %d\n\r", r->cache.blk_real, r->cache.blk_virt);
		}

		// update somehting want to change
		int cache_blk_idx = page_idx * pgsize + byte_idx;
		int rest_size = blksize - cache_blk_idx;
		int op_size = size > rest_size ? rest_size : size;
		dprintf(LOG_INF, "D1 : cached blk real %d, virt %d\n\r", r->cache.blk_real, r->cache.blk_virt);
		dprintf(LOG_INF, "update to cache block offset %d, size %d\n\r", cache_blk_idx, op_size);
		//pfw_dump_mem(data8, op_size);
		memcpy(&r->cache.blk[cache_blk_idx], data8, op_size);
		dprintf(LOG_INF, "D2 : cached blk real %d, virt %d\n\r", r->cache.blk_real, r->cache.blk_virt);
		data8 += op_size;
		size -= op_size;
		r->curr_pos += op_size;

	}
	dprintf(LOG_INF, "D3 : cached blk real %d, virt %d, rec->blk_cnt %d\n\r", r->cache.blk_real, r->cache.blk_virt, r->part_rec->blk_cnt);
	//if (nand_pfw_flush_cache(fr, 0) < 0) {
	//	return -1;
	//}

	return 0;
}

int nand_pfw_write_normal(void *fr, void *data, int size)
{
	return nand_pfw_update_flash(fr, data, size);
}

int nand_pfw_read_mani_unpt(void *fr, void *data, int size)
{
	fw_rec_t *r = (fw_rec_t *)fr;
	if (r->mode != M_MANI_UNPT)	{
		return -1;
	}
	if (size > 0x800)	{
		size = 0x800;
	}

	nand_pfw_seek(fr, 0x800, SEEK_SET);
	nand_pfw_read_normal(fr, data, size);
	return 0;
}

int nand_pfw_write_mani_unpt(void *fr, void *data, int size)
{
	fw_rec_t *r = (fw_rec_t *)fr;
	if (r->mode != M_MANI_UNPT)	{
		return -1;
	}
	if (size > 0x800)	{
		size = 0x800;
	}

	nand_pfw_seek(fr, 0x800, SEEK_SET);
	nand_pfw_update_flash(fr, data, size);
	return 0;
}

int nand_pfw_read_raw(void *fr, void *data, int size)
{
	//fw_rec_t *r = (fw_rec_t *)fr;
	return nand_pfw_read_normal(fr, data, size);
}

int nand_pfw_write_raw(void *fr, void *data, int size)
{
	//fw_rec_t *r = (fw_rec_t *)fr;
	return nand_pfw_update_flash(fr, data, size);
}

int nand_pfw_read(void *fr, void *data, int size)
{
	fw_rec_t *r = (fw_rec_t *)fr;

	switch (r->mode & 0xf) {
	case M_NORMAL:
		return nand_pfw_read_normal(fr, data, size);
	case M_MANI_UNPT:
		return nand_pfw_read_mani_unpt(fr, data, size);
	case M_RAW:
		return nand_pfw_read_raw(fr, data, size);
	}
	return 0;
}

int nand_pfw_write(void *fr, void *data, int size)
{
	fw_rec_t *r = (fw_rec_t *)fr;

	switch (r->mode & 0xf) {
	case M_NORMAL:
		if (r->type_id != 0x78D1) {
			return -1;
		}
		return nand_pfw_write_normal(fr, data, size);
	case M_MANI_UNPT:
		return nand_pfw_write_mani_unpt(fr, data, size);
	case M_RAW:
		return nand_pfw_write_raw(fr, data, size);
	}
	return 0;
}

/* SEEK_SET 0, SEEK_CUR 1, SEEK_END 2 */
int nand_pfw_seek(void *fr, int offset, int pos)
{
	if (!fr)	{
		return -1;
	}

	fw_rec_t *r = (fw_rec_t *)fr;

	int blksize = snand_blksize;
	int pgsize = snand_pgsize;
	int ppb = snand_ppb;

	switch (pos) {
	case SEEK_SET:
		r->curr_pos = offset;

		break;
	case SEEK_CUR:

		r->curr_pos += offset;
		break;
	case SEEK_END:
		r->curr_pos = r->content_len - offset;

		break;
	}

	int max_pos = r->content_len;
	if (r->curr_pos < 0)	{
		r->curr_pos = 0;
	}
	if (r->curr_pos > max_pos) {
		r->curr_pos = max_pos;
	}

	//dprintf(LOG_INF, "seek to offset %d from pos %d = %x\n\r", offset, pos, r->curr_pos);

	int curr_pos = r->curr_pos + r->raw_offset;
	int blkk_idx = curr_pos / blksize;
	int blkk_res = curr_pos - blkk_idx * blksize;
	int page_idx = blkk_res / pgsize;
	//int byte_idx = blkk_res - page_idx * pgsize;
	int real_blk_idx = 0;

	r->part_rec = r->part_recs[blkk_idx / 48];

	real_blk_idx = r->part_rec->vmap[blkk_idx % 48];
	// update tmp_buffer

	snand_page_read(&flash, real_blk_idx * ppb + page_idx, 2048, r->tmp_page);

	r->tmp_page_valid = 1;
	r->tmp_page_index = page_idx;

	return 0;
}

//--------------------------------------------------------------------------------------
// NOR implement
//--------------------------------------------------------------------------------------

typedef struct nor_part_hdr_s {
	uint8_t rec_num;
	uint8_t bl_p_idx;
	uint8_t bl_s_idx;
	uint8_t fw1_idx;
	uint8_t fw2_idx;
	uint8_t iq_idx;
	uint8_t nn_m_idx;
	uint8_t mp_idx;
	uint8_t keycert1_idx;	// reserved
	uint8_t keycert2_idx;	// reserved
	uint8_t fcs_idx;
	uint8_t resv1[5];
	uint16_t ota_trap;
	uint16_t mp_trap;
	uint32_t udl;
	uint8_t resv2[8];
} nor_part_hdr_t;

typedef struct nor_part_rec_s {
	uint32_t start_addr;
	uint32_t length;
	uint16_t type_id;
	uint8_t  resv1[5];
	uint8_t  valid;
	uint8_t  resv2[16];
} nor_part_rec_t;


nor_part_rec_t special_rec[5] = {
	{
		// CER_TBL
		.start_addr = 32,
		.length = 2048,
		.type_id = 0xF1C1,
		.valid = 1
	},
	{
		// PT
		.start_addr = 0x1000,
		.length = 4096 * 2,
		.type_id = 0xD9C4,
		.valid = 1
	},
	{
		// CERT1
		.start_addr = 0,
		.length = 4096,
		.type_id = 0xE9C2,
		.valid = 0
	},
	{
		// CERT2
		.start_addr = 0,
		.length = 4096,
		.type_id = 0xE1C3,
		.valid = 0
	},
	{
		.type_id = 0xFFFF
	}
};

#define NOR_ADDR(x) (FLASH_BASE+(x))

flash_t nor_flash;

static uint8_t *g_ptable = NULL;
nor_part_hdr_t *g_nor_part_hdr = NULL;
nor_part_rec_t *g_nor_part_rec = NULL;

int nor_pfw_seek(void *fr, int offset, int pos);
int nor_pfw_read(void *fr, void *data, int size);

#define ATOMIC_CALL( func ) \
	device_mutex_lock(RT_DEV_LOCK_FLASH);\
	func;\
	device_mutex_unlock(RT_DEV_LOCK_FLASH);


void nor_pfw_init(void)
{
	if (g_pfw_inited == 1)	{
		return;
	}

	g_ptable = malloc(4096);
	if (!g_ptable) {
		g_pfw_inited = 0;
		return;
	}
	// find partition record from NOR flash, fix position 0x2000 (not include manifest)
	// copy to ram for write purpose
	//memcpy(g_ptable, (void *)NOR_ADDR(0x2000), 4096);

	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)0x2000, 4096, g_ptable));

	key_cert_tbl_t cert_info;
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)32, sizeof(key_cert_tbl_t), (uint8_t *)&cert_info));

	special_rec[2].start_addr = cert_info.rec[0].start_addr;
	special_rec[2].valid = cert_info.rec[0].valid;
	special_rec[3].start_addr = cert_info.rec[1].start_addr;
	special_rec[3].valid = cert_info.rec[1].valid;

	g_nor_part_hdr = (nor_part_hdr_t *)g_ptable;
	g_nor_part_rec = (nor_part_rec_t *)&g_ptable[sizeof(nor_part_hdr_t)];
	//g_nor_part_hdr = (nor_part_hdr_t *)NOR_ADDR(0x2000);
	//g_nor_part_rec = (nor_part_rec_t *)NOR_ADDR(0x2000 + sizeof(nor_part_hdr_t));

	dprintf(LOG_INF, "NOR flash firmware init @ %lx\n\r", (uint32_t)g_nor_part_rec);

	g_pfw_inited = 1;
}

void nor_pfw_deinit(void)
{
	free(g_ptable);
	g_ptable = NULL;
	g_pfw_inited = 0;
}

void nor_pfw_list(int mode)
{
	nor_part_rec_t *rec = g_nor_part_rec;
	(void)mode;

	if (g_pfw_inited == 0) {
		return;
	}
	// dump partition items
	int i = 0;
	printf("%4s%8s%8s%8s%8s\t%s\n\r", "rec", "type_id", "addr", "len", "valid", "name");
	while (rec[i].type_id != 0xffff && rec[i].type_id != 0) {

		printf("%4d%8x%10lx%8d%8d\t%s\n\r", i, rec[i].type_id, rec[i].start_addr, (int)rec[i].length, rec[i].valid, __get_pt_name(rec[i].type_id));
		i++;
	}
	int last_idx = i;
	i = 0;
	while (special_rec[i].type_id != 0xffff && special_rec[i].type_id != 0) {

		printf("%4d%8x%10lx%8d%8d\t%s\n\r", last_idx + i, special_rec[i].type_id, special_rec[i].start_addr, (int)special_rec[i].length, special_rec[i].valid,
			   __get_pt_name(special_rec[i].type_id));
		i++;
	}
}

unsigned int nor_pfw_get_address(const char *name)
{
	uint16_t type_id = __get_pt_type_id(name);

	nor_pfw_init();
	nor_part_rec_t *rec = g_nor_part_rec;
	int i = 0;
	while (rec[i].type_id != 0xffff && rec[i].type_id != 0) {
		if (rec[i].type_id == type_id) {
			return rec[i].start_addr;
		}
		i++;
	}

	i = 0;
	while (special_rec[i].type_id != 0xffff && special_rec[i].type_id != 0) {
		if (special_rec[i].type_id == type_id) {
			return special_rec[i].start_addr;
		}
		i++;
	}

	return 0xffffffff;
}

typedef struct nor_fw_rec_s {
	uint16_t type_id;
	int mode;

	nor_part_rec_t *part_rec;

	int curr_pos;

	int manifest_valid;
	int content_len;
	int raw_offset;
} nor_fw_rec_t;

nor_part_rec_t *nor_pfw_search_type_id(uint16_t type_id)
{
	nor_part_rec_t *rec = g_nor_part_rec;
	if (g_pfw_inited == 0) {
		return NULL;
	}

	int i = 0;
	while (rec[i].type_id != 0xffff && rec[i].type_id != 0) {
		if (rec[i].type_id == type_id) {
			return &rec[i];
		}
		i++;
	}

	// check special partition
	i = 0;
	while (special_rec[i].type_id != 0xffff && special_rec[i].type_id != 0) {
		if (special_rec[i].type_id == type_id) {
			return &special_rec[i];
		}
		i++;
	}

	return NULL;
}

int addr_comparator(const void *pa, const void *pb)
{
	nor_part_rec_t *a = (nor_part_rec_t *)pa;
	nor_part_rec_t *b = (nor_part_rec_t *)pb;
	int diff = a->start_addr - b->start_addr;
	if (diff < 0) {
		return 1;
	} else if (diff > 0) {
		return -1;
	}
	return 0;
}


uint32_t nor_pfw_find_available_space(int size)
{
	nor_part_rec_t *rec = g_nor_part_rec;
	if (g_pfw_inited == 0) {
		return 0;
	}
	int new_start_addr = 0;
	int num = g_nor_part_hdr->rec_num;

	nor_part_rec_t *tmp = malloc(sizeof(nor_part_rec_t) * (num + 1));
	if (!tmp) {
		return 0;    // fail, return no space
	}
	memcpy(tmp, rec, sizeof(nor_part_rec_t)*num);

	// sort partition by start_addr
	qsort(tmp, num, sizeof(nor_part_rec_t), addr_comparator);

	// find available gap between fw image, from last image
	for (int i = num - 1; i >= 0; i--) {
		uint32_t end = tmp[i].start_addr + tmp[i].length;
		uint32_t next = MAX_NOR_SIZE;
		if (i != num - 1) {
			next =  tmp[i + 1].start_addr + tmp[i + 1].length;
		}

		if (next - end > size) {
			new_start_addr = end;
		}
	}

	free(tmp);

	return new_start_addr;
}

nor_part_rec_t *nor_pfw_get_free_rec(void)
{
	nor_part_rec_t *rec = g_nor_part_rec;
	if (g_pfw_inited == 0) {
		return NULL;
	}

	int i = 0;
	while (rec[i].type_id != 0xffff && rec[i].type_id != 0) {
		i++;
	}
	return &rec[i];
}

void nor_pfw_update_ptable(void)
{

	dcache_clean_by_addr((uint32_t *)g_ptable, 4096);
	// erase sector
	//ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)NOR_ADDR(0x2000)));
	ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)0x2000));
	// write sector
	//ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)NOR_ADDR(0x2000), 4096, g_ptable));
	ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)0x2000, 4096, g_ptable));
}

void *nor_pfw_open_by_typeid(uint16_t type_id, int mode)
{
	// init firmware systemp
	nor_pfw_init();

	// open partition items by type
	nor_fw_rec_t *fr = (nor_fw_rec_t *)malloc(sizeof(nor_fw_rec_t));
	if (!fr)	{
		return NULL;
	}

	memset(fr, 0, sizeof(nor_fw_rec_t));

	fr->mode = mode;
	fr->type_id = type_id;

	fr->part_rec = nor_pfw_search_type_id(type_id);

	if (fr->part_rec == NULL) {
		if (type_id == 0x78D1 && mode & M_CREATE) {
			nor_part_rec_t *usr_rec = nor_pfw_get_free_rec();
			usr_rec->type_id = 0x78D1;
			usr_rec->start_addr = nor_pfw_find_available_space(DFT_NOR_USER_SPACE);
			if (usr_rec->start_addr != 0) {
				usr_rec->length = DFT_NOR_USER_SPACE;
				usr_rec->valid = 1;
				g_nor_part_hdr->rec_num++;

				dprintf(LOG_INF, "create: new part_rec %lx, length %ld\n\r", (uint32_t)usr_rec->start_addr, usr_rec->length);

				nor_pfw_update_ptable();
				fr->part_rec = usr_rec;
			}
		}
	}

	dprintf(LOG_INF, "open: part_rec %lx, type_id %x\n\r", (uint32_t)fr->part_rec, type_id);

	if (!fr->part_rec || fr->part_rec->valid == 0) {
		free(fr);
		return NULL;
	}


	//manifest_t *mani = (manifest_t *)NOR_ADDR(fr->part_rec->start_addr);
	manifest_t *mani = (manifest_t *)malloc(sizeof(manifest_t));
	if (!mani) {
		free(fr);
		return NULL;
	}
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)(fr->part_rec->start_addr), sizeof(manifest_t), (uint8_t *)mani));

	if (mode == M_NORMAL && memcmp(mani->lbl, manifest_valid_label, 8) == 0) {
		img_hdr_t imghdr;
		ATOMIC_CALL(flash_stream_read(&nor_flash, fr->part_rec->start_addr + 4096, sizeof(img_hdr_t), (uint8_t *)&imghdr));
		//img_hdr_t *imghdr = (img_hdr_t *)NOR_ADDR(fr->part_rec->start_addr + 4096);
		fr->manifest_valid = 1;
		//fr->content_len = tlv_get_value(mani->tlv_start, mani->tlv_end, ID_IMGSZ, &fr->content_len);
		fr->content_len = imghdr.imglen;//imghdr->imglen;
		fr->raw_offset = 4096 + sizeof(img_hdr_t);
	} else {
		fr->manifest_valid = 0;
		fr->content_len = fr->part_rec->length;
		fr->raw_offset = 0;
	}
	free(mani);

	return fr;
}

void *nor_pfw_open(const char *name, int mode)
{
	char name_dup[strlen(name) + 2];
	name_dup[strlen(name) + 1] = 0;
	strncpy(name_dup, name, strlen(name) + 1);

	char *file_name = name_dup;

	char *type_name = strsep(&file_name, "/");

	dprintf(LOG_INF, "type_name %s, file_name %s\n\r", type_name, file_name);


	uint16_t type_id = __get_pt_type_id(type_name);
	if (type_id == 0xffff)	{
		return NULL;
	}

	//dprintf(LOG_INF, "open fw partition %s type id %x\n\r", type_name, type_id);

	nor_fw_rec_t *fr = nor_pfw_open_by_typeid(type_id, mode);


	if (mode == M_NORMAL && file_name != NULL) {
		// search filename and update file size and raw offset
		fwfs_folder_t *tmp = malloc(sizeof(fwfs_folder_t));
		if (!tmp) {
			free(fr);
			return NULL;
		}

		nor_pfw_read(fr, tmp, sizeof(fwfs_folder_t));
		nor_pfw_seek(fr, 0, 3);
		//pfw_dump_mem(tmp, sizeof(fwfs_folder_t));
		if (strcmp(tmp->tag, "FWFSDIR") == 0) {
			//dprintf(LOG_INF, "FWFSDIR mode, file count %d\n\r", tmp->file_cnt);
			for (int i = 0; i < tmp->file_cnt; i++) {
				//dprintf(LOG_INF, "file[%d] %s\n\r", i, tmp->files[i].filename);
				if (strcmp(file_name, tmp->files[i].filename) == 0) {
					//dprintf(LOG_INF, "file %s, len %d\n\r", tmp->files[i].filename, tmp->files[i].filelen);
					fr->content_len = tmp->files[i].filelen;
					fr->raw_offset += tmp->files[i].offset;
					break;
				}
			}
		}
		free(tmp);
	}

	return fr;

}

void nor_pfw_close(void *fr)
{
	if (fr) {
		free(fr);
	}
}

int nor_pfw_tell(void *fr)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;
	if (!fr)	{
		return -1;
	}

	return r->curr_pos;
}

/* src dst len should align to 32byte*/
void memcpy32(void *dst, void *src, int len)
{
	__asm(
		"		push {r0-r12}				\n"
		"1:									\n"
		"		ldmia   r1!, {r4-r11}		\n"
		"		PLD [r1, #0]				\n"
		"		stmia   r0!, {r4-r11}		\n"
		"		PLD [r0, #0]				\n"
		"		subs    r2, r2, #32			\n"
		"		BGT   1b					\n"
		"		pop {r0-r12}				\n"
		"		bx lr						\n"
	);
}

#include "hal_flash.h"

static void nor_copy_read(void *dst, void *src, int len)
{
	extern hal_spic_adaptor_t hal_spic_adaptor;
	hal_spic_adaptor_t *phal_spic_adaptor = &hal_spic_adaptor;
	if ((phal_spic_adaptor->flash_id[2]) >= FLASH_ID_4ADDR) {
		hal_flash_enter_4byte_addr(phal_spic_adaptor);
	}
	if ((uint32_t)dst % 32 == 0 && (uint32_t)src % 32 == 0 && len % 32 == 0) {
		memcpy32(dst, src, len);
	} else {
		memcpy(dst, src, len);
	}
	if ((phal_spic_adaptor->flash_id[2]) >= FLASH_ID_4ADDR) {
		hal_flash_exit_4byte_addr(phal_spic_adaptor);
	}
}

int nor_pfw_read_normal(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	if (!data)	{
		return -1;
	}
	if (size == 0)	{
		return 0;
	}

	//uint32_t start_addr = r->part_rec->start_addr;
	//uint32_t max_length = r->part_rec->length;
	// copy to data

	uint8_t *curr_addr = (uint8_t *)NOR_ADDR(r->part_rec->start_addr + r->curr_pos + r->raw_offset);

	int rest_size = r->content_len - r->curr_pos;

	if (rest_size <= 0)	{
		return EOF;
	}

	if (rest_size < size) {
		size = rest_size;
	}

	//dprintf(LOG_INF, "dst %x src %x size %d\n\r", data, curr_addr, size);
	ATOMIC_CALL(nor_copy_read(data, curr_addr, size));
	//ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)r->part_rec->start_addr + r->curr_pos + r->raw_offset, size, data));

	r->curr_pos += size;

	return size;
}

int nor_pfw_update_flash(uint8_t *nor_addr, uint8_t *data, int size)
{
	// 4k(curr) | <---A--- | curr --B--- | 4k(curr)+4k
	// 4k(curr+size) | <---A--- | curr+size --B--- | 4k(curr+size)+4k
	// backup A section, backup B section

	uint32_t size_a = ((uint32_t)nor_addr) & (4095);
	//uint32_t size_b = 4096 - ((((uint32_t)nor_addr)+size)&(4095));

	uint8_t *addr_cpy;
	uint8_t *addr_a = nor_addr - size_a;
	//uint8_t *addr_b = nor_addr + size;

	uint8_t *data8 = (uint8_t *)data;

	uint8_t *tmp_buf = malloc(4096);
	if (!tmp_buf) {
		return 0;
	}

	addr_cpy = addr_a;
	// backup section abort
	if (size_a) {
		//int cpy_size = 4096 - size_a > size ? 4096 - size : size;
		int cpy_size = 4096 - size_a > size ? size : 4096 - size_a;
		//memcpy(tmp_buf, addr_cpy, 4096);
		ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)addr_cpy, 4096, tmp_buf));
		memcpy(&tmp_buf[size_a], data8, cpy_size);

		dcache_clean_invalidate_by_addr((uint32_t *)tmp_buf, 4096);
		// erase sector
		ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)addr_cpy));
		// write sector
		ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)addr_cpy, 4096, tmp_buf));

		size -= cpy_size;
		data8 += cpy_size;

		addr_cpy += 4096;
	}

	while (size >= 4096) {
		memcpy(tmp_buf, data8, 4096);

		dcache_clean_invalidate_by_addr((uint32_t *)tmp_buf, 4096);
		// erase sector
		ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)addr_cpy));
		// write sector
		ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)addr_cpy, 4096, tmp_buf));

		size -= 4096;
		data8 += 4096;
		addr_cpy += 4096;
	}

	if (size > 0) {
		//memcpy(tmp_buf, addr_cpy, 4096);
		ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)addr_cpy, 4096, tmp_buf));
		memcpy(tmp_buf, data8, size);

		dcache_clean_invalidate_by_addr((uint32_t *)tmp_buf, 4096);
		// erase sector
		ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)addr_cpy));
		// write sector
		ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)addr_cpy, 4096, tmp_buf));

		data8 += size;

		size -= size;
		//data8 += size;
		addr_cpy += size;
	}

	free(tmp_buf);

	return data8 - data;
}

int nor_pfw_write_normal(void *fr, void *data, int size)
{

	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	if (!data)	{
		return -1;
	}
	if (size == 0)	{
		return 0;
	}

	if (r->type_id != 0x78D1) {
		dprintf(LOG_ERR, "partition record is read only\n\r");
		return -1;
	}

	//uint32_t start_addr = r->part_rec->start_addr;
	//uint32_t max_length = r->part_rec->length;
	// copy to data

	//uint8_t *curr_addr = (uint8_t *)NOR_ADDR(r->part_rec->start_addr + r->curr_pos + r->raw_offset);
	uint8_t *curr_addr = (uint8_t *)(r->part_rec->start_addr + r->curr_pos + r->raw_offset);


	int ret_size = nor_pfw_update_flash(curr_addr, (uint8_t *)data, size);
	r->curr_pos += ret_size;

	return ret_size;

}

int nor_pfw_read_mani(void *fr, void *mani)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;
	//uint8_t *mani_nor = (uint8_t *)NOR_ADDR(r->part_rec->start_addr);

	//memcpy(mani, mani_nor, 4096);
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)r->part_rec->start_addr, 4096, mani));

	return 0;
}

int nor_pfw_write_mani(void *fr, void *mani)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;
	//uint8_t *mani_nor = (uint8_t *)NOR_ADDR(r->part_rec->start_addr);
	uint8_t *mani_nor = (uint8_t *)(r->part_rec->start_addr);

	// erase sector
	ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)mani_nor));
	// write sector
	ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)mani_nor, 4096, mani));

	return 0;
}

int nor_pfw_read_mani_unpt(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;
	//uint8_t *mani_nor = (uint8_t *)NOR_ADDR(r->part_rec->start_addr);

	if (size > 0x800)	{
		size = 0x800;
	}

	//dcache_invalidate_by_addr((uint32_t *)mani_nor, 4096);

	//memcpy(data, &mani_nor[0x800], size);
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)r->part_rec->start_addr + 0x800, size, data));
	return size;
}

int nor_pfw_write_mani_unpt(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;
	//uint8_t *mani_nor = (uint8_t *)NOR_ADDR(r->part_rec->start_addr);
	uint8_t *mani_nor = (uint8_t *)(r->part_rec->start_addr);

	uint8_t *tmp = malloc(4096);
	if (!tmp)	{
		return -1;
	}

	if (size > 0x800)	{
		size = 0x800;
	}

	//pfw_dump_mem(data, size);

	//memcpy(tmp, mani_nor, 0x1000);
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)mani_nor, 0x1000, tmp));
	memcpy(&tmp[0x800], data, size);

	//pfw_dump_mem(tmp, 32);
	//pfw_dump_mem(&tmp[0x800], 32);

	dcache_clean_by_addr((uint32_t *)tmp, 4096);
	// erase sector
	ATOMIC_CALL(flash_erase_sector(&nor_flash, (uint32_t)mani_nor));
	// write sector
	ATOMIC_CALL(flash_stream_write(&nor_flash, (uint32_t)mani_nor, 4096, tmp));

	free(tmp);

	return 0;
}

int nor_pfw_read_raw(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	if (!data)	{
		return -1;
	}
	if (size == 0)	{
		return 0;
	}

	//uint32_t start_addr = r->part_rec->start_addr;
	uint32_t max_length = r->part_rec->length;
	// copy to data

	//uint8_t *raw_addr = (uint8_t *)NOR_ADDR(r->part_rec->start_addr + r->curr_pos);
	//uint8_t *raw_4k = (uint8_t *)((uint32_t)raw_addr & (~4095));

	if (size > max_length) {
		size = max_length;
	}

	//dcache_invalidate_by_addr((uint32_t *)raw_4k, (size + 4059) & (~4095));
	//memcpy(data, raw_addr, size);
	ATOMIC_CALL(flash_stream_read(&nor_flash, (uint32_t)(r->part_rec->start_addr + r->curr_pos), size, data));

	r->curr_pos += size;

	return size;
}

int nor_pfw_write_raw(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	if (!data)	{
		return -1;
	}
	if (size == 0)	{
		return 0;
	}

	//uint32_t start_addr = r->part_rec->start_addr;
	uint32_t max_length = r->part_rec->length;
	// copy to data

	uint8_t *raw_addr = (uint8_t *)(r->part_rec->start_addr + r->curr_pos);

	if (r->curr_pos + size > max_length) {
		size = max_length - r->curr_pos;
	}

	int ret_size = nor_pfw_update_flash(raw_addr, data, size);
	r->curr_pos += ret_size;

	return ret_size;
}

int nor_pfw_read(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	switch (r->mode & 0xf) {
	case M_NORMAL:
		return nor_pfw_read_normal(fr, data, size);
	case M_MANI_UNPT:
		return nor_pfw_read_mani_unpt(fr, data, size);
	case M_RAW:
		return nor_pfw_read_raw(fr, data, size);
	}
	return 0;
}

int nor_pfw_write(void *fr, void *data, int size)
{
	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	switch (r->mode & 0xf) {
	case M_NORMAL:
		if (r->type_id != 0x78D1) {
			return -1;
		}
		return nor_pfw_write_normal(fr, data, size);
	case M_MANI_UNPT:
		return nor_pfw_write_mani_unpt(fr, data, size);
	case M_RAW:
		return nor_pfw_write_raw(fr, data, size);
	}
	return 0;
}

int nor_pfw_seek(void *fr, int offset, int pos)
{
	if (!fr)	{
		return -1;
	}

	nor_fw_rec_t *r = (nor_fw_rec_t *)fr;

	switch (pos) {
	case SEEK_SET:
		r->curr_pos = offset;

		break;
	case SEEK_CUR:

		r->curr_pos += offset;
		break;
	case SEEK_END:
		r->curr_pos = r->content_len - offset;

		break;
	}

	int max_pos = r->content_len;
	if (r->curr_pos < 0)	{
		r->curr_pos = 0;
	}
	if (r->curr_pos > max_pos) {
		r->curr_pos = max_pos;
	}

	return 0;

}

//--------------------------------------------------------------------------------------
// API interface
//--------------------------------------------------------------------------------------
typedef struct fwfs_interface_s {
	void (*init)(void);
	void (*deinit)(void);
	void (*list)(int mode);
	void *(*open_by_typeid)(uint16_t, int);
	void *(*open)(const char *, int);
	void (*close)(void *);
	int (*tell)(void *);
	int (*read)(void *, void *, int);
	int (*write)(void *, void *, int);
	int (*seek)(void *, int, int);

	int (*read_unpt)(void *, void *, int);
	int (*write_unpt)(void *, void *, int);

	int (*read_raw)(void *, void *, int);
	int (*write_raw)(void *, void *, int);
} fwfs_interface_t;

static fwfs_interface_t nand_fw = {
	.init   		= nand_pfw_init,
	.deinit 		= nand_pfw_deinit,
	.list			= nand_pfw_list,
	.open_by_typeid = nand_pfw_open_by_typeid,
	.open 			= nand_pfw_open,
	.close 			= nand_pfw_close,
	.tell 			= nand_pfw_tell,
	.read 			= nand_pfw_read,
	.write 			= nand_pfw_write,
	.seek 			= nand_pfw_seek,
	.read_unpt 		= nand_pfw_read_mani_unpt,
	.write_unpt		= nand_pfw_write_mani_unpt,
	.read_raw 		= nand_pfw_read_raw,
	.write_raw		= nand_pfw_write_raw,
};

static fwfs_interface_t nor_fw = {
	.init   		= nor_pfw_init,
	.deinit 		= nor_pfw_deinit,
	.list			= nor_pfw_list,
	.open_by_typeid = nor_pfw_open_by_typeid,
	.open 			= nor_pfw_open,
	.close 			= nor_pfw_close,
	.tell 			= nor_pfw_tell,
	.read 			= nor_pfw_read,
	.write 			= nor_pfw_write,
	.seek 			= nor_pfw_seek,
	.read_unpt 		= nor_pfw_read_mani_unpt,
	.write_unpt		= nor_pfw_write_mani_unpt,
	.read_raw 		= nor_pfw_read_raw,
	.write_raw		= nor_pfw_write_raw,
};


static fwfs_interface_t *curr = NULL;
void atcmd_pfw_init(void);
void pfw_init(void)
{
	if (sys_get_boot_sel() == 0) { // NOR
		curr = &nor_fw;
	} else if (sys_get_boot_sel() == 1) { // NAND
		curr = &nand_fw;
	} else {
		dprintf(LOG_ERR, "Cannot use flash firmware in this mode\n\t");
		while (1);
	}
	//atcmd_pfw_init();
	if (curr && curr->init) {
		curr->init();
	}
}

void pfw_deinit(void)
{
	if (curr && curr->deinit) {
		curr->deinit();
	}
}

void pfw_list(int mode)
{
	if (curr && curr->list) {
		curr->list(mode);
	}
}

void *pfw_open_by_typeid(uint16_t type_id, int mode)
{
	if (curr && curr->open_by_typeid) {
		return curr->open_by_typeid(type_id, mode);
	}
	return NULL;
}

void *pfw_open(const char *name, int mode)
{
	pfw_init();
	if (curr && curr->open) {
		return curr->open(name, mode);
	}
	return NULL;
}

void pfw_close(void *fr)
{
	if (curr && curr->close) {
		curr->close(fr);
	}
}

int pfw_tell(void *fr)
{
	if (curr && curr->tell) {
		return curr->tell(fr);
	}
	return 0;
}

int pfw_read(void *fr, void *data, int size)
{
	if (curr && curr->read) {
		return curr->read(fr, data, size);
	}
	return -1;
}

int pfw_write(void *fr, void *data, int size)
{
	if (curr && curr->write) {
		return curr->write(fr, data, size);
	}
	return -1;
}

int pfw_seek(void *fr, int offset, int pos)
{
	if (curr && curr->seek) {
		return curr->seek(fr, offset, pos);
	}
	return -1;
}

int pfw_read_unpt(void *fr, void *data, int size)
{
	if (curr && curr->read) {
		return curr->read_unpt(fr, data, size);
	}
	return -1;
}

int pfw_write_unpt(void *fr, void *data, int size)
{
	if (curr && curr->write) {
		return curr->write_unpt(fr, data, size);
	}
	return -1;
}

//--------------------------------------------------------------------------------------
// Test command
//--------------------------------------------------------------------------------------

void fLSFW(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);

	int mode = 0;
	if (argc == 2) {
		mode = strtol(argv[1], NULL, 10);
	}

	pfw_init();
	//pfw_list();
	pfw_list(mode);
}

void fDUMP(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);
	(void)argc;

	uint32_t addr = strtoul(argv[1], NULL, 16);
	uint32_t len = strtoul(argv[2], NULL, 16);

	pfw_dump_mem((void *)addr, len);
}

// FWRD=NN_MDL,seek_pos,read_len
void fFWRD(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);
	(void)argc;	// may use this

	pfw_init();
	void *fp = pfw_open(argv[1], M_RAW);
	if (!fp) {
		printf("cannot open file %s\n\r", argv[1]);
		return;
	}

	int offset = strtol(argv[2], NULL, 16);
	int rlen = strtol(argv[3], NULL, 10);

	uint8_t *tmp_buf = malloc(rlen + 32);
	if (!tmp_buf) {
		printf("out of memory\n\r");
		pfw_close(fp);
		return;
	}

	printf("offset %x, read len %d, target %lx\n\r", offset, rlen, (uint32_t)tmp_buf);

	pfw_seek(fp, offset, SEEK_SET);
	pfw_read(fp, tmp_buf, rlen);

	pfw_dump_mem(tmp_buf, rlen);

	pfw_close(fp);
	free(tmp_buf);
}

void fFWWT(void *arg)
{
	unsigned int crc32_result[10] = {0xd202ef8d, 0xa505df1b, 0x3c0c8ea1, 0x4b0bbe37, 0xd56f2b94, 0xa2681b02, 0x3b614ab8, 0x4c667a2e, 0xdcd967bf, 0xabde5729};
	pfw_init();

#if 0
	void *fp = pfw_open_by_typeid(0x89CE, M_MANI_UNPT);

	uint8_t *ref = malloc(4096);
	uint8_t *tmp = malloc(4096);

	pfw_read_unpt(fp, ref, 12);
	pfw_dump_mem(ref, 12);

	ref[4] = 1;
	*(uint32_t *)&ref[8] = crc32_result[ref[4]];

	pfw_write_unpt(fp, ref, 12);

	pfw_read_unpt(fp, tmp, 12);
	pfw_dump_mem(tmp, 12);

	pfw_close(fp);
#else
	void *fp = pfw_open("ISP_IQ", M_MANI_UNPT);

	uint8_t *ref = malloc(4096);
	uint8_t *tmp = malloc(4096);

	pfw_read(fp, ref, 12);
	pfw_dump_mem(ref, 12);

	ref[4] = 1;
	*(uint32_t *)&ref[8] = crc32_result[ref[4]];

	pfw_write(fp, ref, 12);

	pfw_read(fp, tmp, 12);
	pfw_dump_mem(tmp, 12);

	pfw_close(fp);
#endif

}


void fFWW2(void *arg)
{
	pfw_init();

	void *fp = pfw_open("UDATA", M_RAW | M_CREATE);

	uint8_t *ref = malloc(4096);
	uint8_t *tmp = malloc(4096);

	memset(ref, 0, 4096);
	memset(tmp, 0, 4096);

	int wr_status = 0;
	int rd_status = pfw_read(fp, ref, 128);
	pfw_seek(fp, 0, SEEK_SET);

	printf("read ret = %d\n\r", rd_status);
	pfw_dump_mem(ref, 128);


	memset(ref, 0x5a, 128);
	wr_status = pfw_write(fp, ref, 128);
	pfw_seek(fp, 0, SEEK_SET);

	rd_status = pfw_read(fp, tmp, 128);
	printf("read ret = %d, write status = %d\n\r", rd_status, wr_status);
	pfw_dump_mem(tmp, 128);

	pfw_close(fp);
}

void fFWRT(void *arg)
{
	//int argc = 0;
	//char *argv[MAX_ARGC] = {0};
	//argc = parse_param(arg, argv);

	pfw_init();

	void *fp = pfw_open_by_typeid(0xC1C7, 0);

	uint8_t *ref = malloc(4096);
	uint8_t *tmp = malloc(4096);

	pfw_read(fp, ref, 2048);
	pfw_read(fp, &ref[2048], 2048);

	//pfw_dump_mem(ref, 4096);

	// test seek and internal tmp_page read
	pfw_seek(fp, 0, SEEK_SET);
	pfw_read(fp, tmp, 4096);
	//pfw_dump_mem(tmp, 4096);
	if (memcmp(ref, tmp, 4096) != 0) {
		printf("test 1 not match\n\r");
		if (memcmp(ref, tmp, 2048) != 0) {
			pfw_dump_mem(ref, 2048);
			pfw_dump_mem(tmp, 2048);
		}
		if (memcmp(&ref[2048], &tmp[2048], 2048) != 0) {
			pfw_dump_mem(&ref[2048], 2048);
			pfw_dump_mem(&tmp[2048], 2048);
		}
	} else {
		printf("test 1 matched\n\r");
	}

	// small size read
	int bi = 0;
	pfw_seek(fp, 0, SEEK_SET);
	pfw_read(fp, &tmp[bi], 1);
	bi += 1;
	pfw_read(fp, &tmp[bi], 1);
	bi += 1;
	pfw_read(fp, &tmp[bi], 1);
	bi += 1;
	pfw_read(fp, &tmp[bi], 1);
	bi += 1;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 64);
	bi += 64;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 4);
	bi += 4;
	pfw_read(fp, &tmp[bi], 256);
	bi += 256;


	if (memcmp(ref, tmp, bi) != 0) {
		printf("test 1-1 not match\n\r");
	} else {
		printf("test 1-1 matched\n\r");
	}

	// test under byte read
	pfw_seek(fp, 0, SEEK_SET);
	for (int i = 0; i < 4096; i += 8) {
		pfw_read(fp, &tmp[i], 8);
	}

	if (memcmp(ref, tmp, 4096) != 0) {
		printf("test 2 not match\n\r");
	} else {
		printf("test 2 matched\n\r");
	}


	// test cross page read
	pfw_seek(fp, 2045, SEEK_SET);
	pfw_read(fp, tmp, 8);

	if (memcmp(&ref[2045], tmp, 8) != 0) {
		printf("test 3 not match\n\r");
	} else {
		printf("test 3 matched\n\r");
	}

	// test cross block read
	pfw_seek(fp, 63 * 2048, SEEK_SET);

	pfw_read(fp, ref, 2048);
	pfw_read(fp, &ref[2048], 2048);

	//pfw_dump_mem(ref, 4096);

	pfw_seek(fp, 63 * 2048, SEEK_SET);
	pfw_read(fp, tmp, 4096);

	if (memcmp(ref, tmp, 4096) != 0) {
		printf("test 4 not match\n\r");
	} else {
		printf("test 4 matched\n\r");
	}


	// test cross page read
	pfw_seek(fp, 63 * 2048 + 2045, SEEK_SET);
	pfw_read(fp, tmp, 8);

	if (memcmp(&ref[2045], tmp, SEEK_SET) != 0) {
		printf("test 5 not match\n\r");
	} else {
		printf("test 5 matched\n\r");
	}

	// test huge data size read
	free(ref);
	free(tmp);

	ref = malloc(256 * 1024 + 32);
	tmp = malloc(256 * 1024 + 32);

	pfw_seek(fp, 0, SEEK_SET);
	for (int i = 0; i < 256 * 1024; i += 2048) {
		pfw_read(fp, &ref[i], 2048);
	}


	pfw_seek(fp, 0, SEEK_SET);
	pfw_read(fp, tmp, 256 * 1024);

	//pfw_dump_mem(&ref[128*1024], 2048);
	//pfw_dump_mem(&tmp[128*1024], 2048);

	if (memcmp(ref, tmp, 256 * 1024) != 0) {
		printf("test 6 not match\n\r");
	} else {
		printf("test 6 matched\n\r");
	}

	pfw_seek(fp, 2048, SEEK_SET);
	pfw_read(fp, tmp, 128 * 1024);

	if (memcmp(&ref[2048], tmp, 128 * 1024) != 0) {
		printf("test 7 not match\n\r");
		for (int i = 0; i < 128 * 1024; i += 2048) {
			if (memcmp(&ref[2048 + i], &tmp[i], 2048) != 0) {
				printf("test 7.(%x) not match\n\r", i / 2048);
			}
		}
	} else {
		printf("test 7 matched\n\r");
	}

	int pos = pfw_tell(fp);

	pfw_seek(fp, 123, SEEK_CUR);
	pfw_read(fp, tmp, 2049);

	if (memcmp(&ref[pos + 123], tmp, 2049) != 0) {
		printf("test 8 not match\n\r");
	} else {
		printf("test 8 matched\n\r");
	}

	free(ref);
	free(tmp);

	pfw_close(fp);
}

void fNAND(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);

	int blk = 0;
	if (argc == 2) {
		blk = strtol(argv[1], NULL, 10);
	}

	snand_init(&flash);

	uint8_t *tmp = malloc(2048 + 32);

	snand_page_read(&flash, blk, 2048 + 32, tmp);
	pfw_dump_mem(tmp, 2048 + 32);

	free(tmp);
}

log_item_t pfw_items[] = {
	{"LSFW", fLSFW,},
	{"FWWT", fFWWT,},
	{"FWW2", fFWW2,},
	{"FWRT", fFWRT,},
	{"FWRD", fFWRD,},
	{"DUMP", fDUMP,},
	{"NAND", fNAND,},
};

void atcmd_pfw_init(void)
{
	log_service_add_table(pfw_items, sizeof(pfw_items) / sizeof(pfw_items[0]));
}
