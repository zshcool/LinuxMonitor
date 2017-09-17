#include <linux/slab.h>

#include "logitem.h"

/*
struct log_item* init_log_item(void)
{
    struct log_item* item = (struct log_item *)kmalloc(sizeof(struct log_item), GFP_KERNEL);
    item->pid = -1;
    item->ppid = -1;
    item->pname = NULL;
    item->syscall = NULL;
    item->arg1 = NULL;
    item->arg2 = NULL;
    item->arg3 = NULL;
}


void release_log_item(struct log_item* item)
{
    if (item == NULL) return;
    if (item->pname != NULL) kfree(item->pname);
    if (item->syscall != NULL) kfree(item->syscall);
    if (item->arg1 != NULL) kfree(item->arg1);
    if (item->arg2 != NULL) kfree(item->arg2);
    if (item->arg3 != NULL) kfree(item->arg3);

    kfree(item);
}
*/

struct log_item* init_log_item(void)
{
    struct log_item* item = (struct log_item *)kmalloc(sizeof(struct log_item), GFP_KERNEL);
    item->pid = -1;
    item->ppid = -1;
    return item;
}


void release_log_item(struct log_item* item)
{
    if (item == NULL) return;

    kfree(item);
}
