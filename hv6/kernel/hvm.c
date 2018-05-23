#include <stdint.h>
#include <libs/riscv.h>
#include "cpuid.h"
#include "hvm.h"

void svm_init(void);
void vmx_init(void);

void (*hvm_user_init)(void *hvm, uintptr_t user_entry, uintptr_t ulib_entry);
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
	asm volatile ("sfence.vma");
}

int libs_cprintf(const char *fmt, ...);

typedef struct
{
	uintptr_t user_entry;
	uintptr_t ulib_entry;
	pid_t pid;
} hvm_t;

void riscv_hvm_user_init(void *_hvm, uintptr_t user_entry, uintptr_t ulib_entry)
{
	hvm_t *hvm = _hvm;
	hvm->user_entry = user_entry;
	hvm->ulib_entry = ulib_entry;
}

void riscv_hvm_set_pid(void *_hvm, pid_t pid)
{
	hvm_t *hvm = _hvm;
	hvm->pid = pid;
}

void riscv_hvm_switch(void *_hvm, void *stack, register_t cr3, timer_t timer, int launched)
{
	hvm_t *hvm = _hvm;

	libs_cprintf("cr3 = 0x%llx\n", cr3);
	lcr3(cr3);
	hvm_invalidate_tlb(0);
	libs_cprintf("user_entry = 0x%llx ulib_entry = 0x%llx pid = %d\n", hvm->user_entry, hvm->ulib_entry, hvm->pid);

	extern void *syscalls[];
	void (*entry)(void *syscalls[], void (*fn)());
	entry = hvm->ulib_entry;
	entry(syscalls, (void*)hvm->user_entry);
//	uintptr_t sstatus = read_csr(sstatus);
//	sstatus &= ~SSTATUS_SPP;
//	write_csr(sstatus, sstatus);
//	write_csr(sepc, main);
//
//	asm volatile ("sret");
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
