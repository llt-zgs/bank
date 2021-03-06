#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include "msg_queue.h"
#include "bank.h"
#include "tools.h"

// 通信消息
Msg_ctos ctos;
Msg_stoc stoc;

// 消息列队ID
int stoc_msgid = 0;
int ctos_msgid = 0;

void transfer(void)
{
	char str_path[256] = {},dest_path[256];
	
	sprintf(str_path,"%s%s",ACC_PATH,ctos.acc.bank);
	sprintf(dest_path,"%s%s",ACC_PATH,ctos.acc.card);
	
	int src_fd = open(str_path,O_RDWR);
	int dest_fd = open(dest_path,O_RDWR);
	if(0 > src_fd || 0> dest_fd)
	{
		printf("%s:%d：我子进程:%d，open:%m\n",__FILE__,__LINE__,getpid());
		sprintf(stoc.info,"N:服务器正在升级，转账失败");
		return;
	}
	
	Acc src_acc = {},dest_acc={};
	read(src_fd,&src_acc,sizeof(Acc));
	read(dest_fd,&dest_acc,sizeof(Acc));
	
	if(src_acc.balance < ctos.acc.balance)
	{
		sprintf(stoc.info,"N:余额不足,取款失败，当前余额为:%g!",src_acc.balance);
		return;
	}
	
	src_acc.balance -= ctos.acc.balance;
	dest_acc.balance +=ctos.acc.balance;
	
	lseek(src_fd,0,SEEK_SET);
	lseek(dest_fd,0,SEEK_SET);
	write(src_fd,&src_acc,sizeof(Acc));
	write(dest_fd,&dest_acc,sizeof(Acc));
	close(src_fd);
	close(dest_fd);
	sprintf(stoc.info,"Y:转账成功，当前余额为:%g!",src_acc.balance);
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		if(0 > msgrcv(ctos_msgid,&ctos,sizeof(ctos),M_TRANSFER,0))
		{
			error("msgrcv");
			continue;
		}
		
		transfer();
		
		stoc.type = ctos.pid;
		if(0 > msgsnd(stoc_msgid,&stoc,sizeof(stoc.info),0))
		{
			error("msgnd");
		}
	}
}

