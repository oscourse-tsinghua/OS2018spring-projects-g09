riscv64-unknown-elf-gdb -ex "set arch riscv" -ex "symbol rot13-64" -ex "target remote 0.0.0.0:3333" -ex "set riscv use_compressed_breakpoint off" -ex "print wait" -ex "print wait=0" -ex "b 22" -ex "c"

