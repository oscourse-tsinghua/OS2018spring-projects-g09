#include <stdint.h>
#include <libs/riscv.h>
#include "cpuid.h"
#include "hvm.h"

void svm_init(void);
void vmx_init(void);

void (*hvm_user_init)(void *hvm, register_t rip);
void (*hvm_switch)(void *hvm, void *stack, register_t cr3, timer_t timer, int launched);
void (*hvm_flush)(void *hvm);
void (*hvm_copy)(void *dst, void *src, pid_t pid);
void (*hvm_set_timer)(void *hvm, timer_t timer);
void (*hvm_set_io_bitmap)(void *hvm, void *addr);
void (*hvm_set_pid)(void *hvm, pid_t pid);
void (*hvm_invalidate_tlb)(pid_t pid);

void (*hvm_preempt)(void);
void (*hvm_fault)(void);
int (*hvm_extintr)(uint8_t irq);

#define SPIN_FUNC(name) \
void spin_##name() { \
	while(1); \
} \

#define SPIN_SET(name) {name = (void*)spin_##name;}

SPIN_FUNC(hvm_user_init)
SPIN_FUNC(hvm_switch)
SPIN_FUNC(hvm_flush)
SPIN_FUNC(hvm_copy)
SPIN_FUNC(hvm_set_timer)
SPIN_FUNC(hvm_set_io_bitmap)
SPIN_FUNC(hvm_set_pid)
SPIN_FUNC(hvm_preempt)
SPIN_FUNC(hvm_fault)
SPIN_FUNC(hvm_extintr)

void riscv_hvm_invalidate_tlb(pid_t pid)
{
	asm("sfence.vma");
}

int libs_cprintf(const char *fmt, ...);
void (*main)();

void riscv_hvm_user_init(void *hvm, register_t rip)
{
	main = rip;
	libs_cprintf("rip = 0x%x\n", rip);
}

void riscv_hvm_set_pid(void *hvm, pid_t pid)
{
	// nothing
}

void riscv_hvm_switch(void *hvm, void *stack, register_t cr3, timer_t timer, int launched)
{
	write_csr(satp, (0x9000000000000000) | (cr3 >> RISCV_PGSHIFT));
	// lcr3(cr3);
	hvm_invalidate_tlb(0);
	libs_cprintf("main = 0x%x\n", main);

	main();
}

void hvm_init(void)
{
	hvm_user_init = riscv_hvm_user_init;
	hvm_switch = riscv_hvm_switch;
	SPIN_SET(hvm_flush);
	SPIN_SET(hvm_copy);
	SPIN_SET(hvm_set_timer);
	SPIN_SET(hvm_set_io_bitmap);
	hvm_set_pid = riscv_hvm_set_pid;
	hvm_invalidate_tlb = riscv_hvm_invalidate_tlb;
	SPIN_SET(hvm_preempt);
	SPIN_SET(hvm_fault);
	SPIN_SET(hvm_extintr);

	///
//    if (cpuid_has(CPUID_FEATURE_SVM))
//        return svm_init();
//
//    if (cpuid_has(CPUID_FEATURE_VMX))
//        return vmx_init();
//
//    panic("hvm: no svm/vmx");
}
