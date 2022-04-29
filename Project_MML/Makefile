SOURCES  = $(shell find src/. -name *.c)

JUNK	 = $(shell find */. -name *.o) *.bin
CFLAGS	 = -masm=intel -march=i386 -Os


all:	mml clean

clean:
	$(RM) ${JUNK}

mml:	$(SOURCES)
	$(CC) ${CFLAGS} $^ -o $@
	mv $@ bin/
