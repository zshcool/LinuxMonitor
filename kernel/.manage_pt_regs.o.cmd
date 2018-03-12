cmd_/home/kernel/manage_pt_regs.o := gcc -Wp,-MD,/home/kernel/.manage_pt_regs.o.d  -nostdinc -isystem /opt/rh/devtoolset-2/root/usr/lib/gcc/x86_64-redhat-linux/4.8.2/include -Iinclude  -I/usr/src/kernels/2.6.32-696.16.1.el6.x86_64/include/uapi -I/usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include -Iarch/include/generated -Iinclude -include /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/include/linux/kconfig.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_AVX=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=2048 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -fconserve-stack  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(manage_pt_regs)"  -D"KBUILD_MODNAME=KBUILD_STR(antiylm)" -D"DEBUG_HASH=43" -D"DEBUG_HASH2=27" -c -o /home/kernel/.tmp_manage_pt_regs.o /home/kernel/manage_pt_regs.c

deps_/home/kernel/manage_pt_regs.o := \
  /home/kernel/manage_pt_regs.c \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/include/linux/kconfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /home/kernel/manage_pt_regs.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/ptrace.h \
    $(wildcard include/config/x86/32.h) \
    $(wildcard include/config/x86/debugctlmsr.h) \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/types.h \
  include/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/posix_types.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/posix_types_64.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/ptrace-abi.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/vm86.h) \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/segment.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/paravirt.h) \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
    $(wildcard include/config/x86/vsmp.h) \
  include/linux/linkage.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/stringify.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/page_types.h \
  include/linux/const.h \
  /usr/src/kernels/2.6.32-696.16.1.el6.x86_64/arch/x86/include/asm/page_64_types.h \
    $(wildcard include/config/physical/start.h) \
    $(wildcard include/config/physical/align.h) \
    $(wildcard include/config/flatmem.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \

/home/kernel/manage_pt_regs.o: $(deps_/home/kernel/manage_pt_regs.o)

$(deps_/home/kernel/manage_pt_regs.o):
