#include "68k.h"

struct reg68k getregs() {
    /* uint32_t d0, d1, d2, d3, d4, d5, d6, d7, a0, a1, a2, a3, a4, a5, a6, a7, pc; */
    struct reg68k regs;
    /* Move %ccr to 7(%sp) somehow */
    __asm__("
        movem.l %d0-%d7/%a0-%a7,8(%sp)
        move.l 76(%sp),72(%sp)
    ");
    return regs;
}
