/*
linux kernel module
syscall hook
auth by zsh
reference sysmon
*/
//Centos6.5
//#define _k_2_6_32_431_ 1
//Centos7.2
//#define _k_3_10_0_327_ 1
//Ubuntu16.04
//#define _k_4_4_0_21_ 1
//Ubuntu17.04
//#define _k_4_10_0_33_ 1



#include "log_list.h"
#include "manage_pt_regs.h"
#include "log_manage.h"
#include "procfs_manage.h"
#include "kprobe_manage.h"

//static struct logblock *listhead;

static int __init init_mod(void)
{   
    int ret = 0;
    struct logblock *listhead;
    printk("Hello, from the kernell..\n");

    listhead = init_log_list();
    if(listhead == NULL)
    {
        printk("malloc memory failed!\n");
        return -1;
    }

    ret = init_kprobes();
    if (ret != 0)
    {
        printk("registry kprobes failed!\n");
        return ret;
    }

    
    ret = registry_proc_fs();
    if (ret != 0)
    {
        printk("registry proc fs failed!\n");
        return ret;
    }

    return 0;
}

static void __exit cleanup_mod(void)
{
    destroy_kprobes();
    registry_fs_out();
    destroy_log_list();
    printk("good bye kernel...\n");
}

MODULE_LICENSE("GPL");
module_init(init_mod);
module_exit(cleanup_mod);




