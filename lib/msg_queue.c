#include "msg_queue.h"
#include "tools.h"

// 根据提供的key创建或获取消息队列
int get_msg(key_t key)
{
	int msgid = msgget(key,IPC_CREAT|0644);
	if(0 > msgid)
	{
		printf("进程:%d，msgget:%m\n",getpid());
		return -1;
	}
	
	return msgid;
}

// 以阻塞方式发送消息
void snd_msg(int msgid,const void* buf,size_t size)
{
	if(0 > msgsnd(msgid,buf,size-4,0))
	{
		error("msgsnd");
	}
}

// 以阻塞方式接收消息
void rcv_msg(int msgid,void* buf,size_t size)
{
	if(0 > msgrcv(msgid,buf,size,*(long*)buf,0))
	{
		error("msgrcv");
	}
}


// 删除消息队列
void del_msg(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL))
	{
		printf("进程:%d，msgctl:%m\n",getpid());
	}
}

