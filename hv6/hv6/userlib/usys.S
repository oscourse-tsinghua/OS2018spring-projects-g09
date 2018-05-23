#include "syscall.h"

/*
#define SYSCALL(sym)						\
	.global	sys_##sym;					\
	sys_##sym:						\
		movq	$SYS_##sym, %rax;			\
		vmcall;						\
		ret
*/
#define SYSCALL(sym)		\
.global	sys_##sym;			\
sys_##sym:					\
	ld		a7, ulib_syscalls;	\
	addi	a7,a7,8*SYS_##sym;	\
	ld		a7, 0(a7);			\
	jr		a7;					\

SYSCALL(map_page_desc)
SYSCALL(map_pml4)
SYSCALL(map_proc)
SYSCALL(map_dev)
SYSCALL(map_file)
SYSCALL(alloc_pdpt)
SYSCALL(alloc_pd)
SYSCALL(alloc_pt)
SYSCALL(alloc_frame)
SYSCALL(copy_frame)
SYSCALL(protect_frame)
SYSCALL(free_pdpt)
SYSCALL(free_pd)
SYSCALL(free_pt)
SYSCALL(free_frame)
SYSCALL(reclaim_page)
SYSCALL(set_proc_name)
SYSCALL(set_runnable)
SYSCALL(switch)
SYSCALL(kill)
SYSCALL(reap)
SYSCALL(reparent)
SYSCALL(send)
SYSCALL(recv)
SYSCALL(reply_wait)
SYSCALL(call)
SYSCALL(create)
SYSCALL(close)
SYSCALL(dup)
SYSCALL(dup2)
SYSCALL(lseek)
SYSCALL(map_pcipage)
SYSCALL(alloc_iommu_root)
SYSCALL(alloc_iommu_pdpt)
SYSCALL(alloc_iommu_pd)
SYSCALL(alloc_iommu_pt)
SYSCALL(alloc_iommu_frame)
SYSCALL(map_iommu_frame)
SYSCALL(reclaim_iommu_frame)
SYSCALL(reclaim_iommu_root)
SYSCALL(alloc_vector)
SYSCALL(reclaim_vector)
SYSCALL(alloc_intremap)
SYSCALL(reclaim_intremap)
SYSCALL(ack_intr)
SYSCALL(alloc_io_bitmap)
SYSCALL(alloc_port)
SYSCALL(reclaim_port)
SYSCALL(debug_exit)
SYSCALL(debug_print_console)
SYSCALL(debug_print_screen)
SYSCALL(debug_dmesg)
SYSCALL(debug_sysctl)

.global	exec
exec:
	j	exec

.global fexec
fexec:
	j	fexec
