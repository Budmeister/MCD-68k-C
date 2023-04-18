#include "math.h"
#include "68k.h"

unsigned int random(unsigned int max_num, unsigned int seed) {
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    static unsigned int x = 0;
    
    if (seed != 0) {
        x = seed;
    }
    
    x = (a * x + c) % (max_num + 1);
    return x;
}

int pow(int base, int exponent) {
    int result = 1;
    int i;
    for (i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}
