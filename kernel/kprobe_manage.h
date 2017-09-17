#ifndef KPROBE_MANAGE_H_
#define KPROBE_MANAGE_H_

#include "common.h"

#define MAX_PROBES 20

typedef void(*posthandle)(struct kprobe*, struct pt_regs*, unsigned long);

int init_kprobes(void);

void destroy_kprobes(void);

int handle_pre(struct kprobe *p, struct pt_regs *regs);
int handle_fault(struct kprobe *p, struct pt_regs *regs, int trapnr);

void handle_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags);

void init_kprobe(struct kprobe *p, char* name, posthandle handle);

#endif
