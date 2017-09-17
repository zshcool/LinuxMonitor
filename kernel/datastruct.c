#include <linux/slab.h>

#include "datastruct.h"


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
