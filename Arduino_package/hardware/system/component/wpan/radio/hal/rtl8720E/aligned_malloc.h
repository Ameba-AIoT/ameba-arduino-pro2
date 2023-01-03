/*
 * mallocAlign.h
 *
 *  Created on: 2022��3��22��
 *      Author: yan_jia
 */

#ifndef _ALIGNED_MALLOC_H_
#define _ALIGNED_MALLOC_H_

void *aligned_malloc(unsigned int size, unsigned int align);
void aligned_free(void *p);

#endif /*  */
