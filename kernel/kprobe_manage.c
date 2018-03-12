#include "kprobe_manage.h"
#include "log_manage.h"
#include "procfs_manage.h"
#include "manage_pt_regs.h"
#include "dataparse.h"
#include "get_path.h"

// #define PROBE_NUM 18

// static struct kprobe kps[PROBE_NUM];

// static char *probe_names[PROBE_NUM] = {"sys_execve", "sys_connect", "sys_bind", "sys_accept",
// "sys_creat", "sys_mkdir", "sys_mkdirat", "sys_link", "sys_rmdir", "sys_init_module",
// "sys_rename", "sys_chmod", "sys_fchmod", "sys_mount", "sys_unlink","sys_unlinkat", "sys_fchmodat", "sys_linkat"};


#define PROBE_NUM 7
static struct kprobe kps[PROBE_NUM];
static char *probe_names[PROBE_NUM] = {"sys_execve", "sys_connect", "sys_accept",
"sys_creat", "sys_mkdir", "sys_rmdir", "sys_rename"};


void mange_regs(const char *syscall, struct pt_regs *regs, char* buf, int len)
{
    if(strcmp(syscall, "sys_write") == 0)
    {
        parse_file_stream(regs, buf, len);
    }else if(strcmp(syscall, "sys_read") == 0)
    {
        parse_file_stream(regs, buf, len);
    }
    else if (strcmp(syscall, "sys_execve") == 0)
    {
        parse_execve(regs, buf, len);
    }
    else if(strcmp(syscall, "sys_connect") == 0)
    {
        parse_sockaddr(regs, buf, len);
    }else if(strcmp(syscall, "sys_bind") == 0)
    {
        parse_sockaddr(regs, buf, len);
    }else if(strcmp(syscall, "sys_accept") == 0)
    {
        parse_accept(regs, buf, len);
    }else if(strcmp(syscall, "sys_creat") == 0)
    {
        parse_creat(regs, buf, len);
    }else if(strcmp(syscall, "sys_mkdir") == 0)
    {
        parse_creat(regs, buf, len);
    }else if(strcmp(syscall, "sys_mkdirat") == 0)
    {
        parse_creatat(regs, buf, len);
    }else if(strcmp(syscall, "sys_unlinkat") == 0)
    {
        parse_creatat(regs, buf, len);
    }
    else if(strcmp(syscall, "sys_fchmodat") == 0)
    {
        parse_creatat(regs, buf, len);
    }
    else if(strcmp(syscall, "sys_rename") == 0)
    {
        parse_rename(regs, buf, len);
    }else if(strcmp(syscall, "sys_chmod") == 0)
    {
        parse_chmod(regs, buf, len);
    }else if(strcmp(syscall, "sys_fchmod") == 0)
    {
        
    }else if(strcmp(syscall, "sys_mount") == 0)
    {
        parse_mount(regs, buf, len);
    }else if(strcmp(syscall, "sys_init_module") == 0)
    {
        parse_module(regs, buf, len);
    }else if(strcmp(syscall, "sys_unlink") == 0)
    {
        parse_rm(regs, buf, len);
    }else if(strcmp(syscall, "sys_rmdir") == 0)
    {
        parse_rm(regs, buf, len);
    }else if(strcmp(syscall, "sys_link") == 0)
    {
        parse_rename(regs, buf, len);
    }else if(strcmp(syscall, "sys_linkat") == 0)
    {
        parse_linkat(regs, buf, len);
    }else
    {
        ;
    }
}


int init_kprobes(void)
{
    int i;
    int ret = 0;
    for(i = 0; i < PROBE_NUM; ++i)
    {
        kps[i].symbol_name = NULL;
    }

    for(i = 0; i < PROBE_NUM; i++)
    {   
        init_kprobe(&kps[i], probe_names[i]);
    }

    for(i = 0; i < PROBE_NUM; i++)
    {
        if(kps[i].symbol_name != NULL)
        {
            ret = register_kprobe(&kps[i]);
            if(ret < 0)
            {
                //printk("register failed, errno:%d\n", ret);
                goto end;
            }
            //printk("resgistry:%s success!\n", kps[i].symbol_name);
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
    for(i = 0; i < PROBE_NUM; i++)
    {
        if(kps[i].symbol_name != NULL)
        {
            unregister_kprobe(&kps[i]);
        }
    }
}


void handle_post(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
    ;
}




int handle_pre(struct kprobe *p, struct pt_regs *regs)
{

    struct log_item *item;
    char *cur_path;

    if(notstart())
    {
        return 0;
    }

    if(is_monitor(current->pid))
    {
        return 0;
    }

    if(isfilted(current->comm))
    {
        return 0;
    }

    item = get_log_item();

    item->pid = current->pid;
    item->ppid = current->parent->pid;
    strcpy(item->syscall, p->symbol_name);
    cur_path = get_absolute_path(current);
    strcpy(item->path, cur_path);
    strcpy(item->name, current->comm);
    strcpy(item->pname, current->parent->comm);
    mange_regs(p->symbol_name, regs, item->buf, LOGSIZE);

    return 0;
}


int handle_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
    return 0;
}


void init_kprobe(struct kprobe *p, char* name)
{
    p->symbol_name = name;
    p->pre_handler = handle_pre;
    p->post_handler = handle_post;
    p->fault_handler = handle_fault;
}
