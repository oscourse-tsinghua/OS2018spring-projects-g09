#pragma once

#include <uapi/cdefs.h>

#define TRAP_DE 0  /* divide error */
#define TRAP_DB 1  /* debug */
#define TRAP_NMI 2 /* non-maskable interrupt */
#define TRAP_BP 3  /* breakpoint */
#define TRAP_OF 4  /* overflow */
#define TRAP_BR 5  /* bound range exceeded */
#define TRAP_UD 6  /* invalid opcode */
#define TRAP_NM 7  /* device not available */
#define TRAP_DF 8  /* double fault */
/* 9	reserved */
#define TRAP_TS 10 /* invalid TSS */
#define TRAP_NP 11 /* segment not present */
#define TRAP_SS 12 /* stack exception */
#define TRAP_GP 13 /* general protection fault */
#define TRAP_PF 14 /* page fault */
/* 15	reserved */
#define TRAP_MF 16 /* x87 FPU floating point */
#define TRAP_AC 17 /* aligment check */
#define TRAP_MC 18 /* machine check */
#define TRAP_XF 19 /* SIMD floating point */
#define TRAP_VE 20 /* virtualization */
#define TRAP_VC 29 /* VMM communication */
#define TRAP_SX 30 /* security */

#define TRAP_IRQ0 32

#ifndef __ASSEMBLER__

struct push_regs {
    uintptr_t zero;  // Hard-wired zero
    uintptr_t ra;    // Return address
    uintptr_t sp;    // Stack pointer
    uintptr_t gp;    // Global pointer
    uintptr_t tp;    // Thread pointer
    uintptr_t t0;    // Temporary
    uintptr_t t1;    // Temporary
    uintptr_t t2;    // Temporary
    uintptr_t s0;    // Saved register/frame pointer
    uintptr_t s1;    // Saved register
    uintptr_t a0;    // Function argument/return value
    uintptr_t a1;    // Function argument/return value
    uintptr_t a2;    // Function argument
    uintptr_t a3;    // Function argument
    uintptr_t a4;    // Function argument
    uintptr_t a5;    // Function argument
    uintptr_t a6;    // Function argument
    uintptr_t a7;    // Function argument
    uintptr_t s2;    // Saved register
    uintptr_t s3;    // Saved register
    uintptr_t s4;    // Saved register
    uintptr_t s5;    // Saved register
    uintptr_t s6;    // Saved register
    uintptr_t s7;    // Saved register
    uintptr_t s8;    // Saved register
    uintptr_t s9;    // Saved register
    uintptr_t s10;   // Saved register
    uintptr_t s11;   // Saved register
    uintptr_t t3;    // Temporary
    uintptr_t t4;    // Temporary
    uintptr_t t5;    // Temporary
    uintptr_t t6;    // Temporary
};

struct trap_frame {
    struct push_regs gpr;
    uintptr_t status;
    uintptr_t epc;
    uintptr_t badvaddr;
    uintptr_t cause;
};

#endif /* !__ASSEMBLER__ */
