#ifndef PROC_fS_MANAGE_H_
#define PROC_fS_MANAGE_H_

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "common.h"

int registry_proc_fs(void);
void registry_fs_out(void);

int is_monitor(int pid);
int notstart(void);
int isfilted(char *name);

#endif
