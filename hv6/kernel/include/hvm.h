#pragma once

#include <uapi/cdefs.h>
#include <uapi/machine/trap.h>

struct trap_regs;

struct context {
    uintptr_t ra;
    uintptr_t sp;
    uintptr_t s0;
    uintptr_t s1;
    uintptr_t s2;
    uintptr_t s3;
    uintptr_t s4;
    uintptr_t s5;
    uintptr_t s6;
    uintptr_t s7;
    uintptr_t s8;
    uintptr_t s9;
    uintptr_t s10;
    uintptr_t s11;
};

typedef struct
{
	uintptr_t user_entry;
	uintptr_t ulib_entry;
	pid_t pid;
	struct context context;
	struct trap_frame *tf;
} hvm_t;

void hvm_init(void);
extern void (*hvm_user_init)(void *hvm, uintptr_t user_entry, uintptr_t ulib_entry);
extern void (*hvm_run_user_init)(void *hvm);
extern void (*hvm_switch)(void *from_hvm, void *to_hvm);
extern void (*hvm_flush)(void *hvm);
extern void (*hvm_copy)(void *dst, void *src, pid_t pid);
extern void (*hvm_set_timer)(void *hvm, timer_t timer);
extern void (*hvm_set_io_bitmap)(void *hvm, void *addr);
extern void (*hvm_set_pid)(void *hvm, pid_t pid);
extern void (*hvm_invalidate_tlb)(pid_t pid);

/* callback into OS */
extern void (*hvm_preempt)(void);
extern void (*hvm_fault)(void);
extern int (*hvm_extintr)(uint8_t irq);
