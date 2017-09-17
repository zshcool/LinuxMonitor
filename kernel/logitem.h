#ifndef LOG_BLOCK_H_
#define LOG_BLOCK_H_

#include <linux/slab.h>

#define LOGSIZE 1024

struct log_item
{
    int pid;
    int ppid;
    char buf[LOGSIZE];
};


struct log_item* init_log_item(void);
void release_log_item(struct log_item* log_item);


#endif
