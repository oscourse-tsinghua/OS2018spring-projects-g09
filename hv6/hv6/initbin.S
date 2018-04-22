.section .rodata

.global	_binary_init_start
.global _binary_init_end
_binary_init_start:
	;///.incbin	"init"
	j spin
_binary_init_end:

.global	_binary_ulib_start
.global _binary_ulib_end
_binary_ulib_start:
	;///.incbin	"ulib"
	j spin
_binary_ulib_end:

spin:
	j spin