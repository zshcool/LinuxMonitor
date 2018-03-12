#ifndef COMMON_H_
#define COMMON_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>
#include <linux/vmalloc.h>
#include <linux/timex.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/fs_struct.h>


#define MODULE_NAME "[antiylm]"

#define MAX_FILTER_NUM 24
#define FILTER_RULE_FULL -3

#define LOGSIZE 670
#define NAMESIZE 30
#define MAX_FILE_PATH 256
#define ADDR_LEN 256

#define MAX_PROBES 20
#define ROOT_PATH "/"


#define EXECVE_     0
#define CONNECT_    1
#define BIND_       2
#define ACCEPT_     3 
#define READ_       4
#define WRITE_      5
#define CREAT_      6
#define MKDIR_      7
#define MKDIRAT_    8
#define LINK_       9
#define RMDIR_      10
#define INIT_MODULE_ 11
#define RENAME_     12
#define CHMOD_      13
#define FCHMOD_     14
#define MOUNT_      15
#define UNLINK_     16
#define UNLINKAT_   17
#define FCHMODAT_   18
#define LINKAT_     19

#endif