#include "io.h"
#include "string.h"
#include "srec.h"
#include "malloc.h"
#include "supervisor.h"

/* Tests: s-record.s19 */

usize_t (*loaded_program)(usize_t, char**);


usize_t run_program_as_user(usize_t argc, unsigned char** argv, void* start) {
    if(start != NULL)
        loaded_program = start;
    __asm__("andi.w #0xdfff,%sr");     /* 57343 == 0b110111111111*/
    loaded_program(argc, argv);
    __asm__("trap #4");             /* Call trap after user program finishes*/
    __asm__("user_program_finished:");
}

void err_trap4() {
    __asm__("ori.w #0x2000,(%sp)");
    __asm__("move.l #user_program_finished,2(%sp)");
    __asm__("rte");
}


void load_srec() {
    uint8_t cur_char, record_type, addr_size, checksum, checksum_given;
    uint32_t line_num = 1;
    uint8_t *addr, *data;
    unsigned char str_buf[9];
    usize_t i, length;

    while(1) {
        /* Record type */
        do{
            cur_char = getcb();
        } while(cur_char == '\r');
        if(cur_char == 4)
            break;
        if(cur_char != 'S') {
            printf("Invalid start of line: <%x,%c>\r\n", cur_char, cur_char);
            break;
        }
        checksum = 0;
        cur_char = getcb();
        if(cur_char < '0' || cur_char > '9' || cur_char == '4') {
            printf("Invalid record type: %c\r\n", cur_char);
            break;
        }
        record_type = cur_char - '0';

        /* Record length */
        str_buf[0] = getcb();
        str_buf[1] = getcb();
        str_buf[2] = '\0';
        length = stoi(str_buf);
        checksum+=length;

        switch(record_type) {
            case 0:
            case 1:
            case 5:
            case 9:
                addr_size = 4;
                break;
            case 2:
            case 6:
            case 8:
                addr_size = 6;
                break;
            case 3:
            case 7:
                addr_size = 8;
                break;
        }
        for(i = 0; i < addr_size; i+=2) {
            str_buf[i] = getcb();
            str_buf[i+1] = getcb();
            str_buf[i+2] = '\0';
            checksum+=stoi(&str_buf[i]);
        }
        addr = (uint8_t*) stoi(str_buf);
        length-=addr_size/2+1;
        data = malloc(length+1);    /* length+1 for S0 which prints it as a string adds the null character */
        if(data == NULL) {
            printf("Malloc error on line %d\r\n", line_num);
            print_malloc_status();
            return;
        }
        str_buf[2] = '\0';
        for(i = 0; i < length; i++) {
            str_buf[0] = getcb();
            str_buf[1] = getcb();
            data[i] = stoi(str_buf);
            checksum += data[i];
        }
        data[length] = '\0';
        str_buf[0] = getcb();
        str_buf[1] = getcb();
        checksum_given = stoi(str_buf);
        if((uint8_t) (checksum + checksum_given + 1) != 0) {
            printf("Invalid checksum on line %d. %x calculated but %x given.\r\n", line_num, 0xFF - checksum, checksum_given);
            free(data);
            line_num++;
            continue;
        }

        switch(record_type) {
            case 0:
                printf("%s\r\n", data);
                break;
            case 1:
            case 2:
            case 3:
                for(i = 0; i < length; i++) {
                    if(is_user(addr))
                        *addr = data[i];
                    else
                        printf("Cannot write %x to %p on line %d. S-Records can only be written to user space.\r\n", data[i], addr, line_num);
                    addr++;
                }
                break;
            case 7:
            case 8:
            case 9:
                loaded_program = (void*) addr;
                printf("Program entry point: %p\r\n", addr);
                printf("%d lines loaded\r\n", line_num);
        }
        free(data);
        if(line_num % 10 == 0)
            printf("%d lines loaded\r\n", line_num);
        line_num++;
    }
}

