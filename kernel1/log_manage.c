#include "log_manage.h"

static struct logblock *listhead;
static struct logblock *curblock;
static struct logblock *cursorblock;
static int cursor = 0;
static int total_block = 0;


int has_new_log(void)
{
    if(cursor < cursorblock->index)
    {
        printk("cursor:%d, index:%d", cursor, cursorblock->index);
        return 1;
    }
    else
        return 0;
}


void init_log_list(void)
{
    listhead = init_log_block();
    curblock = listhead;
    cursorblock = listhead;
}


void destroy_log_list(void)
{
    remove_block(listhead);
}


struct log_item * get_log_item(void)
{
    struct log_item *item;
    item = init_log_item();
    curblock->items[curblock->index] = item;

    //move cursor to next index
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

    return item;
}



struct log_item * fetch_log(void)
{
    struct log_item* item;
    if(has_new_log())
    {
        item = cursorblock->items[cursor];

        //move the cursor to next log item
        printk("cursor:%d++", cursor);
        cursor++;
        printk("cursor:%d", cursor);

        //has finshed to get the block's logs
        if(cursor >= MAX_ITEM)
        {
            cursorblock = cursorblock->next;
            cursor = 0;
        }

    }else{
        //can't find new log
        item = NULL;
    }

    return item;
}
