#include "log_list.h"


struct logblock * init_log_block()
{
    int i;
    struct logblock* block = (struct logblock *)kmalloc(sizeof(struct logblock), GFP_KERNEL);
    block->index = 0;
    block->next = NULL;
    
    for(i = 0; i < MAX_ITEM; i++)
    {
        block->items[i] = NULL;
    }

    return block;
}


struct logblock * insert_new_log_block(struct logblock * cur_block)
{
    struct logblock* block = init_log_block();
    cur_block->next = block;

    return block;
}


void destory_block(struct logblock * block)
{
    int i;
    if(block == NULL) return;

    for(i = 0; i < MAX_ITEM; i++)
    {
        if(block->items[i] != NULL)
        {
            release_log_item(block->items[i]);
        }
    }

    kfree(block);
}


void remove_block(struct logblock * block)
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

