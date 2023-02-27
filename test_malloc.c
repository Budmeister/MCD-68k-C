
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/easy68k-utils.h"
#include "utils/io.h"

int main() {
    char c;
    int *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;
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
    return 0;
}