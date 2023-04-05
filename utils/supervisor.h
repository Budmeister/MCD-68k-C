#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "68k.h"

#define ROM_START   0x000000
#define ROM_END     0x004fff
#define RAM_START   0x010000
#define RAM_END     0x020000
#define DUART_START 0x020000
#define DUART_END   0x020020
#define USER_START  0x014000
#define USER_END    0x020000

bool is_rom(void* ptr);
bool is_ram(void* ptr);
bool is_duart(void* ptr);
bool is_user(void* ptr);
bool is_printable(unsigned char c);

#endif