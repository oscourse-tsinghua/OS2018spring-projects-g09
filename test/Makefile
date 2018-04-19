
ifndef GCCPREFIX
GCCPREFIX := riscv64-unknown-elf-
endif

GDB		:= $(GCCPREFIX)gdb

CC		:= $(GCCPREFIX)gcc
CFLAGS  := -mcmodel=medany -std=gnu99 -Wno-unused -Werror
CFLAGS	+= -fno-builtin -Wall -O2 -nostdinc
CFLAGS	+= -fno-stack-protector -ffunction-sections -fdata-sections
CFLAGS  += -I. -Ilibs
CTYPE	:= c S

LD      := $(GCCPREFIX)ld
LDFLAGS	:= -m elf64lriscv
LDFLAGS	+= -nostdlib --gc-sections

OBJCOPY := $(GCCPREFIX)objcopy
OBJDUMP := $(GCCPREFIX)objdump

all: build build/test.elf build/test.s build/test.img build/test.bin

build:
	mkdir build

build/test.elf: build/test.o test.lds
	$(LD) $(LDFLAGS) -T test.lds -o $@ $<

%.s: %.elf
	$(OBJDUMP) -d $< > $@

%.bin: %.elf
	cd ../riscv-pk && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	../configure --prefix=$(RISCV) --host=riscv64-unknown-elf --with-payload=../../test/$<  --disable-fp-emulation --enable-logo && \
	make && \
	cp bbl ../../test/$@

%.img: %.bin
	$(OBJCOPY) -O binary $< $@

.PHONY : run
run: all
	-riscvemu test.cfg

build/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
