
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"

#define BUF_SIZE 100
char sendMsg[BUF_SIZE];
char recMsg[BUF_SIZE];
int sendLen = 0;
int recLen = 0;
bool sendReady = false;
bool recReady = false;

int main() {
    char byte;
    int i;
    select_channel(CHANNEL_B);
    duart_init(MODE_RX_INT_RXRDY | MODE_ERR_MODE_CHAR | MODE_NO_PARITY | MODE_PARITY_EVEN | MODE_8_BIT_CHAR);
    duart_update_mode(MODE_ECHO_NORMAL | MODE_BIT_LENGTH_1);
    set_baud(BAUD_19200);    /* This writes the correct byte for 9600 (0xBB), but for some reason it transmits and receives at 7200 */
    command(ENABLE_TX | ENABLE_RX);

    select_channel(CHANNEL_A);
    printf("*");
    while(1) {
        select_channel(CHANNEL_A);
        while(available()) {
            byte = getcb();
            if(byte == '\n' || byte == '\r')
                byte = '\0';
            if(byte == '\0')
                sendReady = true;
            sendMsg[sendLen++] = byte;
            printf("%c", byte);
            if(sendLen == BUF_SIZE - 1) {
                sendReady = true;
                sendMsg[sendLen++] = '\0';
            }
        }
        select_channel(CHANNEL_B);
        while(available()) {
            byte = getcb();
            if(byte == '\n' || byte == '\r')
                byte = '\0';
            if(byte == '\0')
                recReady = true;
            recMsg[recLen++] = byte;
            if(recLen == BUF_SIZE - 1) {
                recReady = true;
                recMsg[recLen++] = '\0';
            }
        }
        if(sendReady) {
            select_channel(CHANNEL_B);
            printf("%s\r", sendMsg);
            select_channel(CHANNEL_A);
            for(i = sendLen; i > 1; i--)
                printf("\b \b");
            printf("Sent:     %s\r\n*", sendMsg);
            sendLen = 0;
            sendReady = false;
        }
        if(recReady) {
            select_channel(CHANNEL_A);
            sendMsg[sendLen] = '\0';
            for(i = sendLen; i > 0; i--)
                printf("\b \b");
            printf("Received: %s\r\n", recMsg);
            printf("*%s", sendMsg);
            recLen = 0;
            recReady = false;
        }
    }


    return 0;
}
