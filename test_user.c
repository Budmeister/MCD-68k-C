
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"


int main() {
    printf("Hello World!");
    /*
    char byte;
    select_channel(CHANNEL_B);
    set_baud(BAUD_19200); */    /* This writes the correct byte (0xBB), but for some reason it transmits and receives at 7200 */
    /*
    while(1) {
        select_channel(CHANNEL_B);
        byte = getcb();
        select_channel(CHANNEL_A);
        printf("%c", byte);
    }
    */

    return 0;
}
