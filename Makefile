SOURCES	= $(shell find . -name *.m)
JUNK	= *.o *.bin
LSCRIPT	= linker.ld

TARGET	= image

# Compiling and linking arguments
OBJCOPY = objcopy -I binary -O elf32-i386 -B i386
QARGS	= -drive format=raw,index=0,if=floppy,file=$< -boot a -nographic -serial mon:stdio
LD	= ld --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_ -static -nostdlib -T$(LSCRIPT) --oformat binary
MML	= ./mml


# Main make function and cleanup definition
all:		$(TARGET) clean run

clean:
	$(RM) $(JUNK)

# Linking
$(TARGET):	$(SOURCES)
	$(MML) -f $< -d -o $@.o
	$(OBJCOPY) $@.o $@.o
	$(LD) $@.o -o $@.bin
	mv $@.bin bin/

# Emulation
run:		$(shell find . -name *.bin)
	qemu-system-i386 $(QARGS)
