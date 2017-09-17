#include "procfs_manage.h"
#include "log_manage.h"


static DECLARE_WAIT_QUEUE_HEAD(log_queue); 

static struct proc_dir_entry *root_entry;
static struct proc_dir_entry *log_entry;
static struct proc_dir_entry *registry_entry;

static int registry_pid = -1;


static ssize_t read_log(struct file *f , char __user *buf, size_t len, loff_t *loff)
{
    ssize_t size = sizeof(struct log_item);
    int ret;
    
    printk("size:%d", size);
    printk("len:%d", len);
        

    if(len != size) 
        return -EINVAL;

    struct log_item* item = fetch_log();

    if(item == NULL)
    {
        size = 0;
    }else{
        //log
        struct log_item* logbuf = (struct log_item*)buf;
        ret = copy_to_user(buf, item, size);
        size -= ret;
    }

    return size;
}


static unsigned int log_poll(struct file *file, struct poll_table_struct *table)
{
    unsigned int mask = 0;
    printk("8888");
    poll_wait(file, &log_queue, table);
    if(has_new_log())
    {
        printk("new");
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


int registry_proc_fs(void)
{
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
 
    printk("registry proc success!\n");

    return 0;
}

void registry_fs_out(void)
{
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

