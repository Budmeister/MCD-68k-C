#include "duart.h"


void commandA(uint8_t com) {
    MISR_CRA = com;
}
void commandB(uint8_t com) {
    _CRB = com;
}
void command(uint8_t com) {
    if (select_channel == CHANNEL_A)
        commandA(com);
    else
        commandB(com);
}
void standby() {
    commandA(SET_STANDBY);
}
void active() {
    commandA(SET_ACTIVE);
}
void duart_init(uint8_t mr1) {
    if (selected_channel == CHANNEL_A)
        MRA = mr1;
    else
        MRB = mr1;
}
void duart_update_mode(uint8_t mr2) {
    if (selected_channel == CHANNEL_A)
        MRA = mr2;
    else
        MRB = mr2;
}
void set_baud(uint8_t baud) {
    volatile uint8_t *CSR;

    if (selected_channel == CHANNEL_A) {
        CSR = &SRA_CSRA;
    } else {
        CSR = &SRB_CSRB;
    }

    /* SET X */
    if(baud & BBM_X) {
        command(SET_RX_BRG_SEL_EX);
        command(SET_TX_BRG_SEL_EX);
    } else {
        command(CLR_RX_BRG_SEL_EX);
        command(CLR_TX_BRG_SEL_EX);
    }
    IPCR_ACR = baud & BBM_ACR7;    /* No other bits of ACR matter, only ACR[7] */
    baud &= BBM_SELECT;
    baud |= baud << 4;
    *CSR = baud;
}

void echo(uint8_t mode) {
    volatile uint8_t *MR;
    if (selected_channel == CHANNEL_A)
        MR = &MRA;
    else
        MR = &MRB;
    mode = mode & 0xc0;
    *MR = (*MR & 0x3f) | mode;
}

void printA(const char* str) {
    while(*str != '\0') {
        while(!(SRA_CSRA & STATUS_TXRDY));
        RHRA_THRA = *str;
        str++;
    }
}

void printB(const char* str) {
    while(*str != '\0') {
        while(!(SRB_CSRB & STATUS_TXRDY));
        RHRB_THRB = *str;
        str++;
    }
}

bool available() {
    if(selected_channel == CHANNEL_A)
        return SRA_CSRA & STATUS_RXRDY;
    else
        return SRB_CSRB & STATUS_RXRDY;
}

char getc() {
    if(selected_channel == CHANNEL_A)
        return RHRA_THRA;
    else
        return RHRB_THRB;
}

char getcb() {
    while(!available());
    return getc();
}

void print(const char* str) {
    if(selected_channel == CHANNEL_A)
        printA(str);
    else
        printB(str);
}

void select_channel(uint8_t channel) {
    if(channel == CHANNEL_A || channel == CHANNEL_B)
        selected_channel = channel;
}

uint8_t get_selected_channel() {
    return selected_channel;
}
