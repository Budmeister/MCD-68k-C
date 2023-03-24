/*
#include <math.h>
#include <malloc.h>
    float c = 3;
    float d = c - 1.5;
    return malloc(10);
    free(ptr);
*/
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/easy68k-utils.h"
#include "utils/string.h"
#include "utils/io.h"

void err_bus() {

}

void err_trap0() {
    /* __asm__("reset"); */
    while(1);
}


int16_t hello() {
    int a = 2;
    a = a + 3;
    return 0;
}

struct mystruct {
    int a;
    int b;
};

struct mystruct myfun() {
    struct mystruct s;
    return s;
}


int main() {
    char c;
    int *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;
    struct mystruct s;
    printf("\r\n\r\nTesting malloc\r\n");
    ptr1 = malloc(sizeof(int));
    printf("malloc(4) returned: %p\r\n", ptr1);
    ptr2 = malloc(sizeof(int));
    printf("malloc(4) returned: %p\r\n", ptr2);
    ptr3 = malloc(sizeof(int));
    printf("malloc(4) returned: %p\r\n", ptr3);
    printf("Freeing %p\r\n", ptr3);
    free(ptr3);
    ptr4 = malloc(sizeof(int));
    printf("malloc(4) returned: %p\r\n", ptr4);
    printf("Freeing %p\r\n", ptr2);
    free(ptr2);
    ptr5 = malloc(6);
    printf("malloc(6) returned: %p\r\n", ptr5);
    ptr6 = malloc(4);
    printf("malloc(4) returned: %p\r\n", ptr6);
    while(1) {
        c = getc();
        if(c != -1) {
            printf("%c", c);
        }
    }
    s = myfun();
    return 0;
}