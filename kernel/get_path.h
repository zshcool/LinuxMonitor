#ifndef GET_PATH_H
#define GET_PATH_H

#include <linux/module.h>
#include <linux/fcntl.h>//for O_RDONLY
#include <linux/fs.h>//for filp_open
#include <linux/uaccess.h>//for get_fs
#include <linux/limits.h>//for PATH_MAX 
#include <linux/sched.h> 
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/fs_struct.h>
#include "common.h"

struct path_name_node{
    char    name[NAMESIZE];
    struct path_name_node * next;
};

// #if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
// extern void set_fs_pwd(struct fs_struct *, struct path *);
// #endif

char* get_absolute_path(struct task_struct * task);
void get_pwd(struct task_struct * task, char *buf, int size);


#endif