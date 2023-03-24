
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"

#define COMMAND_BUFSIZE 20
unsigned char command[COMMAND_BUFSIZE];

void myfunc() {

}

void print_regs();
void pause(char* msg);


int main() {
    unsigned char** words;
    usize_t num_words, i;
    while(1) {
        /* printf("Enter your command: "); */
        getl(command, COMMAND_BUFSIZE);
        printf("Command %s received\r\n", command);
        /* printf("%s\r", command); */
        words = splitw(command, &num_words);
        
        printf("Regs: \r\n");
        print_regs(getregs());

        free(words);
        print_malloc_status();
    }
    return 0;
}

void print_regs(struct reg68k regs) {
    printf("D0: %x\r\n", regs.d0);
    printf("D1: %x\r\n", regs.d1);
    printf("D2: %x\r\n", regs.d2);
    printf("D3: %x\r\n", regs.d3);
    printf("D4: %x\r\n", regs.d4);
    printf("D5: %x\r\n", regs.d5);
    printf("D6: %x\r\n", regs.d6);
    printf("D7: %x\r\n", regs.d7);
    printf("A0: %p\r\n", regs.a0);
    printf("A1: %p\r\n", regs.a1);
    printf("A2: %p\r\n", regs.a2);
    printf("A3: %p\r\n", regs.a3);
    printf("A4: %p\r\n", regs.a4);
    printf("A5: %p\r\n", regs.a5);
    printf("A6: %p\r\n", regs.a6);
    printf("A7: %p\r\n", regs.a7);
    printf("PC: %p\r\n", regs.pc);
}

void pause(char* msg) {
    printf("%s\r\n", msg);
    printf("Change D0 to 00000000 to continue\r\n");
    __asm__("
        move.l #1,%d0
    .startloop:
        tst %d0
        bne .startloop
    ");
}