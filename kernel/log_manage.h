#ifndef LOG_MANAGE_H_
#define LOG_MANAGE_H_

#include "datastruct.h"
#include "log_list.h"

#define MAX_BLOCK 5

//judge whether there are new logs to read, return 0 no,1 yes
int has_new_log(void);


struct logblock * init_log_list(void);

void destroy_log_list(void);

//move current cursor index
struct log_item * get_log_item(void);


//get a recorded log, return NULL means can't fine a new log
struct log_item * fetch_log(void);

#endif
