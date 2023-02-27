#ifndef MALLOC_H
#define MALLOC_H

#include "68k.h"

void* malloc(usize_t len);
void free(void* ptr);
void print_malloc_status();

#endif