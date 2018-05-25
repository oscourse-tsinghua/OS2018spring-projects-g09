#include <uapi/machine/cpufunc.h>
#include <uapi/machine/segment.h>
#include <uapi/machine/trap.h>
#include <machine/memlayout.h>
#include <hvm.h>
#include <xapic.h>
#include <syscall.h>
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

void interrupt_handler(struct trap_frame *tf) {
    intptr_t cause = (tf->cause << 1) >> 1;
    switch (cause) {
        case IRQ_U_SOFT:
            libs_cprintf("User software interrupt\n");
            break;
        case IRQ_S_SOFT:
            libs_cprintf("Supervisor software interrupt\n");
            // serial_intr();
            // dev_stdin_write(cons_getc());
            break;
        case IRQ_H_SOFT:
            libs_cprintf("Hypervisor software interrupt\n");
            break;
        case IRQ_M_SOFT:
            libs_cprintf("Machine software interrupt\n");
            break;
        case IRQ_U_TIMER:
            libs_cprintf("User timer interrupt\n");
            break;
        case IRQ_S_TIMER:
            // "All bits besides SSIP and USIP in the sip register are
            // read-only." -- privileged spec1.9.1, 4.1.4, p59
            // In fact, Call sbi_set_timer will clear STIP, or you can clear it
            // directly.
            // clear_csr(sip, SIP_STIP);
            // clock_set_next_event();
            // ++ticks;
            // run_timer_list();

            // serial_intr();
            // dev_stdin_write(cons_getc());
            break;
        case IRQ_H_TIMER:
            libs_cprintf("Hypervisor software interrupt\n");
            break;
        case IRQ_M_TIMER:
            libs_cprintf("Machine software interrupt\n");
            break;
        case IRQ_U_EXT:
            libs_cprintf("User external interrupt\n");
            break;
        case IRQ_S_EXT:
            libs_cprintf("Supervisor external interrupt\n");
            break;
        case IRQ_H_EXT:
            libs_cprintf("Hypervisor external interrupt\n");
            break;
        case IRQ_M_EXT:
            libs_cprintf("Machine external interrupt\n");
            break;
        default:
            print_trapframe(tf);
            break;
    }
}

int syscall(struct trap_frame *tf) {
    int num = tf->gpr.a7;
    uintptr_t a0 = tf->gpr.a0;
    uintptr_t a1 = tf->gpr.a1;
    uintptr_t a2 = tf->gpr.a2;
    uintptr_t a3 = tf->gpr.a3;
    uintptr_t a4 = tf->gpr.a4;
    uintptr_t a5 = tf->gpr.a5;
    uintptr_t a6 = tf->gpr.a6;
    int (*entry)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);

    if (num >= 0 && num < NR_syscalls) {
    	entry = syscalls[num];
    	return entry(a0, a1, a2, a3, a4, a5, a6);
    }
    print_trapframe(tf);
}

void exception_handler(struct trap_frame *tf) {
    int ret = 0;
    switch (tf->cause) {
        case CAUSE_MISALIGNED_FETCH:
            libs_cprintf("Instruction address misaligned\n");
            break;
        case CAUSE_FETCH_ACCESS:
            libs_cprintf("Instruction access fault\n");
            break;
        case CAUSE_ILLEGAL_INSTRUCTION:
            libs_cprintf("Illegal instruction\n");
            break;
        case CAUSE_BREAKPOINT:
            libs_cprintf("Breakpoint\n");
            break;
        case CAUSE_MISALIGNED_LOAD:
            libs_cprintf("Load address misaligned\n");
            break;
        case CAUSE_LOAD_ACCESS:
            libs_cprintf("Load access fault\n");
            break;
        case CAUSE_MISALIGNED_STORE:
            libs_cprintf("AMO address misaligned\n");
            break;
        case CAUSE_STORE_ACCESS:
            libs_cprintf("Store/AMO access fault\n");
            break;
        case CAUSE_USER_ECALL:
            //libs_cprintf("Environment call from U-mode\n");
            tf->epc += 4;
            ret = syscall(tf);
            break;
        case CAUSE_SUPERVISOR_ECALL:
            libs_cprintf("Environment call from S-mode\n");
            tf->epc += 4;
            ret = syscall(tf);
            break;
        case CAUSE_HYPERVISOR_ECALL:
            libs_cprintf("Environment call from H-mode\n");
            break;
        case CAUSE_MACHINE_ECALL:
            libs_cprintf("Environment call from M-mode\n");
            break;
        case CAUSE_FETCH_PAGE_FAULT:
            panic("Instruction page fault\n");
            break;
        case CAUSE_LOAD_PAGE_FAULT:
            libs_cprintf("Load page fault\n");
//            if ((ret = pgfault_handler(tf)) != 0) {
//                print_trapframe(tf);
//                if (current == NULL) {
//                    panic("handle pgfault failed. ret=%d\n", ret);
//                } else {
//                    if (trap_in_kernel(tf)) {
//                        panic("handle pgfault failed in kernel mode. ret=%d\n",
//                              ret);
//                    }
//                    libs_cprintf("killed by kernel.\n");
//                    panic("handle user mode pgfault failed. ret=%d\n", ret);
//                    do_exit(-E_KILLED);
//                }
//            }
            break;
        case CAUSE_STORE_PAGE_FAULT:
            libs_cprintf("Store/AMO page fault\n");
//            if ((ret = pgfault_handler(tf)) != 0) {
//                print_trapframe(tf);
//                if (current == NULL) {
//                    panic("handle pgfault failed. ret=%d\n", ret);
//                } else {
//                    if (trap_in_kernel(tf)) {
//                        panic("handle pgfault failed in kernel mode. ret=%d\n",
//                              ret);
//                    }
//                    libs_cprintf("killed by kernel.\n");
//                    panic("handle user mode pgfault failed. ret=%d\n", ret);
//                    do_exit(-E_KILLED);
//                }
//            }
            break;
        default:
            print_trapframe(tf);
            break;
    }
    tf->gpr.a0 = ret;
}

static inline void trap_dispatch(struct trap_frame* tf) {
    if ((intptr_t)tf->cause < 0) {
        // interrupts
        interrupt_handler(tf);
    } else {
        // exceptions
        exception_handler(tf);
    }
}

void trap(struct trap_frame *tf)
{
	// libs_cprintf("trap in kernel: case = 0x%llx badvaddr = 0x%llx\n", tf->cause, tf->badvaddr);
	trap_dispatch(tf);
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
