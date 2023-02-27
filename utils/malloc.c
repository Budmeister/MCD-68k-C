
#include "malloc.h"
#include "68k.h"
#include "io.h"

struct mptr_t{
    void* ptr;
    usize_t size;
} mptr_t; /* sizeof(struct mptr_t) == 8 bytes */

#define MALLOC_SIZE 8192
#define MAX_MPTRS MALLOC_SIZE/sizeof(mptr_t)
usize_t num_mptrs = 0;
extern void heap_start;

struct mptr_t mptrs[MAX_MPTRS];

void* malloc(usize_t size) {
    usize_t gap, i, small = MAX_USIZE, small_i = num_mptrs;
    struct mptr_t new, temp;
    void* retval;
    if(size & 0x1)
        size++;
    new.size = size;
    /*
    printf("Doing malloc for %d bytes. %d mallocs already exist.\r\n", size, num_mptrs);
    printf("heap_start: %p\r\n", &heap_start);
    */
    if(num_mptrs == 0) {
        new.ptr = &heap_start;
        mptrs[num_mptrs++] = new;
        return new.ptr;
    }
    if(num_mptrs == MAX_MPTRS)
        return NULL;
    /* Find the smallest gap greater than size */
    for(i = 1; i < num_mptrs; i++) {
        gap = ((usize_t) mptrs[i].ptr) - (usize_t) mptrs[i-1].ptr - mptrs[i-1].size;
        /* printf("Index: %d, gap: %d\r\n", i, gap); */
        if(gap >= size && gap < small) {
            small = gap;
            small_i = i;
        }
    }
    /* printf("Smallest gap %d bytes at index %d\r\n", small, small_i); */
    new.ptr = (void*) ((usize_t) mptrs[small_i-1].ptr + mptrs[small_i-1].size);
    retval = new.ptr;
    /* Insert new at position small_i */
    while(small_i < num_mptrs) {
        temp = mptrs[small_i];
        mptrs[small_i] = new;
        new = temp;
        small_i++;
    }
    mptrs[num_mptrs++] = new;
    return retval;
}

void free(void* ptr) {
    int i;

    for(i = 0; i < num_mptrs; i++) {
        if(mptrs[i].ptr == ptr) {
            num_mptrs--;
            for( ; i < num_mptrs; i++)
                mptrs[i] = mptrs[i+1];
            break;
        }
    }
}

void print_malloc_status() {
    usize_t i;
    /* Put other local variables above stack */
    void* stack;
    __asm__("
        move.l %sp, 12(%sp)
    ");
    printf("Malloc status: \r\n");
    printf("%d mptrs\r\n", num_mptrs);
    for(i = 0; i < num_mptrs; i++) {
        printf("{%d, ptr: %p, size: %d}\r\n", i, mptrs[i].ptr, mptrs[i].size);
    }
    printf("Top of heap:     %p\r\n", num_mptrs == 0 ? &heap_start : (char*) mptrs[num_mptrs-1].ptr + mptrs[num_mptrs-1].size);
    printf("Bottom of stack: %p\r\n", stack);
}

void bcopy(const void *src, void *dest, size_t n) {
    char *s = src;
    char *d = dest;
    while (n --> 0) {
        *d++ = *s++;
    }
}

