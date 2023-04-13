

#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/string.h"
#include "utils/io.h"
#include "utils/duart.h"
#include "duart_test.h"

void myerr() {
    uint16_t sr;
    uint32_t pc;
}

static void my_static_fun() {
    
}


int main() {
    select_channel(CHANNEL_A);
    duart_init(MODE_RX_INT_RXRDY | MODE_ERR_MODE_CHAR | MODE_NO_PARITY | MODE_PARITY_EVEN | MODE_8_BIT_CHAR);
    duart_update_mode(MODE_ECHO_NORMAL | MODE_BIT_LENGTH_1);
    set_baud(BAUD_9600);    /* This writes the correct byte (0xBB), but for some reason it transmits and receives at 7200 */
    command(ENABLE_TX | ENABLE_RX);
    while(1) {
        printf("Baud byte: %x\r\n", BAUD_9600);
        /* RHRA_THRA = 'j'; */
    }
   /*
    INIT_DUART();
    */
    return 0;
}