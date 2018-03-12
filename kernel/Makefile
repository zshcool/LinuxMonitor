obj-m += antiylm.o
antiylm-y := get_path.o manage_pt_regs.o  log_list.o log_manage.o dataparse.o kprobe_manage.o procfs_manage.o main.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
