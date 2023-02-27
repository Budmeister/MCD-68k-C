STARTUP(crt0.o)
OUTPUT_ARCH(m68k)
/* OUTPUT_FORMAT(coff-m68k) */
OUTPUT_FORMAT(srec)

MEMORY
{
    rom (rx)   : ORIGIN = 0x0, LENGTH = 16K
    ram (rwx)  : ORIGIN = 0x010000, LENGTH = 64K
    duart (rw) : ORIGIN = 0x020000, LENGTH = 32
}

SECTIONS
{
    .text : {
        *(.text)
    } > rom

    .data : {
        *(.data)
    } > ram

    .bss : {
        __bss_start = .;
        *(.bss)
        _end =  ALIGN (0x8);
        end = _end;
        __end = _end;
        *(COMMON)
        heap_start = .;
    } > ram
}

PROVIDE(__sstack = 0x010000 + 0x4000 - 4);     /* ORIGIN(ram) + supervisor_size - 4 */
PROVIDE(err_bus     = __empty);
PROVIDE(err_addr    = __empty);
PROVIDE(err_illegal = __empty);
PROVIDE(err_divzero = __empty);
PROVIDE(err_chk     = __empty);
PROVIDE(err_trapv   = __empty);
PROVIDE(err_priv    = __empty);
PROVIDE(err_trace   = __empty);
PROVIDE(err_spur    = __empty);
PROVIDE(err_intr1   = __empty);
PROVIDE(err_intr2   = __empty);
PROVIDE(err_intr3   = __empty);
PROVIDE(err_intr4   = __empty);
PROVIDE(err_intr5   = __empty);
PROVIDE(err_intr6   = __empty);
PROVIDE(err_intr7   = __empty);
PROVIDE(err_trap0   = __empty);
PROVIDE(err_trap1   = __empty);
PROVIDE(err_trap2   = __empty);
PROVIDE(err_trap3   = __empty);
PROVIDE(err_trap4   = __empty);
PROVIDE(err_trap5   = __empty);
PROVIDE(err_trap6   = __empty);
PROVIDE(err_trap7   = __empty);
PROVIDE(err_trap8   = __empty);
PROVIDE(err_trap9   = __empty);
PROVIDE(err_trap10  = __empty);
PROVIDE(err_trap11  = __empty);
PROVIDE(err_trap12  = __empty);
PROVIDE(err_trap13  = __empty);
PROVIDE(err_trap14  = __empty);
PROVIDE(err_trap15  = __empty);
/*
 * Initalize some symbols to be zero so we can reference them in the
 * crt0 without core dumping. These functions are all optional, but
 * we do this so we can have our crt0 always use them if they exist. 
 * This is so BSPs work better when using the crt0 installed with gcc.
 * We have to initalize them twice, so we cover a.out (which prepends
 * an underscore) and coff object file formats.
 */
/* PROVIDE (hardware_init_hook = 0);
PROVIDE (_hardware_init_hook = 0);
PROVIDE (software_init_hook = 0);
PROVIDE (_software_init_hook = 0);
PROVIDE(__FINI_SECTION__ = 0); */
