STARTUP(user/crt0.o)
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
    .text 0x014000 : {
        *(.text)
    } > ram

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

PROVIDE(__stack = 0x020000 - 4);     /* ORIGIN(ram) + supervisor_size - 4 */


PROVIDE(MRA         = 0x020001);
PROVIDE(SRA_CSRA    = 0x020003);
PROVIDE(MISR_CRA    = 0x020005);
PROVIDE(RHRA_THRA   = 0x020007);
PROVIDE(IPCR_ACR    = 0x020009);
PROVIDE(ISR_IMR     = 0x02000b);
PROVIDE(CTU         = 0x02000d);
PROVIDE(CTL         = 0x02000f);
PROVIDE(MRB         = 0x020011);
PROVIDE(SRB_CSRB    = 0x020013);
PROVIDE(_CRB        = 0x020015);
PROVIDE(RHRB_THRB   = 0x020017);
PROVIDE(IVR         = 0x020019);
PROVIDE(IP_OPCR     = 0x02001b);
PROVIDE(SCC_SOPBC   = 0x02001d);
PROVIDE(STC_COPBC   = 0x02001f);


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
