#ifndef LOG_LIST_H_
#define LOG_LIST_H_

#include "datastruct.h"

#define MAX_ITEM 30
struct logblock
{
    int blockid;
    int index;
    struct logblock *next;
    struct log_item items[MAX_ITEM];
};



//Initialize list && return head
struct logblock * init_log_block_list(int num);

//free all the memory of the list behind the block
void remove_block_list(struct logblock * block);

void initiate_log_item(struct log_item* item);

#endif
