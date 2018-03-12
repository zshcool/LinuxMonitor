#ifndef MANAGE_PT_REGS_H_
#define MANAGE_PT_REGS_H_

#include <asm/ptrace.h>

long unsigned int get_arg1(struct pt_regs *regs);
long unsigned int get_arg2(struct pt_regs *regs);
long unsigned int get_arg3(struct pt_regs *regs);
long unsigned int get_arg4(struct pt_regs *regs);
long unsigned int get_arg5(struct pt_regs *regs);

#endif