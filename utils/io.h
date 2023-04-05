#ifndef IO_H
#define IO_H

#include "68k.h"
#ifdef SIM
#include "easy68k-utils.h"
#else
#include "duart.h"
#endif

void print_char(char c);
void print_hex(uint32_t num);
void print_dec(int32_t num);
void print_ptr(void* ptr);
void printf(const char* format, ...);
void getl(unsigned char* buf, usize_t bufsize);
unsigned char* getla(usize_t bufsize);

#endif