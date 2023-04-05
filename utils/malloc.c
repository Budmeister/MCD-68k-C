
#include "malloc.h"
#include "68k.h"
#include "io.h"

struct mptr_t{
    void* ptr;
    usize_t size;
} mptr_t; /* sizeof(struct mptr_t) == 8 bytes */

/* USER_MODE macro will be defined in Makefile */
#ifdef USER_MODE
#define MALLOC_SIZE 8192
#define HEAP_SIZE 24576
#else
#define MALLOC_SIZE 1024    /* Change to 8192 for user code */
#define HEAP_SIZE 8192      /* Change to 24576 for user code */
#endif
#define MAX_MPTRS MALLOC_SIZE/sizeof(mptr_t)
#define HEAP_BORDER ((uint32_t*) ((char*) &heap_start + (HEAP_SIZE - 4)))
#define HEAP_BORDER_KEYWORD 0x00C0FFEE
usize_t num_mptrs;
extern void heap_start;

#define MERR_NONE 0
#define MERR_HBORDER_BROKEN 1
#define MERR_MPTR_TABLE_FULL 2
uint32_t malloc_error = MERR_NONE;

struct mptr_t mptrs[MAX_MPTRS];

/* Called from crt0.S */
void minit() {
    *HEAP_BORDER = HEAP_BORDER_KEYWORD;
    num_mptrs = 0;
    malloc_error = MERR_NONE;
}

void mcheck() {
    if(*HEAP_BORDER != HEAP_BORDER_KEYWORD) {
        malloc_error = MERR_HBORDER_BROKEN;
        return;
    }else if(num_mptrs >= MAX_MPTRS) {
        malloc_error = MERR_MPTR_TABLE_FULL;
        return;
    }
    malloc_error = MERR_NONE;
}

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
        if((usize_t) new.ptr + new.size >= (usize_t) &heap_start + HEAP_SIZE - 4)
            return NULL;
        mptrs[num_mptrs++] = new;
        return new.ptr;
    }
    if(num_mptrs == MAX_MPTRS)
        return NULL;
    /* Find the smallest gap greater than size */
    for(i = 1; i < num_mptrs; i++) {
        gap = (usize_t) mptrs[i].ptr - (usize_t) mptrs[i-1].ptr - mptrs[i-1].size;
        /* printf("Index: %d, gap: %d\r\n", i, gap); */
        if(gap >= size && gap < small) {
            small = gap;
            small_i = i;
        }
    }
    /* printf("Smallest gap %d bytes at index %d\r\n", small, small_i); */
    new.ptr = (void*) ((usize_t) mptrs[small_i-1].ptr + mptrs[small_i-1].size);
    if((usize_t) new.ptr + new.size >= (usize_t) &heap_start + HEAP_SIZE - 4)
        return NULL;
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
    __asm__("move.l %sp, 12(%sp)");
    printf("Malloc status: \r\n");
    printf("\t%d mptrs\r\n", num_mptrs);
    for(i = 0; i < num_mptrs; i++) {
        printf("\t\t{%d, ptr: %p, size: %d}\r\n", i, mptrs[i].ptr, mptrs[i].size);
    }
    printf("\tTop of heap:      %p\r\n", num_mptrs == 0 ? &heap_start : (char*) mptrs[num_mptrs-1].ptr + mptrs[num_mptrs-1].size);
    printf("\tHeap Border:      %p\r\n", HEAP_BORDER);
    printf("\tBottom of stack:  %p\r\n", stack);
    mcheck();
    if(malloc_error == MERR_HBORDER_BROKEN) {
        printf("\tMalloc Error:     Heap Border Broken\r\n");
    } else if(malloc_error == MERR_MPTR_TABLE_FULL) {
        printf("\tMalloc Error:     Mptr Table Full\r\n");
    } else if(malloc_error == MERR_NONE) {
        printf("\tMalloc Error:     None\r\n");
    } else {
        printf("\tMalloc Error:     Invalid Error: %d\r\n", malloc_error);
    }
}

void bcopy(const void *src, void *dest, size_t n) {
    const char *s = src;
    char *d = dest;
    while (n --> 0) {
        *d++ = *s++;
    }
}
