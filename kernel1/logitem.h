#ifndef LOG_ITEM_H_
#define LOG_ITEM_H_

#include <linux/slab.h>

#define LOGSIZE 1024
#define NAMESIZE 16

struct log_item
{
    int pid;
    int ppid;
    char name[NAMESIZE];
    char pname[NAMESIZE];
    char buf[LOGSIZE];
};


struct log_item* init_log_item(void);
void release_log_item(struct log_item* log_item);


#endif
