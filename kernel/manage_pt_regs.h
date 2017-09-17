#ifndef MANAGE_PT_REGS_H_
#define MANAGE_PT_REGS_H_

#include <asm/ptrace.h>

long get_arg1(struct pt_regs *regs);
long get_arg2(struct pt_regs *regs);
long get_arg3(struct pt_regs *regs);
long get_arg4(struct pt_regs *regs);
long get_arg5(struct pt_regs *regs);

#endif