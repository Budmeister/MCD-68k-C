

#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"
#include "utils/srec.h"
#include "utils/supervisor.h"

#define COMMAND_BUFSIZE 20
unsigned char command_buf[COMMAND_BUFSIZE];
#define IFF if(false)

void run_command(usize_t argc, unsigned char** argv);

void pause(char* msg);
void memory_display(usize_t argc, unsigned char** argv);
void memory_modify(usize_t argc, unsigned char** argv);
void reg(usize_t argc, unsigned char** argv);
void print_regs(struct reg68k regs);
void load_prog(usize_t argc, unsigned char** argv);
void run_prog(usize_t argc, unsigned char** argv);
void help(usize_t argc, unsigned char** argv);

/*
 * md - Memory Display
 * mm - Memory Modify
 * reg - Print Registers
 * reg D0 fedcba98 - Write fedcba98 to D0
 * load 014000 - Load program with launch location 014000
 * run - Run program
 */

struct reg68k current_regs;
void* program_location;

int main() {
    unsigned char** argv;
    usize_t argc;
    /* Init Duart */
#ifndef SIM
    select_channel(CHANNEL_A);
    duart_init(MODE_RX_INT_RXRDY | MODE_ERR_MODE_CHAR | MODE_NO_PARITY | MODE_PARITY_EVEN | MODE_8_BIT_CHAR);
    duart_update_mode(MODE_ECHO_NORMAL | MODE_BIT_LENGTH_1);
    set_baud(BAUD_19200);    /* This writes the correct byte for 9600 (0xBB), but for some reason it transmits and receives at 7200 */
    command(ENABLE_TX | ENABLE_RX);

    /* echo(MODE_ECHO_AUTO); */
#else
    echo(false);
#endif

    program_location = (void*) 0x0000c0;
    /* Main Loop */
    while(1) {
        printf("turtle> ");
        current_regs = getregs();
        getl(command_buf, COMMAND_BUFSIZE);
        printf("\r");
        argv = splitw(command_buf, &argc);
        if(argc != 0) {
            run_command(argc, argv);
        }

        free(argv);
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

void run_command(usize_t argc, unsigned char** argv) {
    if(!strcmp(argv[0], "md")) {
        memory_display(argc, argv);
    } else if(!strcmp(argv[0], "mm")) {
        memory_modify(argc, argv);
    } else if(!strcmp(argv[0], "reg")) {
        reg(argc, argv);
    } else if(!strcmp(argv[0], "load")) {
        load_prog(argc, argv);
    } else if(!strcmp(argv[0], "run")) {
        run_prog(argc, argv);
    } else if(!strcmp(argv[0], "malloc")) {
        print_malloc_status();
    } else if(!strcmp(argv[0], "help")) {
        help(argc, argv);
    } else {
        help(argc, argv);
    }
}

void memory_display(usize_t argc, unsigned char** argv) {
    uint8_t* ptr;
    uint8_t i, j;
    /* Arg checking */
    if(argc != 2) {
        printf("Usage: %s [address]\r\n", argv[0]);
        return;
    }
    ptr = (uint8_t*) stoi(argv[1]);
    if(ptr == 0) {
        printf("Invalid address: %s\r\n", argv[1]);
        return;
    }
    /* Start memory_display */
    ptr = (uint8_t*) ((usize_t) ptr & 0xfffffff0);
    printf("            00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 0123456789ABCDEF\r\n");
    for(i = 0; i < 16; i++) {
        printf("%p: ", ptr);
        for(j = 0; j < 16; j++) {
            if(is_rom(ptr) || is_ram(ptr))
                if(*ptr < 0x10)
                    printf("0%x ", *ptr);
                else
                    printf("%x ", *ptr);
            else
                printf("?? ");
            ptr++;
        }
        ptr-=16;
        for(j = 0; j < 16; j++) {
            if((is_rom(ptr) || is_ram(ptr)) && is_printable(*ptr))
                printf("%c", *ptr);
            else
                printf("-");
            ptr++;
        }
        printf("\r\n");
    }
    /* TODO */
}

void memory_modify(usize_t argc, unsigned char** argv) {
    uint8_t *ptr;
    unsigned char* buf;
    /* Arg checking */
    if(argc != 2) {
        printf("Usage: %s [address]\r\n", argv[0]);
        return;
    }
    ptr = (uint8_t*) stoi(argv[1]);
    if(ptr == 0) {
        printf("Invalid address: %s\r\n", argv[1]);
        return;
    }
    /* Start memory_modify */
    while(1) {
        if(!is_ram(ptr)) {
            printf("Address %p not writable\r\n", ptr);
            break;
        }
        printf("%p(%x): ", ptr, *ptr);
        buf = getla(3);
        if(strlen(buf) == 0) {
            free(buf);
            break;
        }
        *ptr = stoi(buf);
        ptr++;
        free(buf);
        printf("\r\n");
    }
}

void reg(usize_t argc, unsigned char** argv) {
    uint32_t val;
    if(argc == 1) {
        print_regs(current_regs);
    } else if(argc == 3) {
        /* Load regs */
        val = stoi(argv[2]);
        if(!strcmp(argv[1], "D0") || !strcmp(argv[1], "d0")) {
            __asm__("move.l 4(%sp),%d0");
        } else if(!strcmp(argv[1], "D1") || !strcmp(argv[1], "d1")) {
            __asm__("move.l 4(%sp),%d1");
        } else if(!strcmp(argv[1], "D2") || !strcmp(argv[1], "d2")) {
            __asm__("move.l 4(%sp),%d2");
        } else if(!strcmp(argv[1], "D3") || !strcmp(argv[1], "d3")) {
            __asm__("move.l 4(%sp),%d3");
        } else if(!strcmp(argv[1], "D4") || !strcmp(argv[1], "d4")) {
            __asm__("move.l 4(%sp),%d4");
        } else if(!strcmp(argv[1], "D5") || !strcmp(argv[1], "d5")) {
            __asm__("move.l 4(%sp),%d5");
        } else if(!strcmp(argv[1], "D6") || !strcmp(argv[1], "d6")) {
            __asm__("move.l 4(%sp),%d6");
        } else if(!strcmp(argv[1], "D7") || !strcmp(argv[1], "d7")) {
            __asm__("move.l 4(%sp),%d7");
        } else if(!strcmp(argv[1], "A0") || !strcmp(argv[1], "a0")) {
            __asm__("move.l 4(%sp),%a0");
        } else if(!strcmp(argv[1], "A1") || !strcmp(argv[1], "a1")) {
            __asm__("move.l 4(%sp),%a1");
        } else if(!strcmp(argv[1], "A2") || !strcmp(argv[1], "a2")) {
            __asm__("move.l 4(%sp),%a2");
        } else if(!strcmp(argv[1], "A3") || !strcmp(argv[1], "a3")) {
            __asm__("move.l 4(%sp),%a3");
        } else if(!strcmp(argv[1], "A4") || !strcmp(argv[1], "a4")) {
            __asm__("move.l 4(%sp),%a4");
        } else if(!strcmp(argv[1], "A5") || !strcmp(argv[1], "a5")) {
            __asm__("move.l 4(%sp),%a5");
        } else if(!strcmp(argv[1], "A6") || !strcmp(argv[1], "a6")) {
            __asm__("move.l 4(%sp),%a6");
        } else if(!strcmp(argv[1], "A7") || !strcmp(argv[1], "a7")) {
            __asm__("move.l 4(%sp),%a7");
        }
    } else {
        printf("Usage: %s\r\n", argv[0]);
        printf("Usage: %s [reg] [value]\r\n", argv[0]);
    }
}

void load_prog(usize_t argc, unsigned char** argv) {
    /* Arg checking */
    if(argc != 1) {
        printf("Usage: %s\r\n", argv[0]);
        return;
    }
    /* Start load_program */
    printf("Loading program\r\n");
    load_srec();
    /* TODO */
}

void run_prog(usize_t argc, unsigned char** argv) {
    if(argc != 1) {
        printf("Usage: %s\r\n", argv[0]);
        return;
    }
    run_program_as_user(NULL);
}

void help(usize_t argc, unsigned char** argv) {
    printf(
        "\r\n"
        "\trom                000000-010000\r\n"
        "\tram                010000-020000\r\n"
        "\r\n"
        "\tmd                 Memory Display\r\n"
        "\tmm                 Memory Modify\r\n"
        "\treg                Print Registers\r\n"
        "\treg D0 fedcba98    Write fedcba98 to D0\r\n"
        "\tload               Load S-Record\r\n"
        "\trun                Run program\r\n"
        "\tmalloc             Print malloc status\r\n"
        "\thelp               Print this help message\r\n"
        "\r\n"
    );
}

void err_bus() {
    register uint32_t num = 0;
    printf("Bus error\r\n");
    /* print_regs(getregs()); */
    __asm__("move.w 4(%sp), %d2");
    printf("R/W(%d) I/N(%d) FC(%d%d%d)\r\n", !!(num&0x10), !!(num&0x8), !!(num&0x4), !!(num&0x2), !!(num&0x1));
    __asm__("move.l 6(%sp), %d2");
    printf("Access Address, %p\r\n", (void*) num);
    __asm__("move.w 10(%sp), %d2");
    printf("Instruction Register: %x\r\n", num);
    __asm__("move.w 12(%sp), %d2");
    printf("Status Register: %x\r\n", num);
    __asm__("move.l 14(%sp), %d2");
    printf("Program Counter: %x\r\n", num);
    while(1);
}

void err_addr() {
    register uint32_t num = 0;
    printf("Address error\r\n");
    /* print_regs(getregs()); */
    __asm__("move.w 4(%sp), %d2");
    printf("R/W(%d) I/N(%d) FC(%d%d%d)\r\n", !!(num&0x10), !!(num&0x8), !!(num&0x4), !!(num&0x2), !!(num&0x1));
    __asm__("move.l 6(%sp), %d2");
    printf("Access Address, %p\r\n", (void*) num);
    __asm__("move.w 10(%sp), %d2");
    printf("Instruction Register: %x\r\n", num);
    __asm__("move.w 12(%sp), %d2");
    printf("Status Register: %x\r\n", num);
    __asm__("move.l 14(%sp), %d2");
    printf("Program Counter: %x\r\n", num);
    while(1);
}

void err_illegal() {
    printf("Illegal operation error\r\n");
    while(1);
}

void err_divzero() {
    printf("Divide by zero error\r\n");
    while(1);
}

#ifdef SIM
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
#endif
