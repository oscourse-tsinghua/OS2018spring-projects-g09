
ifndef GCCPREFIX
GCCPREFIX := riscv64-unknown-elf-
endif

GDB		:= $(GCCPREFIX)gdb

CC		:= $(GCCPREFIX)gcc
CFLAGS  := -mcmodel=medany -std=gnu99 -Wno-unused -Werror
CFLAGS	+= -fno-builtin -Wall -O2 -nostdinc
CFLAGS	+= -fno-stack-protector -ffunction-sections -fdata-sections
CFLAGS  += -I. -Ilibs -Isrc
CTYPE	:= c S

LD      := $(GCCPREFIX)ld
LDFLAGS	:= -m elf64lriscv
LDFLAGS	+= -nostdlib --gc-sections

OBJCOPY := $(GCCPREFIX)objcopy
OBJDUMP := $(GCCPREFIX)objdump

SRC_FILES = $(wildcard src/*.c)
SRC_OBJS = $(subst src/,build/, $(subst .c,.o, $(SRC_FILES)))
LIBS_FILES = $(wildcard libs/*.c)
LIBS_OBJS = $(subst libs/,build/, $(subst .c,.o, $(LIBS_FILES)))

all: build build/test.elf build/test.s build/test.img build/test.bbl build/test.bbl.s

build:
	mkdir build

build/test.elf: $(SRC_OBJS) $(LIBS_OBJS)
	$(LD) $(LDFLAGS) -T test.lds -o $@ $^

%.s: %.elf
	$(OBJDUMP) -D $< > $@

build/test.bbl.s: build/test.bbl
	$(OBJDUMP) -D $< > $@

%.bbl: %.elf
	cd ../riscv-pk && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	../configure --prefix=$(RISCV) --host=riscv64-unknown-elf --with-payload=../../test/$<  --disable-fp-emulation --enable-logo && \
	make && \
	cp bbl ../../test/$@

%.img: %.bbl
	$(OBJCOPY) -O binary $< $@

.PHONY : run
run: all
	-riscvemu test.cfg

$(LIBS_OBJS) : build/%.o: libs/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(SRC_OBJS) : build/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
