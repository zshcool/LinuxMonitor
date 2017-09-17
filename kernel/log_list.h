#ifndef LOG_LIST_H_
#define LOG_LIST_H_

#include "logitem.h"

#define MAX_ITEM 30
struct logblock
{
    int index;
    struct logblock *next;
    struct log_item *items[MAX_ITEM];
};

//Initialize list head
struct logblock * init_log_block(void);
//insert node and return new node
struct logblock * insert_new_log_block(struct logblock * cur_block);
//free block
void destory_block(struct logblock * block);
//free all the memory of the list behind the block
void remove_block(struct logblock * block);

#endif
