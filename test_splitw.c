
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"

int main() {
    const char teststr_static[] = "The quick brown fox jumped over the lazy dog.";
    char* teststr;
    unsigned char** words;
    usize_t numwords, i;
    teststr = malloc(sizeof(teststr_static));
    strcpy(teststr, teststr_static);
    printf("%s", teststr);
    words = splitw(teststr, &numwords);
    print_malloc_status();
    for(i = 0; i < numwords; i++) {
        printf("%s\r\n", words[i]);
    }
    free(teststr);
    free(words);
    return 0;
}