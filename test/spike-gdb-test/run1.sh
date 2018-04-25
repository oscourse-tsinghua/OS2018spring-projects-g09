riscv64-unknown-elf-gcc -g -Og -o rot13-64.o -c rot13.c
riscv64-unknown-elf-gcc -g -Og -T spike.lds -nostartfiles -o rot13-64 rot13-64.o
spike --rbb-port=9824 -m0x10000000:0x20000 rot13-64
riscv64-unknown-elf-objdump -D rot13-64 > rot13-64.asm

