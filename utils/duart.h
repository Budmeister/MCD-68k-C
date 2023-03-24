#ifndef DUART_H

#include "68k.h"

                                        /* Read                                 Write                               */
                                        /* ------------------------------------------------------------------------ */
extern volatile uint8_t MRA;            /* Mode Register A                      Mode Register A                     */
extern volatile uint8_t SRA_CSRA;       /* Status Register A                    Clock Select Register A             */
extern volatile uint8_t MISR_CRA;       /* Masked Interrupt Status Register     Command Register A                  */
extern volatile uint8_t RHRA_THRA;      /* RX Holding Register A                TX Holding Register A               */
extern volatile uint8_t IPCR_ACR;       /* Input Port Change Register           Auxilliary Control Register         */
extern volatile uint8_t ISR_IMR;        /* Interrupt Status Register            Interrupt Mask Register             */
extern volatile uint8_t CTU;            /* Counter/Timer Upper Byte Register    Counter/Timer Upper Byte Register   */
extern volatile uint8_t CTL;            /* Counter/Timer Lower Byte Register    Counter/Timer Lower Byte Register   */
extern volatile uint8_t MRB;            /* Mode Register B                      Mode Register B                     */
extern volatile uint8_t SRB_CSRB;       /* Status Register B                    Clock Select Register B             */
extern volatile uint8_t _CRB;           /* RESERVED                             Command Register B                  */
extern volatile uint8_t RHRB_THRB;      /* RX Holding Register B                TX Holding Register B               */
extern volatile uint8_t IVR;            /* Interrupt Vector Register            Interrupt Vector Register           */
extern volatile uint8_t IP_OPCR;        /* Input Port                           Output Port Configuration Register  */
extern volatile uint8_t SCC_SOPBC;      /* (Start Counter/Timer Command)        (Set Output Port Bits Command)      */
extern volatile uint8_t STC_COPBC;      /* (Stop Counter/Timer Command)         (Clear Output Port Bits 1 Command)  */

#define CHANNEL_A           0
#define CHANNEL_B           1

/* Command Register Commands */
/* Bitwise combine a TX command, an RX command, and any of the lower commands */
#define DISABLE_TX          0x08
#define ENABLE_TX           0x04
#define DISABLE_RX          0x02
#define ENABLE_RX           0x01

#define RESET_MRN           0x10
#define RESET_RX            0x20
#define RESET_TX            0x30
#define RESET_ERR           0x40
#define RESET_BRK_CHG_INT   0x50
#define START_BRK           0x60
#define STOP_BRK            0x70
#define SET_RX_BRG_SEL_EX   0x80
#define CLR_RX_BRG_SEL_EX   0x90
#define SET_TX_BRG_SEL_EX   0xA0
#define CLR_TX_BRG_SEL_EX   0xB0
#define SET_STANDBY         0xC0
#define SET_ACTIVE          0xD0

/* Baud Preferences */
#define BBM_ACR7        0x80    /* 0b10000000 */
#define BBM_X           0x10    /* 0b00010000 */
#define BBM_SELECT      0x0f    /* 0b00001111 */

#define BAUD_50         0x00    /* 0b00000000 */
#define BAUD_75         0x10    /* 0b00010000 */
#define BAUD_110        0x01    /* 0b00000001 */
#define BAUD_134_5      0x02    /* 0b00000010 */
#define BAUD_150        0x13    /* 0b00010011 */
#define BAUD_200        0x03    /* 0b00000011 */
#define BAUD_300        0x04    /* 0b00000100 */
#define BAUD_600        0x05    /* 0b00000101 */
#define BAUD_1200       0x06    /* 0b00000110 */
#define BAUD_1050       0x07    /* 0b00000111 */
#define BAUD_1800       0x1a    /* 0b00011010 */
#define BAUD_2000       0x87    /* 0b10000111 */
#define BAUD_2400       0x08    /* 0b00001000 */
#define BAUD_3600       0x14    /* 0b00010100 */
#define BAUD_4800       0x09    /* 0b00001001 */
#define BAUD_7200       0x0a    /* 0b00001010 */
#define BAUD_9600       0x0b    /* 0b00001011 */
#define BAUD_14400      0x15    /* 0b00010101 */
#define BAUD_19200      0x1c    /* 0b00011100 */
#define BAUD_28800      0x16    /* 0b00010110 */
#define BAUD_38400      0x0c    /* 0b00001100 */
#define BAUD_57600      0x17    /* 0b00010111 */
#define BAUD_115200     0x18    /* 0b00011000 */

/* Status Registers */
#define STATUS_RECEIVED_BREAK  0x80
#define STATUS_FRAMING_ERROR   0x40
#define STATUS_PARITY_ERROR    0x20
#define STATUS_OVERRUN_ERROR   0x10
#define STATUS_TXEMT           0x08
#define STATUS_TXRDY           0x04
#define STATUS_FFULL           0x02
#define STATUS_RXRDY           0x01

void commandA(uint8_t com);
void commandB(uint8_t com);
void standby();
void active();
void set_baud(uint8_t baud, uint8_t channel);
void echo(uint8_t mode, uint8_t channel);   /* Remove easy68kutils.h include, and remove the underscore */
bool available();
char getc();
char getcb();
void print(const char* str);

bool availableA();
char getcA();
char getcb();
void printA(const char* str);

bool availableB();
char getcB();
char getcB();
void printB(const char* str);

#define DUART_H
#endif