#include <stdint.h>
#include <libs/riscv.h>
#include "cpuid.h"
#include "hvm.h"
#include "proc.h"

void svm_init(void);
void vmx_init(void);

void (*hvm_user_init)(void *hvm, uintptr_t user_entry, uintptr_t ulib_entry);
void (*hvm_run_user_init)(void *hvm);
void (*hvm_switch)(void *from_hvm, void *to_hvm);
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

void switch_to(struct context* from, struct context* to);

void riscv_hvm_user_init(void *_hvm, uintptr_t user_entry, uintptr_t ulib_entry)
{
	hvm_t *hvm = _hvm;
	hvm->user_entry = user_entry;
	hvm->ulib_entry = ulib_entry;
}

void riscv_hvm_run_user_init(void *_hvm)
{
	hvm_t *hvm = _hvm;
	uintptr_t cr3 = get_page(get_proc(hvm->pid)->page_table_root);
	libs_cprintf("cr3 = 0x%llx\n", cr3);
	lcr3(cr3);
	hvm_invalidate_tlb(0);
	libs_cprintf("user_entry = 0x%llx ulib_entry = 0x%llx pid = %d\n", hvm->user_entry, hvm->ulib_entry, hvm->pid);

	extern void *syscalls[];
	void (*entry)(void *syscalls[], void (*fn)());
	entry = hvm->ulib_entry;
	entry(syscalls, (void*)hvm->user_entry);
}

void riscv_hvm_set_pid(void *_hvm, pid_t pid)
{
	hvm_t *hvm = _hvm;
	hvm->pid = pid;
}

//void riscv_hvm_switch(void *_hvm, void *stack, register_t cr3, timer_t timer, int launched)
//{
//	hvm_t *hvm = _hvm;
//
//	libs_cprintf("cr3 = 0x%llx\n", cr3);
//	lcr3(cr3);
//	hvm_invalidate_tlb(0);
//	libs_cprintf("user_entry = 0x%llx ulib_entry = 0x%llx pid = %d\n", hvm->user_entry, hvm->ulib_entry, hvm->pid);
//
//	extern void *syscalls[];
//	void (*entry)(void *syscalls[], void (*fn)());
//	entry = hvm->ulib_entry;
//	entry(syscalls, (void*)hvm->user_entry);
////	uintptr_t sstatus = read_csr(sstatus);
////	sstatus &= ~SSTATUS_SPP;
////	write_csr(sstatus, sstatus);
////	write_csr(sepc, main);
////
////	asm volatile ("sret");
//}

void riscv_hvm_switch(void *_from_hvm, void *_to_hvm)
{
	hvm_t* from_hvm = _from_hvm;
	hvm_t* to_hvm = _to_hvm;
	lcr3(get_page(get_proc(to_hvm->pid)->page_table_root));
	switch_to(&from_hvm->context, &to_hvm->context);
}

void riscv_hvm_flush(void *hvm)
{
	// nothing
}

// forkret -- the first kernel entry point of a new thread/process
// NOTE: the addr of forkret is setted in copy_thread function
//       after switch_to, the current proc will execute here.
static void
forkret(void) {
    forkrets(((hvm_t*)get_page(get_proc(current)->hvm))->tf);
}

//// copy_thread - setup the trapframe on the  process's kernel stack top and
////             - setup the kernel entry point and stack of process
//static void
//copy_thread(struct proc_struct *proc, uintptr_t esp, struct trapframe *tf) {
//    proc->tf = (struct trapframe *)(proc->kstack + KSTACKSIZE) - 1;
//    *(proc->tf) = *tf;
//
//    // Set a0 to 0 so a child process knows it's just forked
//    proc->tf->gpr.a0 = 0;
//    proc->tf->gpr.sp = (esp == 0) ? (uintptr_t)proc->tf - 4 : esp;
//
//    proc->context.ra = (uintptr_t)forkret;
//    proc->context.sp = (uintptr_t)(proc->tf);
//}

void riscv_hvm_copy(void *_dst, void *_src, pid_t pid)
{
	hvm_t* dst = (hvm_t*)_dst;
	hvm_t* src = (hvm_t*)_src;
	*dst = *src;
	dst->pid = pid;

	dst->tf = (struct trap_frame *)(get_page(get_proc(dst->pid)->stack) + PAGE_SIZE) - 1;
	*(dst->tf) = *src->tf;
	dst->tf->gpr.a0 = 1;

	dst->tf->gpr.sp = src->tf->gpr.sp;
	dst->context.sp = dst->tf;
	dst->context.ra = forkret;
}

void hvm_init(void)
{
	hvm_user_init = riscv_hvm_user_init;
	hvm_run_user_init = riscv_hvm_run_user_init;
	hvm_switch = riscv_hvm_switch;
	hvm_flush = riscv_hvm_flush;
	hvm_copy = riscv_hvm_copy;
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
