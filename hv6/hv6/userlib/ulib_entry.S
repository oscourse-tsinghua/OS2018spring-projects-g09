#include <uapi/machine/mmu.h>

.section .head.text

.global	_start
_start:
	addi	sp,sp,-16
	sd		s0,8(sp)
	sd		ra,0(sp)
	addi	s0,sp,16

	la		sp, ulib_stack_top
	call	ulib_init
	mv		sp, s0

	ld		s0,-8(sp)
	ld		ra,-16(sp)
	ret

#if 0
_start:
	push	%rbp
	movq	%rsp, %rbp
	movq	$ulib_stack_top, %rsp
	call	ulib_init
	movq	%rbp, %rsp
	pop	%rbp
	ret
#endif

.section .bss
.balign	PAGE_SIZE
.global	ulib_stack_top
	.space	SZ_64K
ulib_stack_top:
