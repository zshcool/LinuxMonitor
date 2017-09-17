obj-m += antiylm.o
antiylm-y := manage_pt_regs.o logitem.o log_list.o main.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
