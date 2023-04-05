#include "supervisor.h"
#include "68k.h"

bool is_rom(void* ptr) {
    return (usize_t) ptr >= ROM_START && (usize_t) ptr < ROM_END;
}

bool is_ram(void* ptr) {
    return (usize_t) ptr >= RAM_START && (usize_t) ptr < RAM_END;
}

bool is_duart(void* ptr) {
    return (usize_t) ptr >= DUART_START && (usize_t) ptr < DUART_END && (usize_t) ptr & 1;
}

bool is_user(void* ptr) {
    return (usize_t) ptr >= USER_START && (usize_t) ptr < USER_END;
}

bool is_printable(unsigned char c) {
    return c >= ' ' && c <= '~';
}