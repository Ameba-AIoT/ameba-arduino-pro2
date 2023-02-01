/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2017 - 2022 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _GC_VIP_VERSION_H
#define _GC_VIP_VERSION_H

/*
VIPLite compatible NBG format version defines.
VIPLite supports forward compatibility with NBG format, which means that the NBG format version
smaller than NBG_VERSION can be supported by this driver.
*/
#define NBG_VERSION_MAJOR(x) ((x & 0xFFFF) << 16)
#define NBG_VERSION_MINOR(x) ((x & 0xFFFF) << 0)

#define NBG_VERSION          (NBG_VERSION_MAJOR(1) | NBG_VERSION_MINOR(0x14))


/*
VIPLite driver version number defines.
*/
#define VERSION_MAJOR		1

#define VERSION_MINOR		8

#define VERSION_SUB_MINOR	0

/* a string for patch version number defines */
#define VERSION_PATCH           "0"

#endif
