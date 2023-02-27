
#ifndef _68K_UTILS_H
#define _68K_UTILS_H

#define int8_t      char
#define uint8_t     unsigned char
#define int16_t     short
#define uint16_t    unsigned short
#define int32_t     int
#define uint32_t    unsigned int

#define bool        uint8_t
#define true        1
#define false       0

#define MAX_INT8    0x7f
#define MIN_INT8    0x80
#define MAX_UINT8   0xff
#define MAX_INT16   0x7fff
#define MIN_INT16   0x8000
#define MAX_UINT16  0xffff
#define MAX_INT32   0x7fffffff
#define MIN_INT32   0x80000000
#define MAX_UINT32  0xffffffff

#define size_t      int32_t
#define usize_t     uint32_t
#define MAX_SIZE    MAX_INT32
#define MIN_SIZE    MIN_INT32
#define MAX_USIZE   MAX_UINT32

#define NULL        0

#endif
