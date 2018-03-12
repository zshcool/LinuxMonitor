#include "manage_pt_regs.h"

long unsigned int get_arg1(struct pt_regs *regs)
{
#if defined(__x86_64__)
    return regs->di;
#elif defined(__x86__)
    return regs->di;
#elif defined(__i386)
    return regs-ebx;
#endif
}

long unsigned int get_arg2(struct pt_regs *regs)
{
#if defined(__x86_64__)
    return regs->si;
#elif defined(__x86__)
    return regs->si;
#elif defined(__i386)
    return regs-ecx;
#endif
}

long unsigned int get_arg3(struct pt_regs *regs)
{
#if defined(__x86_64__)
    return regs->dx;
#elif defined(__x86__)
    return regs->dx;
#elif defined(__i386)
    return regs-edx;
#endif
}

long unsigned int get_arg4(struct pt_regs *regs)
{
#if defined(__x86_64__)
    return regs->r10;
#elif defined(__x86__)
    return regs->r10;
#elif defined(__i386)
    return regs-esi;
#endif 
}

long unsigned int get_arg5(struct pt_regs *regs)
{
#if defined(__x86_64__)
    return regs->r8;
#elif defined(__x86__)
    return regs->r8;
#elif defined(__i386)
    return regs-edi;
#endif 
}



