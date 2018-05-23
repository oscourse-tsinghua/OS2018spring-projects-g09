#include "memlayout.h"

.section .text

.global	_start
#if 0
_start:
	movq	$stack_top, %rsp
	/* ulib entry point */
	movq	$0xffffffff80000000, %rax
	call	*%rax
	/* return from ulib_init */
	call	main
#endif
_start:
	la	sp, stack_top
	/* ulib entry point */
	li	a5, 0xffffffff80000000
	jalr	a5
	/* return from ulib_init */
	call	main

.section .bss
.balign	PAGE_SIZE
	.space	USTACK_SIZE
stack_top:
