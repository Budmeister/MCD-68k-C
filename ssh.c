
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"

int main() {
    select_channel(CHANNEL_B);
    duart_init(MODE_RX_INT_RXRDY | MODE_ERR_MODE_CHAR | MODE_NO_PARITY | MODE_PARITY_EVEN | MODE_8_BIT_CHAR);
    duart_update_mode(MODE_ECHO_NORMAL | MODE_BIT_LENGTH_1);
    set_baud(BAUD_19200);    /* This writes the correct byte for 9600 (0xBB), but for some reason it transmits and receives at 7200 */
    command(ENABLE_TX | ENABLE_RX);

    printf("ssh");

    

    return 0;
}

