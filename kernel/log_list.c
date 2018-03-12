#include "log_list.h"
#include <linux/string.h>
#include <linux/vmalloc.h>


void initiate_log_item(struct log_item* item)
{
    memset(item, 0, sizeof(struct log_item));
    item->pid = -1;
    item->ppid = -1;
    item->syscall[0] = '\0';
    item->name[0] = '\0';
    item->pname[0] = '\0';
    item->buf[0] = '\0';
}


struct logblock * init_log_block(void)
{
    int i;
    struct logblock* block;

    block = (struct logblock *)vmalloc(sizeof(struct logblock));
    if (block == NULL) return NULL;

    block->blockid = 0;
    block->index = 0;
    block->next = NULL;
    
    for(i = 0; i < MAX_ITEM; i++)
    {
        initiate_log_item(&block->items[i]);
    }

    return block;
}


struct logblock * init_log_block_list(int num)
{
    int left;
    int flag = 0;
    struct logblock* head;
    struct logblock* cur;
    
    if (num == 0) return NULL;

    head = init_log_block();
    if(head == NULL) return NULL;

    head->blockid = 0;

    left = num - 1;
    cur = head;

    while(left > 0)
    {
        struct logblock* tmp = init_log_block();
        if (tmp == NULL)
        {
            flag = 1;
            break;
        }

        cur->next = tmp;
        cur->next->blockid = cur->blockid + 1;

        cur = cur->next;
        left--;
    }

    if(flag)
    {
        remove_block_list(head);
        head = NULL;
    }

    return head;
}


void destory_block(struct logblock * block)
{
    if(block == NULL) return;

    vfree(block);
}


void remove_block_list(struct logblock * block)
{
    struct logblock * cur = block;
    struct logblock * tmp = NULL;

    while(cur != NULL)
    {
        tmp = cur;
        cur = cur->next;

        destory_block(tmp);
    }
}

