
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
else
	INCLUDES += bin/srec.o bin/supervisor.o
endif
LDFLAGS = -m68000 -Wl,-n -T$(LINKER_SCRIPT) -nostartfiles -Wl,-Map=$(basename $@).map


monitor.x: monitor.o supervisor/crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) monitor.o $(INCLUDES) -o monitor.srec

monitor.o: monitor.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) monitor.c -c -o monitor.o

test.x: test.o supervisor/crt0.o $(LINKER_SCRIPT) $(INCLUDES) duart_test.o
	$(CC) $(LDFLAGS) test.o $(INCLUDES) duart_test.o -o test.srec

test.o: test.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) test.c -c -o test.o

test_user.x: test_user.o user/crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test_user.o $(INCLUDES) -o test_user.srec

test_user.o: test_user.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) test_user.c -c -o test_user.o

%.S: %.c $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(basename $@).c -S -o asm/$(basename $@).S

test_malloc.x: test_maloc.c supervisor/crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test_malloc.c $(INCLUDES) -o test_malloc.srec

test_splitw.x: test_splitw.c supervisor/crt0.o $(LINKER_SCRIPT) $(INCLUDES)
	$(CC) $(LDFLAGS) test_splitw.c $(INCLUDES) -o test_splitw.srec

bin/easy68k-utils.o: utils/easy68k-utils.c
	$(CC) $(CFLAGS) utils/easy68k-utils.c -c -o bin/easy68k-utils.o

bin/malloc.o: utils/malloc.c
	$(CC) $(CFLAGS) utils/malloc.c -c -o bin/malloc.o

bin/duart.o: utils/duart.c
	$(CC) $(CFLAGS) utils/duart.c -c -o bin/duart.o

bin/string.o: utils/string.c
	$(CC) $(CFLAGS) utils/string.c -c -o bin/string.o

bin/srec.o: utils/srec.c
	$(CC) $(CFLAGS) utils/srec.c -c -o bin/srec.o

bin/supervisor.o: utils/supervisor.c
	$(CC) $(CFLAGS) utils/supervisor.c -c -o bin/supervisor.o

bin/math.o: utils/math.c
	$(CC) $(CFLAGS) utils/math.c -c -o bin/math.o

bin/io.o: utils/io.c
	$(CC) $(CFLAGS) utils/io.c -c -o bin/io.o

bin/68k.o: utils/68k.c
	$(CC) $(CFLAGS) utils/68k.c -c -o bin/68k.o

supervisor/crt0.o: supervisor/crt0.S
	$(CC) supervisor/crt0.S -c -o supervisor/crt0.o

user/crt0.o: user/crt0.S
	$(CC) user/crt0.S -c -o user/crt0.o

duart_test.o: duart_test.S
	$(CC) duart_test.S -c -o duart_test.o

# hello.o and hello.x are just tests on the example compilations.
hello.o: hello.c
	m68k-coff-gcc -m5200 -O4 -fomit-frame-pointer --verbose -Wall -ansi hello.c -c -o hello.o

hello.x: hello.o
	m68k-coff-gcc -m5200  -Wl,-s -Wl,-n -Tsbc5206-srec.ld -Wl,-Map=hello.map --verbose  hello.o   -o hello

clean:
	rm -f *.x *.o *.srec *.map core *.d bin/* asm/utils/*
