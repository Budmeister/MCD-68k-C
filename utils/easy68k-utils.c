
#include "68k.h"
#include <stdarg.h>

void print(const char* str) {
    __asm__("
        moveq.l  #14, %d0
        move.l  4(%sp), %a1
        trap #15
    ");
}

bool available() {
    __asm__("
        moveq.l #7, %d0
        trap    #15
        moveq.l #0, %d0
        move.b  %d1, %d0
    ");
}

char getcb() {
    __asm__("
        moveq.l #5, %d0
        trap    #15
        moveq.l #0, %d0
        move.b  %d1, %d0
    ");
}

char getc() {
    if(available())
        return getcb();
    return -1;
}

void echo(bool e) {
    __asm__("
        move.b  7(%sp), %d1
        moveq.l #12, %d0
        trap    #15
    ");
}
