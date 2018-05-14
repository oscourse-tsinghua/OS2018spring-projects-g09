#include <uapi/machine/cpufunc.h>
#include <uapi/machine/segment.h>
#include <uapi/machine/trap.h>
#include <machine/memlayout.h>
#include <hvm.h>
#include <xapic.h>
#include <libs/riscv.h>

static struct gate_desc idt[256] = {{0}};

static struct pseudo_desc idt_desc = {
    sizeof(idt) - 1, (uint64_t)idt,
};

void trap_init(void)
{
    #if 0//Origin
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

void trap(struct trap_frame *tf, uint8_t nr)
{
    /* svm helper for external interrupts */
    if (nr >= TRAP_IRQ0) {
        if (hvm_extintr)
            hvm_extintr(nr);
        xapic_eoi();
        return;
    }

    panic("trap %d err %lu on rip 0x%lx addr 0x%lx", nr, tf->err, tf->rip,
          rcr2());
}
