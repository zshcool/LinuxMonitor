#include "datastruct.h"
#include "manage_pt_regs.h"
#include <linux/string.h>


void parse_execve(struct pt_regs *regs, char* buf, int len)
{
    char *path;
    char **argv;
    char **tmp;

    path = (char*)get_arg1(regs);
    argv = (char**)get_arg2(regs);

    strcat(buf, "objpath");
    strcat(buf, COLON);
    strcat(buf, path);
    strcat(buf, SPLIT);
    strcat(buf, "command");
    strcat(buf, COLON);

    tmp = argv;
    strcat(buf, path);
    while(*tmp != NULL)
    {
        if(strlen(buf) + strlen(*tmp) < LOGSIZE)
        strcat(buf, " ");
        strcat(buf, *tmp);
        tmp++;
    }
}

void parse_sockaddr(struct pt_regs *regs, char* buf, int len)
{
    int fd = (int)get_arg1(regs);
    int data_len = get_arg3(regs);
    struct addrinfo * addr = (struct addrinfo *)buf;

    addr->len = data_len;
    addr->fd = fd;
    memcpy(addr->data, (char*)get_arg2(regs), data_len);
}

void parse_accept(struct pt_regs *regs, char* buf, int len)
{
    int fd = (int)get_arg1(regs);
    int data_len = *((int*)get_arg3(regs));
    struct addrinfo * addr = (struct addrinfo *)buf;

    addr->len = data_len;
    addr->fd = fd;
    memcpy(addr->data, (char*)get_arg2(regs), data_len);
}



void parse_file_stream(struct pt_regs *regs, char* buf, int len)
{
    struct file_stream * stream = (struct file_stream *)buf;
    stream->fd = (int)get_arg1(regs);
    //stream->size = (int)get_arg3(regs);

    printk("fd:%d\n", stream->fd);
    //printk("size:%d\n", stream->size);
}


void parse_creat(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod * file = (struct file_create_chmod *)buf;
    strcpy(file->pathname, (char*)get_arg1(regs));
    printk("path:%s",file->pathname);
    file->mode = (mode_t)get_arg2(regs);
    printk("path:%d",file->mode);
}

void parse_rm(struct pt_regs *regs, char* buf, int len)
{
    strcpy(buf, (char*)get_arg1(regs));
    printk("path:%s",buf);
}




void parse_rename(struct pt_regs *regs, char* buf, int len)
{
    struct file_rename * file = (struct file_rename *)buf;
    strcpy(file->oldname, (char*)get_arg1(regs));
    strcpy(file->newname, (char*)get_arg2(regs));
}


void parse_chmod(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod * file = (struct file_create_chmod *)buf;
    strcpy(file->pathname, (char*)get_arg1(regs));
    file->mode = (mode_t)get_arg2(regs);
}


void parse_mount(struct pt_regs *regs, char* buf, int len)
{
    struct file_mount * file = (struct file_mount *)buf;
    strcpy(file->devname, (char*)get_arg1(regs));
    strcpy(file->filename, (char*)get_arg2(regs));
}

void parse_module(struct pt_regs *regs, char* buf, int len)
{
    struct file_module * file = (struct file_module *)buf;
    strcpy(file->uargs, (char*)get_arg3(regs));
}

