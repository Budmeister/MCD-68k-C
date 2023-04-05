*-----------------------------------------------------------
* Program : Test Loop
* Written by : Instructor
* Date : 2010
* Description: Testing RAM with a subroutine jump. To jump
* to a subroutine, the PC and SR are pushed onto
* the stack which is a location in RAM. If the
* program continually loops, the RAM is working
*-----------------------------------------------------------
SUPER_STACK EQU $01FFFC ; MUST BE A VALID RAM LOCATION
    ORG $000000
    DC.L SUPER_STACK
    DC.L MAIN
    ORG $000100
MAIN JSR RAM_TEST
    JMP MAIN
    ORG $010000
RAM_TEST NOP
    NOP
    NOP
    RTS
    END MAIN
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
