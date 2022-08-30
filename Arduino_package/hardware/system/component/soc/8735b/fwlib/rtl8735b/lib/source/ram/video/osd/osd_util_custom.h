#ifndef OSD_UTIL_CUSTOM_H
#define OSD_UTIL_CUSTOM_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#include "hal_osd_util.h"


typedef void (*func_write_bmp)(BITMAP_S *dst, BITMAP_S *src, rt_font_st *font, int start_loc, int width);

// NOTE:
//  osd_text_update_xxx() are quick functions,
//  they equal to 'osd_text_set_xxx() + osd_text_update()'
//
void	osd_text_get_xy_custom(osd_text_st *p, u32 *x, u32 *y);
void	osd_text_set_xy_custom(osd_text_st *p, u32 x, u32 y);
void	osd_text_set_str_custom(osd_text_st *p, char *str);
// Caution!
//  only these rt_font_st fields are used:
//  bg_enable, bg_color, ch_color, block_alpha, h_gap, v_gap
//
void	osd_text_set_font_custom(osd_text_st *p, rt_font_st *font);
void	osd_text_set_rotate_custom(osd_text_st *p, rt_rotate_t rotate);

int		osd_text_update_xy_custom(osd_text_st *p, u32 x, u32 y, BOOL ready2update);
int		osd_text_update_str_custom(osd_text_st *p, char *str, BOOL ready2update);
int		osd_text_update_font_custom(osd_text_st *p, rt_font_st *font_attr, BOOL ready2update);
int		osd_text_update_rotate_custom(osd_text_st *p, rt_rotate_t rotate, BOOL ready2update);

int		osd_text_update_custom(osd_text_st *p, BOOL ready2update);

int		osd_text_show_custom(osd_text_st *p);
int		osd_text_hide_custom(osd_text_st *p);

BOOL	osd_text_is_inited_custom(osd_text_st *p);

int		osd_pict_update_custom(osd_pict_st *p, BOOL ready2update);

int		osd_pict_show_custom(osd_pict_st *p);
int		osd_pict_hide_custom(osd_pict_st *p);

void *_fontlib_get(fontlib_e n, unsigned char *eng_bin, unsigned char *chi_bin);

#endif	// OSD_UTIL_CUSTOM_H
