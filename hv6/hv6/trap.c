#include <uapi/machine/cpufunc.h>
#include <uapi/machine/segment.h>
#include <uapi/machine/trap.h>
#include <machine/memlayout.h>
#include <hvm.h>
#include <xapic.h>
#include <libs/riscv.h>

void print_trapframe(struct trap_frame *tf);
void print_regs(struct push_regs* gpr);
bool trap_in_kernel(struct trap_frame *tf);

void trap_init(void)
{
    #if 0///Origin
    size_t i;
    extern void *trap_vectors[];

    for (i = 0; i < countof(idt); ++i)
        set_gate_desc(&idt[i], 0, GDT_CS, trap_vectors[i], KERNEL_PL);
    lidt(&idt_desc);
    #endif
    extern void __alltraps(void);
    /* Set sscratch register to 0, indicating to exception vector that we are
     * presently executing in the kernel */
    write_csr(sscratch, 0);
    /* Set the exception vector address */
    write_csr(stvec, &__alltraps);
    /* Allow kernel to access user memory */
    set_csr(sstatus, SSTATUS_SUM);
    /* Allow keyboard interrupt */
    set_csr(sie, MIP_SSIP);
}

/* ///
void trap(struct trap_frame *tf, uint8_t nr)
{
    // svm helper for external interrupts
    if (nr >= TRAP_IRQ0) {
        if (hvm_extintr)
            hvm_extintr(nr);
        xapic_eoi();
        return;
    }

    panic("trap %d err %lu on rip 0x%lx addr 0x%lx", nr, tf->err, tf->rip,
          rcr2());
}
*/

void trap(struct trap_frame *tf)
{
    while(1);
}

/* trap_in_kernel - test if trap happened in kernel */
bool
trap_in_kernel(struct trap_frame *tf) {
    return (tf->status & SSTATUS_SPP) != 0;
}

void
print_trapframe(struct trap_frame *tf) {
    libs_cprintf("trapframe at %p\n", tf);
    print_regs(&tf->gpr);
    libs_cprintf("  status   0x%08x\n", tf->status);
    libs_cprintf("  epc      0x%08x\n", tf->epc);
    libs_cprintf("  badvaddr 0x%08x\n", tf->badvaddr);
    libs_cprintf("  cause    0x%08x\n", tf->cause);
}

void
print_regs(struct push_regs* gpr) {
    libs_cprintf("  zero     0x%08x\n", gpr->zero);
    libs_cprintf("  ra       0x%08x\n", gpr->ra);
    libs_cprintf("  sp       0x%08x\n", gpr->sp);
    libs_cprintf("  gp       0x%08x\n", gpr->gp);
    libs_cprintf("  tp       0x%08x\n", gpr->tp);
    libs_cprintf("  t0       0x%08x\n", gpr->t0);
    libs_cprintf("  t1       0x%08x\n", gpr->t1);
    libs_cprintf("  t2       0x%08x\n", gpr->t2);
    libs_cprintf("  s0       0x%08x\n", gpr->s0);
    libs_cprintf("  s1       0x%08x\n", gpr->s1);
    libs_cprintf("  a0       0x%08x\n", gpr->a0);
    libs_cprintf("  a1       0x%08x\n", gpr->a1);
    libs_cprintf("  a2       0x%08x\n", gpr->a2);
    libs_cprintf("  a3       0x%08x\n", gpr->a3);
    libs_cprintf("  a4       0x%08x\n", gpr->a4);
    libs_cprintf("  a5       0x%08x\n", gpr->a5);
    libs_cprintf("  a6       0x%08x\n", gpr->a6);
    libs_cprintf("  a7       0x%08x\n", gpr->a7);
    libs_cprintf("  s2       0x%08x\n", gpr->s2);
    libs_cprintf("  s3       0x%08x\n", gpr->s3);
    libs_cprintf("  s4       0x%08x\n", gpr->s4);
    libs_cprintf("  s5       0x%08x\n", gpr->s5);
    libs_cprintf("  s6       0x%08x\n", gpr->s6);
    libs_cprintf("  s7       0x%08x\n", gpr->s7);
    libs_cprintf("  s8       0x%08x\n", gpr->s8);
    libs_cprintf("  s9       0x%08x\n", gpr->s9);
    libs_cprintf("  s10      0x%08x\n", gpr->s10);
    libs_cprintf("  s11      0x%08x\n", gpr->s11);
    libs_cprintf("  t3       0x%08x\n", gpr->t3);
    libs_cprintf("  t4       0x%08x\n", gpr->t4);
    libs_cprintf("  t5       0x%08x\n", gpr->t5);
    libs_cprintf("  t6       0x%08x\n", gpr->t6);
}
