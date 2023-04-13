
#include "io.h"
#include "68k.h"
#include "string.h"
#include "malloc.h"
#include <stdarg.h>
#ifdef SIM
#include "easy68k-utils.h"
#else
#include "duart.h"
#endif


#ifdef CLRF
#define isnewline(c1, c2) (c1 == '\n' && c2 == '\r')
#define replacenl(str, i2, replace) str[i2-1] = replace
#else
#ifdef SIM
#define isnewline(c1, c2) (c2 == '\r')
#else
#define isnewline(c1, c2) (c2 == 13)
#endif
#define replacenl(str, i2, replace) str[i2] = replace
#endif
#define NL '\r'

void print_char(char c) {
    uint16_t str;
    str = c;
    str = str << 8;
    print((char*) &str);
}

void print_hex(uint32_t num) {
    /* 4 bytes = 8 nibbles */
    bool nonzero = false;
    uint8_t shift = 32, cur_nibble;
    while(shift > 0) {
        shift-=4;
        cur_nibble = (num >> shift) & 0x0f;
        if(cur_nibble || shift == 0)
            nonzero = true;
        if(!nonzero)
            continue;
        if(cur_nibble < 10) {
            print_char(cur_nibble + (char) '0');
        }else{
            print_char(cur_nibble + (char) 'a' - 10);
        }
    }
}

void print_dec(int32_t num) {
    const int32_t powers[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    int32_t digit;
    uint8_t power;
    bool nonzero = false;
    if(num < 0) {
        if(num == MIN_INT32) {
            print("-2147483648");
            return;
        }
        print_char('-');
        num = -num;
    }
    power = 10;
    while(power --> 0) {
        digit = (num / powers[power]) % 10;
        if(digit || power == 0)
            nonzero = true;
        if(!nonzero)
            continue;
        print_char(digit + '0');
    }
}

void print_ptr(void* num) {
    uint8_t shift = 32, cur_nibble;
    print("0x");
    /* 4 bytes = 8 nibbles */
    while(shift > 0) {
        shift-=4;
        cur_nibble = ((uint32_t) num >> shift) & 0x0f;
        if(cur_nibble < 10) {
            print_char(cur_nibble + (char) '0');
        }else{
            print_char(cur_nibble + (char) 'a' - 10);
        }
    }
}

void printf(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    print_char(va_arg(arguments, char));
                    break;
                case 'x':
                    print_hex(va_arg(arguments, uint32_t));
                    break;
                case 'd':
                    print_dec(va_arg(arguments, int32_t));
                    break;
                case 'p':
                    print_ptr(va_arg(arguments, void *));
                    break;
                case 's':
                    print(va_arg(arguments, char *));
                    break;
                default:
                    break;
            }
        }
        else {
            print_char(*format);
        }
        format++;
    }
    va_end(arguments);
}

void getl(unsigned char* buf, usize_t bufsize) {
    usize_t i;
    for(i = 0; i < bufsize-1; i++) {
        buf[i] = getcb();
        if(buf[i] == NL) {
            buf[i] = '\0';
            break;
        }
        if(buf[i] == '\0')
            break;
        if(buf[i] == '\b') {
            if(i > 0) {
                print("\b \b");
                i--;
                i--;
            } else
                i--;
            continue;
        }
        print_char(buf[i]);
    }
    print("\r\n");
}

/*
 * Get Line Automatic
 * This uses malloc to allocate the buffer. Be sure to free
 * the returned pointer when finished with this string to 
 * avoid memory leaks.
 */
unsigned char* getla(usize_t bufsize) {
    unsigned char* buf = malloc(bufsize);
    getl(buf, bufsize);
    return buf;
}
