*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000

*-----------------------------------------------------------
* Program : Test Loop
* Written by : Instructor
* Date : 2010
* Description: Testing ROM. NOP is "No operation" and will
* simply increase the PC
*-----------------------------------------------------------


SUPER_STACK EQU $00FFE  ; note this stack pointer points to a location
                        ; in ROM and therefore will not function as a
                        ; stack, it is simply used as a place holder.
    ORG $000000
    DC.L SUPER_STACK
    DC.L MAIN
    ORG $000100
MAIN NOP
    NOP
    NOP
    JMP MAIN
    END MAIN

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
