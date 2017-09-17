#include "datastruct.h"
#include "manage_pt_regs.h"
#include <linux/string.h>


void parse_execve(struct pt_regs *regs, char* buf, int len)
{
    char *path;
    char **argv;
    char **tmp;
    struct execveinfo * info = (struct execveinfo *)buf;

    path = (char*)get_arg1(regs);
    argv = (char**)get_arg2(regs);

    strcpy(info->objpath, path);

    tmp = argv;

    while(*tmp != NULL)
    {
        if(strlen(buf) + strlen(*tmp) < LOGSIZE)
        strcat(info->command, *tmp);
        strcat(info->command, " ");
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
    int *data_len = (int*)get_arg3(regs);
    struct addrinfo * addr = (struct addrinfo *)buf;

    if (data_len == NULL)
    {
        data_len = 0;
    }else{
        addr->len = *data_len;
        addr->fd = fd;
        memcpy(addr->data, (char*)get_arg2(regs), addr->len);
    }
}


void parse_file_stream(struct pt_regs *regs, char* buf, int len)
{
    struct file_stream * stream = (struct file_stream *)buf;
    stream->fd = (int)get_arg1(regs);
    stream->size = (int)get_arg3(regs);
}


void parse_creat(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod * file = (struct file_create_chmod *)buf;
    strcpy(file->pathname, (char*)get_arg1(regs));
    file->mode = (mode_t)get_arg2(regs);

    printk("path:%s",file->pathname);
}

void parse_rm(struct pt_regs *regs, char* buf, int len)
{
    char *path = (char*)get_arg1(regs);
    if (path == NULL) buf[0] = 0x00;
    else strcpy(buf, path);

    printk("remove:%s",buf);
}


void parse_rename(struct pt_regs *regs, char* buf, int len)
{
    struct file_rename * file = (struct file_rename *)buf;

    char *oldname = (char*)get_arg1(regs);
    char* newname = (char*)get_arg2(regs);

    if(oldname == NULL) file->oldname[0] = 0x00;
    else strcpy(file->oldname, oldname);

    if(newname == NULL) file->newname[0] = 0x00;
    else strcpy(file->newname, newname);
}


void parse_chmod(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod * file = (struct file_create_chmod *)buf;

    char *pathname = (char*)get_arg1(regs);

    if(pathname == NULL) file->pathname[0] = 0x00;
    else strcpy(file->pathname, pathname);
}


void parse_mount(struct pt_regs *regs, char* buf, int len)
{
    struct file_mount * file = (struct file_mount *)buf;
    char *devname = (char*)get_arg1(regs);
    char* filename = (char*)get_arg2(regs);

    if(devname == NULL) file->devname[0] = 0x00;
    else strcpy(file->devname, devname);

    if(filename == NULL) file->filename[0] = 0x00;
    else strcpy(file->filename, filename);
}

void parse_module(struct pt_regs *regs, char* buf, int len)
{
    struct file_module * file = (struct file_module *)buf;
    char * arg = (char*)get_arg3(regs);
    if(arg == NULL) file->uargs[0] = 0x00;
    else strcpy(file->uargs, arg);
}

