#ifndef LOG_ITEM_H_
#define LOG_ITEM_H_

#include <linux/slab.h>

#define LOGSIZE 1024
#define NAMESIZE 16
#define MAX_FILE_PATH 256
#define ADDR_LEN 256
#define COLON "&:"
#define SPLIT "&/"

struct log_item
{
    int pid;
    int ppid;
    char syscall[NAMESIZE];
    char name[NAMESIZE];
    char pname[NAMESIZE];
    char buf[LOGSIZE];
};

struct addrinfo
{
    int len;
    int fd;
    char data[ADDR_LEN];
};	

struct file_stream
{
    int fd;
    size_t size;
}

struct file_open
{
    int fd;
    mode_t  mode;
    char* filename[MAX_FILE_PATH];
}

struct file_create_chmod
{
    mode_t  mode;
    char *pathname[MAX_FILE_PATH];
}

struct file_rename
{
    char *oldname[MAX_FILE_PATH];
    char *newname[MAX_FILE_PATH];
}

struct file_mount
{
    char *devname[MAX_FILE_PATH];
    char *filename[MAX_FILE_PATH];
}

struct file_module
{
    char *uargs[MAX_FILE_PATH];    
}

struct log_item* init_log_item(void);
void release_log_item(struct log_item* log_item);


#endif
