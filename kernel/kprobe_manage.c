#include "kprobe_manage.h"
#include "log_manage.h"
#include "procfs_manage.h"
#include "manage_pt_regs.h"

static struct kprobe kps[MAX_PROBES];
static int count = 0;

static char *probe_names[] = {"sys_execve"};


int init_kprobes(void)
{
    int i, probe_num;
    int ret = 0;
    for(i = 0; i < MAX_PROBES; ++i)
    {
        kps[i].symbol_name = NULL;
    }

    //probe_names is an array
    probe_num = 1;//sizeof(probe_names);
    printk("default probe_num:%d\n", probe_num);

    if((probe_num > 0))
    {
        for(i = 0; i < probe_num; i++)
        {   
            //kps[count] = (struct kprobe*)kmalloc(sizeof(struct kprobe), GFP_KERNEL);
            init_kprobe(&kps[count], probe_names[i], handle_post);
            count++;
        }
    }
    
    for(i = 0; i < MAX_PROBES; i++)
    {
        if(kps[i].symbol_name != NULL)
        {
            printk("resgistry:%s", kps[i].symbol_name);
            ret = register_kprobe(&kps[i]);
            if(ret < 0)
            {
                printk("register failed, errno:%d\n", ret);
                goto end;
            }
        }
    }
   
    ret = 0;

end:
    if(ret < 0)
        destroy_kprobes();

    return ret;
}


void destroy_kprobes(void)
{
    int i;
    for(i = 0; i < MAX_PROBES; i++)
    {
        if(kps[i].symbol_name != NULL)
        {
            unregister_kprobe(&kps[i]);
            //kfree(&kps[i]);
        }
    }
}





int handle_pre(struct kprobe *p, struct pt_regs *regs)
{

    //printk(MODULE_NAME "pid:%d,ppid:%d,name:%s", current->pid, current->parent->pid, current->comm);

    return 0;
}


void handle_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    struct log_item *item;    

    if(is_monitor(current->pid))
    {
        printk("monitor process filter!\n");
        return;
    }

    item = get_log_item();
    
    item->pid = current->pid;
    item->ppid = current->parent->pid;

    char **argv = (char**)get_arg2(regs);
    int argc = 0;
    char **tmp = argv;
    while(*tmp != NULL)
    {
        printk("%d:%s", argc, *tmp);
        tmp++;
        argc++;
    }
    printk("%s\n", get_arg1(regs));
    printk("exe:%s, argc:%d!\n", *((char**)get_arg2(regs)+1), argc);


    printk("func:%s", p->symbol_name);
}


/*
void handle_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    struct log_item *item;    

    if(current->pid == registry_pid)
    {
        printk("monitor process filter!\n");
        return;
    }

    item = 1//d
    
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


    printk("func:%s", p->symbol_name);
    printk(MODULE_NAME "log");
}
*/

int handle_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
    return 0;
}


void init_kprobe(struct kprobe *p, char* name, posthandle handle)
{
    printk("name:%s", name);
    p->symbol_name = "sys_execve";
    p->pre_handler = handle_pre;
    p->post_handler = handle;
    p->fault_handler = handle_fault;
}
