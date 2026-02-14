# OS-Mini AI Kernel Makefile
CC = gcc
LD = ld

CFLAGS = -m32 -O2 -Wall -Iinclude
LDFLAGS = -m elf_i386 -T linker.ld --oformat elf32-i386

# Include lib.c and hal.c
CSRCS = core/kernel.c core/pfa.c core/process.c core/scheduler.c core/paging_advanced.c drivers/ramfs.c gui/font.c gui/framebuffer.c lib.c arch/x86/hal.c
COBJS = $(CSRCS:.c=.o)

TARGET = kernel.bin
ELF_TARGET = kernel.elf

.PHONY: all clean

all: $(ELF_TARGET) $(TARGET)

$(ELF_TARGET): $(COBJS) linker.ld
	$(LD) $(LDFLAGS) -o $(ELF_TARGET) $(COBJS)

$(TARGET): $(ELF_TARGET)
	objcopy -O binary $(ELF_TARGET) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COBJS) $(ELF_TARGET) $(TARGET)

