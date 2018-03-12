#ifndef DATA_PARSE_H_
#define DATA_PARSE_H_

#include <linux/string.h>
#include "common.h"
#include "datastruct.h"

void parse_execve(struct pt_regs *regs, char* buf, int len);
void parse_sockaddr(struct pt_regs *regs, char* buf, int len);
void parse_accept(struct pt_regs *regs, char* buf, int len);
void parse_file_stream(struct pt_regs *regs, char* buf, int len);
void parse_creat(struct pt_regs *regs, char* buf, int len);
void parse_rename(struct pt_regs *regs, char* buf, int len);
void parse_chmod(struct pt_regs *regs, char* buf, int len);
void parse_mount(struct pt_regs *regs, char* buf, int len);
void parse_module(struct pt_regs *regs, char* buf, int len);
void parse_rm(struct pt_regs *regs, char* buf, int len);
void parse_linkat(struct pt_regs *regs, char* buf, int len);
void parse_creatat(struct pt_regs *regs, char* buf, int len);

#endif
