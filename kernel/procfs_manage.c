#include "procfs_manage.h"
#include "log_manage.h"
#include <linux/slab.h>
#include <linux/string.h>


static DECLARE_WAIT_QUEUE_HEAD(log_queue); 

static struct proc_dir_entry *root_entry;
static struct proc_dir_entry *log_entry;
static struct proc_dir_entry *registry_entry;
static struct proc_dir_entry *filter_entry;


static int registry_pid = -1;
static int filter_num = 0;
static char filter_names[MAX_FILTER_NUM][NAMESIZE];


static ssize_t read_log(struct file *f , char __user *buf, size_t len, loff_t *loff)
{
    int ret;
    struct log_item* item;
    ssize_t size = sizeof(struct log_item);

    if(len != size) 
        return -EINVAL;

    item = fetch_log();

    if(item == NULL)
    {
        size = 0;
    }else{
        //log
        ret = copy_to_user(buf, item, size);
        size -= ret;
    }

    return size;
}


static unsigned int log_poll(struct file *file, struct poll_table_struct *table)
{
    unsigned int mask = 0;
    poll_wait(file, &log_queue, table);
    if(has_new_log())
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

    return size;
}



static ssize_t get_filter_num(struct file *f , char __user *buf, size_t len, loff_t *loff)
{
    int ret;
    ssize_t size = sizeof(filter_num);
 
    ret = copy_to_user(buf, &filter_num, size);
    size -= ret;

    return size;
}


static ssize_t add_filter(struct file *f , const char __user *buf, size_t len, loff_t *loff)
{
    int ret;
    char *cur_name;

    if(filter_num >= MAX_FILTER_NUM) return FILTER_RULE_FULL;

    cur_name = filter_names[filter_num];

    ret = copy_from_user(cur_name, buf, len);

    printk("add filter rule:%s\n", filter_names[filter_num]);

    filter_num++;
    return len - ret;
}



static const struct file_operations filter_fops = {
    .owner = THIS_MODULE,
    .read = get_filter_num,
    .write = add_filter,
   };


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


int registry_proc_fs(void)
{
    root_entry = proc_mkdir("antiylm", NULL);
    if (root_entry == NULL)
    {
        printk("create proc dir antiylm failed");
        return -EFAULT;
    }

    filter_entry = proc_create("filter", 0, root_entry, &filter_fops);
    log_entry = proc_create("lmlog", 0, root_entry, &log_fops);
    registry_entry = proc_create("registry", 0, root_entry, &reg_fops);
    if (log_entry == NULL || registry_entry == NULL || filter_entry == NULL)
    {
        printk("registry failed!");
        remove_proc_entry("filter", root_entry);
        remove_proc_entry("lmlog", root_entry);
        remove_proc_entry("registry", root_entry);
        remove_proc_entry("antiylm", NULL);
        return -EFAULT;
    }

    printk("registry proc success!\n");

    return 0;
}


void registry_fs_out(void)
{
    remove_proc_entry("filter", root_entry);    
    remove_proc_entry("lmlog", root_entry);
    remove_proc_entry("registry", root_entry);
    remove_proc_entry("antiylm", NULL);
    
    printk("success remove proc\n");
}


int is_monitor(int pid)
{
    if(pid == registry_pid)
        return 1;
    else
        return 0;
}


int notstart(void)
{
    return registry_pid == -1;
}


int isfilted(char *name)
{
    int i;
    if (filter_num == 0)
        return 0;
    
    for(i = 0; i < filter_num; ++i)
    {
        if(strcmp(filter_names[i], name) == 0)
        {
            return 1;
        }
            
    }

    return 0;
}

