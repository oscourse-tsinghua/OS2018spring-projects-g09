#include <uapi/machine/mmu.h>

.section .text

.global	_start
#if 0
///
_start:
	movq	$0, %rbp
	pop	%rdi		/* argc */
	movq	%rsp, %rsi	/* argv */
	push	%rbp		/* align the stack */
	call	main
#endif
_start:
spin:
	call	exit
	j	spin
