
#include "string.h"
#include "malloc.h"

uint32_t strcmp(const char* str1, const char* str2) {
    usize_t i = 0;
    while(str1[i] == str2[i]) {
        if(str1[i] == 0)
            return 0;
        i++;
    }
    return str1[i] - str2[i];
}

char* strcpy(char* destination, const char* source) {
    char* cursor = destination;
    do {
        *cursor = *source;
        cursor++;
        source++;
    } while (*source != '\0');
    return destination;
}

usize_t strlen(const char* str) {
    usize_t len = 0;
    while(*str != '\0') {
        len++;
        str++;
    }
    return len;
}

int32_t atoi(const unsigned char* str) {
    bool neg = false;
    usize_t i = 0;
    int32_t retval = 0;
    if(str[i] == '-') {
        neg = true;
        i++;
    }
    for( ; str[i] != 0; i++) {
        if(str[i] < '0' || str[i] > '9')
            return 0;
        retval = retval * 10 + (str[i] - '0');
    }
    if(neg)
        retval = -retval;
    return retval;
}

int32_t stoi(const unsigned char* str) {
    bool neg = false;
    usize_t i = 0;
    int32_t retval = 0;
    if(str[i] == '-') {
        neg = true;
        i++;
    }
    for( ; str[i] != 0; i++) {
        if(str[i] >= '0' && str[i] <= '9')
            retval = retval * 16 + (str[i] - '0');
        else if(str[i] >= 'a' && str[i] <= 'f')
            retval = retval * 16 + (str[i] - 'a' + 10);
        else if(str[i] >= 'A' && str[i] <= 'F')
            retval = retval * 16 + (str[i] - 'A' + 10);
        else
            return 0;
    }
    if(neg)
        retval = -retval;
    return retval;
}

#define iswhitespace(x) (x == ' ' || x == '\n' || x == '\r')

/*
 * Returns a pointer to the next character that either
 * is not a whitespace character or is '\0'
 */
unsigned char* nextblack(unsigned char* str) {
    while(1) {
        /* printf("Inspecting '%c' for blackness\r\n", *str); */
        if(!iswhitespace(*str) || *str == '\0')
            return str;
        str++;
    }
}

/* 
 * Returns a pointer to the next 
 * whitespace character or '\0'
 */
unsigned char* nextwhite(unsigned char* str) {
    while(1) {
        /* printf("Inspecting '%c' for whiteness\r\n", *str); */
        if(iswhitespace(*str) || *str =='\0')
            return str;
        str++;
    }
}
/*
 * Returns NULL if there are no words (including the
 * case where there is only whitspace). Otherwise, 
 * returns an array of pointers to the start of the words,
 * and the first whitespace character after each word is
 * replaced with the null character.
 */
unsigned char** splitw(unsigned char* str, usize_t* num_words) {
    unsigned char* word = str;
    unsigned char** retval;
    usize_t i;
    *num_words = 0;
    /* Count the words */
    /* printf("Splitting: %s\r\n", str); */
    /* printf("*num_words: %d@%p\r\n", *num_words, num_words); */
    {
        word = nextblack(word);
        if(word == NULL)
            return NULL;
        if(*word == '\0')
            return NULL;
        (*num_words)++;
        while(1) {
            /* printf("*num_words: %d@%p\r\n", *num_words, num_words); */
            word = nextwhite(word);
            word = nextblack(word);
            if(*word == '\0')
                break;
            (*num_words)++;
        }
    }
    /* printf("Found %d words\r\n", *num_words); */
    /* 
     * Same thing but store the pointers to the beginning 
     * of the words and change the whitespace character after
     * the words to '\0'
     */
    {
        retval = malloc(*num_words);
        /* word = nextblack(str); */
        word = str;
        for(i = 0; i < *num_words; i++) {
            word = nextblack(word);
            retval[i] = word;
            word = nextwhite(word);
            *word = '\0';
            word++;
        }
    }
    return retval;
}
