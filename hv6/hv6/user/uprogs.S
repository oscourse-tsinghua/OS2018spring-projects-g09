.section .rodata

.global	_uprogs_hello_start
.global _uprogs_hello_end
_uprogs_hello_start:
	.incbin	"user/uprogs/hello"
_uprogs_hello_end:

.global	_uprogs_calc_start
.global _uprogs_calc_end
_uprogs_calc_start:
	.incbin	"user/uprogs/calc"
_uprogs_calc_end:
