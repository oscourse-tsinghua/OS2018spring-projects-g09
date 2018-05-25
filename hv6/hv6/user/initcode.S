#include "memlayout.h"

.section .text

.global	_start
_start:
	;la	sp, stack_top
	call	main

.section .bss
.balign	PAGE_SIZE
	.space	USTACK_SIZE
stack_top:
