
CC 		= m68k-coff-gcc
LINKER_SCRIPT = supervisor/linkerSupervisor.ld
CFLAGS = -m68000 -O0 -fomit-frame-pointer --verbose -Wall -ansi
INCLUDES = bin/malloc.o bin/string.o bin/io.o bin/math.o bin/68k.o

# When switching between SIM and not SIM or between IS_USER and not IS_USER,
# do make clean because the libraries are dependent on those variables
# and will not be recompiled automatically.
ifdef SIM
	CFLAGS += -DSIM
	INCLUDES += bin/easy68k-utils.o
else
	INCLUDES += bin/duart.o
endif
ifdef IS_USER
	CFLAGS += -DUSER
	LINKER_SCRIPT = user/linkerUser.ld
	CRT0 = user/crt0.o
else
	INCLUDES += bin/srec.o bin/supervisor.o
	CRT0 = supervisor/crt0.o
endif
LDFLAGS = -m68000 -Wl,-n -T$(LINKER_SCRIPT) -nostartfiles -Wl,-Map=$(basename $@).map

%.srec: %.o $(CRT0) $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) $< $(INCLUDES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

bin/%.o: utils/%.c
	$(CC) $(CFLAGS) $< -c -o $@

asm/%.S: %.c
	$(CC) $(CFLAGS) $< -S -o $@

supervisor/crt0.o: supervisor/crt0.S
	$(CC) supervisor/crt0.S -c -o supervisor/crt0.o

user/crt0.o: user/crt0.S
	$(CC) user/crt0.S -c -o user/crt0.o

# hello.o and hello.x are just tests on the example compilations.
hello.o: hello.c
	m68k-coff-gcc -m5200 -O4 -fomit-frame-pointer --verbose -Wall -ansi hello.c -c -o hello.o

hello.x: hello.o
	m68k-coff-gcc -m5200  -Wl,-s -Wl,-n -Tsbc5206-srec.ld -Wl,-Map=hello.map --verbose  hello.o   -o hello

clean:
	rm -f *.x *.o *.srec *.map core *.d bin/* asm/utils/*
