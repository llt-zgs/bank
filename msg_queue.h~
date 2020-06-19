#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define STOC_KEY (1711374123ul)
#define CTOS_KEY (3372318507ul)



// 根据提供的key创建或获取消息队列
int get_msg(key_t key);

// 以阻塞方式发送消息
void snd_msg(int msgid,const void* buf,size_t size);

// 以阻塞方式接收消息
void rcv_msg(int msgid,void* buf,size_t size);

// 删除消息队列
void del_msg(int msgid);

#endif//MSG_QUEUE_H

