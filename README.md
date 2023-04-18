# MCD-68k-C
This is the C code for my Microcomputer Design Project in Spring 2023.

I wrote `crt0.S` and the linker script for compilation myself (as opposed to using the default ones for 68k C), since my memory mapping is custom. For this same reason, I made my own malloc and standard library.

## Makefile
To compile a main application, use make,
```
make monitor.srec
```
To compile for the EASy68k emulator, use the `SIM` flag,
```
make monitor.c SIM=1
```
To compile a file as a user program, use the `IS_USER` flag,
```
make charlie.c IS_USER=1
```
