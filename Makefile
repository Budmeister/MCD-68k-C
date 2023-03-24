
CC 		= m68k-coff-gcc
LINKER_SCRIPT = linkerSupervisor.ld
CFLAGS = -m68000 -O0 -fomit-frame-pointer --verbose -Wall -ansi
LDFLAGS = -m68000 -Wl,-n -T$(LINKER_SCRIPT) -nostartfiles -Wl,-Map=$(basename $@).map
INCLUDES = bin/malloc.o bin/string.o bin/io.o bin/math.o bin/68k.o bin/duart.o
# INCLUDES = bin/malloc.o bin/string.o bin/io.o bin/math.o bin/68k.o bin/easy68k-utils.o

test.o: test.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) test.c -c -o test.o

%.S: %.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(basename $@).c -S -o asm/$(basename $@).S

test.x: test.o crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test.o $(INCLUDES) -o test.srec

monitor.o: monitor.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) monitor.c -c -o monitor.o

monitor.x: monitor.o crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) monitor.o $(INCLUDES) -o monitor.srec

test_malloc: crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test_malloc.c $(INCLUDES) -o test_malloc.srec

test_splitw: crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test_splitw.c $(INCLUDES) -o test_splitw.srec

bin/easy68k-utils.o: utils/easy68k-utils.c
	$(CC) $(CFLAGS) utils/easy68k-utils.c -c -o bin/easy68k-utils.o

bin/malloc.o: utils/malloc.c
	$(CC) $(CFLAGS) utils/malloc.c -c -o bin/malloc.o

bin/duart.o: utils/duart.o
	$(CC) $(CFLAGS) utils/duart.c -c -o bin/duart.o

bin/string.o: utils/string.c
	$(CC) $(CFLAGS) utils/string.c -c -o bin/string.o

bin/math.o: utils/math.c
	$(CC) $(CFLAGS) utils/math.c -c -o bin/math.o

bin/io.o: utils/io.c
	$(CC) $(CFLAGS) utils/io.c -c -o bin/io.o

bin/68k.o: utils/68k.c
	$(CC) $(CFLAGS) utils/68k.c -c -o bin/68k.o

crt0.o: crt0.S
	$(CC) crt0.S -c -o crt0.o

# hello.o and hello.x are just tests on the example compilations.
hello.o: hello.c
	m68k-coff-gcc -m5200 -O4 -fomit-frame-pointer --verbose -Wall -ansi hello.c -c -o hello.o

hello.x: hello.o
	m68k-coff-gcc -m5200  -Wl,-s -Wl,-n -Tsbc5206-srec.ld -Wl,-Map=hello.map --verbose  hello.o   -o hello

clean:
	rm -f *.x *.o *.srec *.map core *.d bin/* asm/utils/* asm/*
