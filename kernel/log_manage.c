#include "log_manage.h"
#include <linux/mutex.h>

static struct logblock *listhead;
static struct logblock *curblock;
static struct logblock *cursorblock;
static int cursorindex = 0;
static DEFINE_MUTEX(locker);


int has_new_log(void)
{
    if(cursorindex < cursorblock->index)
        return 1;
    else
        return 0;
}


struct logblock *get_next_log(struct logblock * block)
{
     if(block->next == NULL)
         return listhead;
     else
         return block->next;
}


struct logblock * init_log_list(void)
{
    listhead = init_log_block_list(MAX_BLOCK);

    if (listhead == NULL)
        return NULL;

    curblock = listhead;
    cursorblock = listhead;

    return listhead;
}


void destroy_log_list(void)
{   mutex_lock(&locker);
    remove_block_list(listhead);
    mutex_unlock(&locker);
}


struct log_item * get_log_item(void)
{
    struct log_item *item;

    mutex_lock(&locker);    
    item = &curblock->items[curblock->index];
    initiate_log_item(item);

    //move cursor to next index
    curblock->index++;
    if (curblock->index < MAX_ITEM)
    {
        ;
    }
    else{
        curblock = get_next_log(curblock);
        curblock->index = 0;

        if(curblock->blockid == cursorblock->blockid)
        {
            //if current log block reaches the  read cursor,
            //move the read-cursor to next;
            cursorblock = get_next_log(cursorblock);
            cursorindex = 0;
        }

    }

    mutex_unlock(&locker);
    return item;
}



struct log_item * fetch_log(void)
{
    struct log_item* item;

    mutex_lock(&locker);
    if(has_new_log())
    {
        item = &cursorblock->items[cursorindex];

        //move the cursor to next log item
        cursorindex++;

        //has finshed to get the block's logs
        if(cursorindex == MAX_ITEM)
        {
            cursorblock = get_next_log(cursorblock);
            cursorindex = 0;
        }

    }else{
        //can't find new log
        item = NULL;
    }

    mutex_unlock(&locker);
    return item;
}
