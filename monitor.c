
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"

#define COMMAND_BUFSIZE 20

int main() {
    char* command;
    char** words;
    usize_t num_words, i;
    command = getl(COMMAND_BUFSIZE);
    printf("%s\r\n", command);
    words = splitw(command, &num_words);
    for(i = 0; i < num_words; i++){
        printf("%s\r\n", words[i]);
    }

    free(words);
    free(command);
    print_malloc_status();
    return 0;
}