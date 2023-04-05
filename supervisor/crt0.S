
/*
 * crt0.S -- startup file for m68k-coff
 * This is the startup file for Supervisor Programs. For user programs, see user/crt0.S
 * 
 * From: file:///D:/GccAshWare/gcc-m68k-ashware/doc/porting_3.html
 * 
 * To make a program that has been compiled with GCC to run, you need to write some startup code. 
 * The initial piece of startup code is called a crt0. (C RunTime 0) This is usually written in 
 * assembler, and it's object gets linked in first, and bootstraps the rest of the application when executed. 
 * This file needs to do the following things.
 * 
 * 1. Initialize anything that needs it. This init section varies. If you are developing an application 
 * that gets download to a ROM monitor, then there is usually no need for any special initialization. 
 * The ROM monitor handles it for you. If you plan to burn your code in a ROM, then the crt0 typically has 
 * to do all the hardware initialization that is required to run an application. This can include things 
 * like initializing serial ports or run a memory check. It all depends on the hardware.
 * 
 * 2. Zero the BSS section. This is for uninitialized data. All the addresses in this section need to be 
 * initialized to zero so that programs that forget to check new variables default value will get 
 * unpredictable results.
 * 
 * 3. Call main() This is what basically starts things running. If your ROM monitor supports it, 
 * then first setup argc and argv for command line arguments and an environment pointer. Then branch to main(). 
 * For G++ the the main routine gets a branch to __main inserted by the code generator at the very top. 
 * __main() is used by G++ to initialize it's internal tables. __main() then returns back to your original 
 * main() and your code gets executed.
 * 
 * 4. Call exit() After main() has returned, you need to cleanup things and return control of the hardware 
 * from the application. On some hardware, there is nothing to return to, especially if your program is in ROM. 
 * Sometimes the best thing to do in this case is do a hardware reset, or branch back to the start address 
 * all over again. When there is a ROM monitor present, usually a user trap can be called and then the ROM 
 * takes over. Pick a safe vector with no side effects. Some ROMs have a builtin trap handler just for this case.
 */

	.title "crt0.S for m68k-coff"

/* These are predefined by new versions of GNU cpp.  */

#ifndef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX__ _
#endif

#ifndef __REGISTER_PREFIX__
#define __REGISTER_PREFIX__
#endif

/* ANSI concatenation macros.  */

#define CONCAT1(a, b) CONCAT2(a, b)
#define CONCAT2(a, b) a ## b

/* Use the right prefix for global labels.  */

#define SYM(x) CONCAT1 (__USER_LABEL_PREFIX__, x)

/* Use the right prefix for registers.  */

#define REG(x) CONCAT1 (__REGISTER_PREFIX__, x)

#define d0 REG (d0)
#define d1 REG (d1)
#define d2 REG (d2)
#define d3 REG (d3)
#define d4 REG (d4)
#define d5 REG (d5)
#define d6 REG (d6)
#define d7 REG (d7)
#define a0 REG (a0)
#define a1 REG (a1)
#define a2 REG (a2)
#define a3 REG (a3)
#define a4 REG (a4)
#define a5 REG (a5)
#define a6 REG (a6)
#define fp REG (fp)
#define sp REG (sp)

/*
 * Set up some room for a stack. We just grab a chunk of memory.
 * 
 * CHANGE:
 * 
 * The CPU will automatically load the long word at 0x000000 to
 * the supervisor stack, so put the sstack symbol there. 
 * See Vector Table belos.
 */


/*
 * Beginning of .data section
 */
	.data
/*
 * Do not put anything in the .data section, since the linker script 
 * will place it in the RAM, and the S-Record will be burned to the ROM.
 */

/*
 * Beginning of .text section
 */
 	.align	2
	.text
	.global SYM (stack)

	.global SYM (main)
	.global SYM (exit)
/* 
 * This really should be __bss_start, not SYM (__bss_start).
 */
	.global __bss_start
	.global __main
/*
 * Put Vector Table here
 * 000 - Reset--initial supervisor stack pointer
 * 004 - Reset--initial program counter value
 * 008 - Bus error
 * 00C - Address error
 * 010 - Illegal instruction
 * 014 - Divide by zero
 * 018 - CHK instruction
 * 01C - TRAPV instruction
 * 020 - Privilege violation
 * 024 - Trace
 * 060 - Spurious interrupt
 * 064 - Level 1 interrupt autovector
 * 068 - Level 2 interrupt autovector
 * ...
 * 07C - Level 7 interrupt autovector
 * 080 - TRAP #0 vector
 * 084 - TRAP #1 vector
 * ...
 * 0BC - TRAP #15 vector
 * [end vector table]
 */
	.global __sstack
	.global err_bus
	.global err_addr
	.global err_illegal
	.global err_divzero
	.global err_chk
	.global err_trapv
	.global err_priv
	.global err_trace
	.global err_spur
	.global err_intr1
	.global err_intr2
	.global err_intr3
	.global err_intr4
	.global err_intr5
	.global err_intr6
	.global err_intr7
	.global err_trap0
	.global err_trap1
	.global err_trap2
	.global err_trap3
	.global err_trap4
	.global err_trap5
	.global err_trap6
	.global err_trap7
	.global err_trap8
	.global err_trap9
	.global err_trap10
	.global err_trap11
	.global err_trap12
	.global err_trap13
	.global err_trap14
	.global err_trap15
	.global __empty
	
	dc.l	__sstack
	dc.l 	SYM (start)
	dc.l	err_bus
	dc.l	err_addr
	dc.l	err_illegal
	dc.l	err_divzero
	dc.l	err_chk
	dc.l	err_trapv
	dc.l	err_priv
	dc.l	err_trace
	.org	96
	dc.l	err_spur
	dc.l	err_intr1
	dc.l	err_intr2
	dc.l	err_intr3
	dc.l	err_intr4
	dc.l	err_intr5
	dc.l	err_intr6
	dc.l	err_intr7
	dc.l	err_trap0
	dc.l	err_trap1
	dc.l	err_trap2
	dc.l	err_trap3
	dc.l	err_trap4
	dc.l	err_trap5
	dc.l	err_trap6
	dc.l	err_trap7
	dc.l	err_trap8
	dc.l	err_trap9
	dc.l	err_trap10
	dc.l	err_trap11
	dc.l	err_trap12
	dc.l	err_trap13
	dc.l	err_trap14
	dc.l	err_trap15

/*
 * start -- set things up so the application will run.
 */
	.even
	.global SYM (start)
SYM (start):
	link	a6, #-8

/*
 * zerobss -- zero out the bss section
 */
	movea.l	#__bss_start, a0
	movea.l	#SYM (end), a1
1:
	move.l	#0, (a0)
	lea.l	4(a0), a0
	cmpa.l	a0, a1
	bge	1b

/*
 * Initialize malloc
 */
	.global minit
	jsr minit

/*
 * Call the main routine from the application to get it going.
 * main (argc, argv, environ)
 * We pass argv as a pointer to NULL.
 * We pass eviron as a pointer to NULL.
 */
	pea     0
	pea     0
	pea     sp@(4)
	pea     0
	jsr	SYM (main)
	move.l	d0, sp@-
	jsr SYM (exit)
	/* End subroutine start */
	
/*
 * __main -- Used by G++ to initialize some tables for C++. It is 
 *			 not implemented here, so do not use C++.
 */
	.even
__main:
	rts
__empty:
	rte
/*
 * _exit -- Exit from the application. Normally we cause a user trap
 *          to return to the ROM monitor for another run.
 */
	.even
SYM (exit):
	trap	#0