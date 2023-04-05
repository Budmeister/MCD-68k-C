*-----------------------------------------------------------
* Subroutine : DUART enable
* Written by : Instructor
* Date : 2013
* Description: used to initialize a 68681 DUART
*-----------------------------------------------------------
* Note, most DUART configurations are ignorant of UDS/LDS
* and thus are only active on odd addresses (since the lower
* data lines are usually run to the DUART data bus)
; *******************************************************************

    ORG    $0000
    DC.L    $00013FFC, $00001000

    ORG    $1000

; Constants: (Note the (odd) offsets to account for no A0)
DUART EQU $020000 loaded in A0 when needed, regs are offsets
MR1A EQU 1 Mode Register1
MR2A EQU 1 points here after MR1A is set
SRA EQU 3 Status Register (read)
CSRA EQU 3 Clock Select Register
CRA EQU 5 Command Register
TBA EQU 7 Transfer Holding Register
RBA EQU 7 Receive Holding Register
ACR EQU 9 Auxiliary control register
RxRDY EQU 0 Recieve ready bit position
TxRDY EQU 2 Transmit ready bit position
BAUD EQU $CC baud rate value = 19,200 baud
; *******************************************************************
MAIN JSR EMPTY
    JSR EMPTY
    JSR INIT_DUART
LOOP JSR LOOP

EMPTY JSR EMPTY2
    RTS

EMPTY2 RTS

INIT_DUART LEA DUART,A0 A0 points to base DUART address
    ; Software reset:
    MOVE.B #$30,CRA(A0) Reset TxA
    MOVE.B #$20,CRA(A0) Reset RxA
    MOVE.B #$10,CRA(A0) Reset MRA pointer
    ; Initialization:
    MOVE.B #$80,ACR(A0) selects baud rate set 2
    MOVE.B #BAUD,CSRA(A0) set 19.2k baud Rx/Tx
    MOVE.B #$13,MR1A(A0) 8-bits, no parity, 1 stop bit
    ; This is the most important register to set in the 68681 DUART.
    ; 07 sets: Normal mode, CTS and RTS disabled, stop bit length = 1
    ; For testing load $#47 to enable auto-echo
    MOVE.B #$47,MR2A(A0)
    MOVE.B #$05,CRA(A0) enable Tx and Rx
    RTS

SIMHALT
END



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
