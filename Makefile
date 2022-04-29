SOURCES = $(shell find src/. -name *.m)
JUNK	= *.o
TARGET	= a

MML	= ./mml
OBJCOPY = objcopy -I binary -O elf32-i386 -B i386
LD	= ld -m elf_i386 -Ttext 0x0 -o 

all:	$(TARGET) clean


clean:
	$(RM) ${JUNK}


$(TARGET):	$(SOURCES)
	$(MML) -f $< -d -o $@.o
	$(OBJCOPY) $@.o $@.o
	$(LD) $@.elf $@.o
	mv $@.elf bin/
