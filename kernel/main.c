/*
antiy honeypot project
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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>
#include <linux/vmalloc.h>
#include <linux/timex.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/poll.h>


#include "log_list.h"
#include "manage_pt_regs.h"


#define MODULE_NAME "[antiylm]"

#define MAX_BLOCK 50

static int total_block = 0;
static struct kprobe kp;
static struct logblock *listhead;
static struct logblock *curblock;
static struct logblock *cursorblock;
static int cursor = 0;
static DECLARE_WAIT_QUEUE_HEAD(log_queue); 

static struct proc_dir_entry *root_entry;
static struct proc_dir_entry *log_entry;
static struct proc_dir_entry *registry_entry;

static int registry_pid = -1;


int handler_pre(struct kprobe *p, struct pt_regs *regs)
{

    //printk(MODULE_NAME "pid:%d,ppid:%d,name:%s", current->pid, current->parent->pid, current->comm);

    return 0;
}


void handler_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    struct log_item *item;    

    if(current->pid == registry_pid)
    {
        printk("monitor process filter!\n");
        return;
    }

    item = init_log_item();
    curblock->items[curblock->index] = item;
    
    item->pid = current->pid;
    item->ppid = current->parent->pid;
    char **argv = (char**)get_arg2(regs);
    int count = 0;
    char **tmp = argv;
    while(*tmp != NULL)
    {
        printk("%d:%s", count, *tmp);
        tmp++;
        count++;
    }
    printk("%s\n", get_arg1(regs));
    printk("exe:%s, argc:%d!\n", *((char**)get_arg2(regs)+1), count);

    if (++(curblock->index) < MAX_ITEM)
    {
        ;
    }
    else{
        curblock = insert_new_log_block(curblock);
        total_block++;

        if(total_block > MAX_BLOCK)
        {
            struct logblock *tmp;
            //if user visit is listhead, move it next
            if(curblock == listhead)
            {
                if(curblock == listhead)
                {
                    curblock = listhead->next;
                    cursor = 0;
                }
            }
            tmp = listhead;
            listhead = listhead->next;
            
            destory_block(tmp);
        }
    }
    printk("func:%s", p->symbol_name);
    printk(MODULE_NAME "log");
}


int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
    return 0;
}


static ssize_t read_log(struct file *f , char __user *buf, size_t len, loff_t *loff)
{
    ssize_t size = sizeof(struct log_item);
    int ret;

    if(len != size) return -EINVAL;

    if(cursor < cursorblock->index)
    {
        struct log_item* item = cursorblock->items[cursor];

        //log
        struct log_item* logbuf = (struct log_item*)buf;
        ret = copy_to_user(buf, item, size);
        size -= ret;

        //move the cursor to next log item
        cursor++;

        //has finshed to get the block's logs
        if(cursor >= MAX_ITEM)
        {
            cursorblock = cursorblock->next;
            cursor = 0;
        }

    }else{
        //hasn't upodate log
printk("noupdate curosr:%d, block:%d", cursor, cursorblock->index);
        size = 0;
    }

    return size;
}


static unsigned int log_poll(struct file *file, struct poll_table_struct *table)
{
    unsigned int mask = 0;
printk("8888");
    poll_wait(file, &log_queue, table);
    if(cursor < cursorblock->index)
    {
        mask |= POLLIN | POLLRDNORM;
    }

    return mask;
}


static ssize_t read_registry(struct file *f , char __user *buf, size_t len, loff_t *loff)
{
    int ret;
    ssize_t size = sizeof(registry_pid);
 
    ret = copy_to_user(buf, &registry_pid, size);
    size -= ret;

    return size;
}


static ssize_t write_registry(struct file *f , const char __user *buf, size_t len, loff_t *loff)
{
    int ret;
    ssize_t size = sizeof(registry_pid);
    if(len < size)
        return -1;
 
    ret = copy_from_user(&registry_pid, buf, sizeof(registry_pid));
    size -= ret;

    printk("update registry_pid:%d", registry_pid);

    return size;
}



static const struct file_operations log_fops = {
    .owner = THIS_MODULE,
    .read = read_log,
    .poll = log_poll,
   };


static const struct file_operations reg_fops = {
    .owner = THIS_MODULE,
    .read = read_registry,
    .write = write_registry,
   };


static int __init init_mod(void)
{   
    int ret;

    listhead = init_log_block();
    curblock = listhead;
    cursorblock = listhead;
    printk("Hello, from the kernell..\n");
    kp.symbol_name = "sys_execve";
    kp.pre_handler = (void*)handler_pre;
    kp.post_handler = (void*)handler_post;
    kp.fault_handler = (void*)handler_fault;

    root_entry = proc_mkdir("antiylm", NULL);
    if (root_entry == NULL)
    {
        printk("create proc dir antiylm failed");
        return -EFAULT;
    }

    log_entry = proc_create("lmlog", 0, root_entry, &log_fops);
    registry_entry = proc_create("registry", 0, root_entry, &reg_fops);
    if (log_entry == NULL || registry_entry == NULL)
    {
        printk("registry failed!");
        remove_proc_entry("lmlog", root_entry);
        remove_proc_entry("registry", root_entry);
        remove_proc_entry("antiylm", NULL);
        return -EFAULT;
    }

    ret = register_kprobe(&kp);
    if (ret < 0){
        printk("register failed\n");
        return ret;
    }    

    printk("registry success!\n");

    return 0;
}

static void __exit cleanup_mod(void)
{
    unregister_kprobe(&kp);
    printk("good bye kernel...\n");
    remove_proc_entry("lmlog", root_entry);
    remove_proc_entry("registry", root_entry);
    remove_proc_entry("antiylm", NULL);
    remove_block(listhead);   
}

MODULE_LICENSE("GPL");
module_init(init_mod);
module_exit(cleanup_mod);




