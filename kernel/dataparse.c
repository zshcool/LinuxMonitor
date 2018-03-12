#include "datastruct.h"
#include "manage_pt_regs.h"
#include <linux/spinlock.h>
#include <linux/string.h>
#include "get_path.h"


void parse_execve(struct pt_regs *regs, char* buf, int len)
{
    char *path;
    char **argv;
    char **tmp;
    struct execveinfo * info = (struct execveinfo *)buf;

    path = (char*)get_arg1(regs);
    argv = (char**)get_arg2(regs);

    if(path[0] == '/')
    {
        strcpy(info->objpath, path);
    }else{
        get_pwd(current, info->objpath, MAX_FILE_PATH);
        strcat(info->objpath, "/");
        strcat(info->objpath, path);
    }

    tmp = argv;

    if(*tmp != NULL )
    {
        strcat(info->command, *tmp);
        tmp++;
    }
        
    while(*tmp != NULL)
    {
        if(strlen(buf) + strlen(*tmp) >= LOGSIZE)
        {
            break;
        }
        strcat(info->command, " ");
        strcat(info->command, *tmp);
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
}


void parse_rm(struct pt_regs *regs, char* buf, int len)
{
    char *path = (char*)get_arg1(regs);
    if (path == NULL) buf[0] = '\0';
    else strcpy(buf, path);
}


void parse_rename(struct pt_regs *regs, char* buf, int len)
{
    struct file_rename * file = (struct file_rename *)buf;

    char *oldname = (char*)get_arg1(regs);
    char* newname = (char*)get_arg2(regs);

    if(oldname == NULL) file->oldname[0] = '\0';
    else strcpy(file->oldname, oldname);

    if(newname == NULL) file->newname[0] = '\0';
    else strcpy(file->newname, newname);
}


void parse_chmod(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod * file = (struct file_create_chmod *)buf;

    char *pathname = (char*)get_arg1(regs);

    if(pathname == NULL) file->pathname[0] = '\0';
    else strcpy(file->pathname, pathname);

    file->mode = (mode_t)get_arg2(regs);
}


void parse_mount(struct pt_regs *regs, char* buf, int len)
{
    struct file_mount * file = (struct file_mount *)buf;
    char *devname = (char*)get_arg1(regs);
    char* filename = (char*)get_arg2(regs);

    if(devname == NULL) file->devname[0] = '\0';
    else strcpy(file->devname, devname);

    if(filename == NULL) file->filename[0] = '\0';
    else strcpy(file->filename, filename);
}


void parse_module(struct pt_regs *regs, char* buf, int len)
{
    struct file_module * file = (struct file_module *)buf;
    char * arg = (char*)get_arg3(regs);
    if(arg == NULL) file->uargs[0] = '\0';
    else strcpy(file->uargs, arg);
}


void parse_creatat(struct pt_regs *regs, char* buf, int len)
{
    struct file_create_chmod_at *file = (struct file_create_chmod_at *)buf;
    char* filename = (char*)get_arg2(regs);

    file->fd = (int)get_arg1(regs);
    file->mode = (mode_t)get_arg3(regs);

    if(filename == NULL) file->pathname[0] = '\0';
    else strcpy(file->pathname, filename);
}


void parse_linkat(struct pt_regs *regs, char* buf, int len)
{
    struct file_rename * file = (struct file_rename *)buf;
    
    char *oldname = (char*)get_arg2(regs);
    char* newname = (char*)get_arg4(regs);

    if(oldname == NULL) file->oldname[0] = '\0';
    else strcpy(file->oldname, oldname);

    if(newname == NULL) file->newname[0] = '\0';
    else strcpy(file->newname, newname);
}



/*
void get_abs_path(int fd, struct files_struct *files)
{
    char *tmp;
    char *pathname;
    struct file *file;
    struct path *path;
    
    spin_lock(&files->file_lock);
    file = fcheck_files(files, fd);
    if (!file) {
        spin_unlock(&files->file_lock);
        return -ENOENT;
    }
    
    path = &file->f_path;
    path_get(path);
    spin_unlock(&files->file_lock);
    
    tmp = (char *)__get_free_page(GFP_KERNEL);

    if (!tmp) {
        path_put(path);
        return -ENOMEM;
    }
    
    pathname = d_path(path, tmp, PAGE_SIZE);
    path_put(path);
    
    if (IS_ERR(pathname)) {
        free_page((unsigned long)tmp);
        return PTR_ERR(pathname);
    }

    printk("pathname:%s\n", pathname);
    // do something here with pathname
    
    free_page((unsigned long)tmp);
}*/
