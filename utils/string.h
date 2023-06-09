#ifndef STRING_H
#define STRING_H

#include "68k.h"

uint32_t strcmp(const char* str1, const char* str2);
char* strcpy(char* destination, const char* source);
usize_t strlen(const char* str);
int32_t atoi(const unsigned char* str);
int32_t stoi(const unsigned char* str);
unsigned char** splitw(unsigned char* str, usize_t* num_words);


#endif