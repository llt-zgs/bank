#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define error(func) fprintf(stderr,"%s:%d,%s:%m,pid:%u\n",__FILE__,__LINE__,func,getpid())

// 清理输入缓冲区
void clear_stdin(void);

// 获取指令
int get_cmd(char start,char end);

// 获取字符串
char* get_str(char* str,size_t len);

// 获取密码
char* get_pass(char* pass,size_t len,bool flag);

// 初始化银行卡号
void init_bank(const char* path,int bank);

// 生成一个银行卡号
int get_bank(const char* path);

// 按任意键继续
void anykey_continue(void);

#endif//TOOLS_H

