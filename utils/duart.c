#include "duart.h"


void commandA(uint8_t com) {
    MISR_CRA = com;
}
void commandB(uint8_t com) {
    _CRB = com;
}
void standby() {
    commandA(SET_STANDBY);
}
void active() {
    commandA(SET_ACTIVE);
}
void set_baud(uint8_t baud, uint8_t channel) {
    void (*command)(uint8_t);
    volatile uint8_t *CSR;

    if (channel == CHANNEL_A) {
        command = &commandA;
        CSR = &SRA_CSRA;
    } else if (channel == CHANNEL_B) {
        command = &commandB;
        CSR = &SRB_CSRB;
    } else {
        return;
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

void echo(uint8_t mode, uint8_t channel) {
    volatile uint8_t *MR;
    if (channel == CHANNEL_A)
        MR = &MRA;
    else if (channel == CHANNEL_B)
        MR = &MRB;
    else
        return;
    mode = mode & 0xc0;
    *MR = (*MR & 0x3f) | mode;
}

bool availableA() {
    return SRA_CSRA & STATUS_RXRDY;
}

char getcA() {
    return RHRA_THRA;
}

char getcbA() {
    while(!availableA());
    return getcA();
}

void printA(const char* str) {
    while(*str != '\0') {
        while(!(SRA_CSRA & STATUS_TXRDY));
        RHRA_THRA = *str;
        str++;
    }
}

bool availableB() {
    return SRB_CSRB & STATUS_RXRDY;
}

char getcB() {
    return RHRB_THRB;
}

char getcbB() {
    while(!availableB());
    return getcB();
}

void printB(const char* str) {
    while(*str != '\0') {
        while(!(SRB_CSRB & STATUS_TXRDY));
        RHRB_THRB = *str;
        str++;
    }
}

bool available() {
    return availableA();
}

char getc() {
    return getcA();
}

char getcb() {
    return getcbA();
}

void print(const char* str) {
    printA(str);
}
