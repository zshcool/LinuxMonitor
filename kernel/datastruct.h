#ifndef LOG_ITEM_H_
#define LOG_ITEM_H_

#include <linux/slab.h>
#include "common.h"


struct log_item
{
    int pid;
    int ppid;
    char syscall[NAMESIZE];
    char path[MAX_FILE_PATH];
    char name[NAMESIZE];
    char pname[NAMESIZE];
    char buf[LOGSIZE];
};


struct execveinfo
{
    char objpath[MAX_FILE_PATH];
    char command[512];
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
};

struct file_open
{
    int fd;
    mode_t  mode;
    char filename[MAX_FILE_PATH];
};

struct file_create_chmod
{
    mode_t  mode;
    char pathname[MAX_FILE_PATH];
};

struct file_rename
{
    char oldname[MAX_FILE_PATH];
    char newname[MAX_FILE_PATH];
};

struct file_mount
{
    char devname[MAX_FILE_PATH];
    char filename[MAX_FILE_PATH];
};

struct file_module
{
    char uargs[MAX_FILE_PATH];    
};


struct file_create_chmod_at
{
    mode_t  mode;
    int fd;
    char pathname[MAX_FILE_PATH];
};


#endif
