#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "msg_queue.h"
#include "bank.h"
#include "tools.h"

// 通信消息
Msg_ctos ctos;
Msg_stoc stoc;

// 消息列队ID
int stoc_msgid = 0;
int ctos_msgid = 0;

void save(void)
{
	char path[256] = {};
	sprintf(path,"%s%s",ACC_PATH,ctos.acc.bank);
	
	int fd = open(path,O_RDWR);
	if(0 > fd)
	{
		error("open");
		sprintf(stoc.info,"N:服务器正在升级，存款失败!");
		return;
	}
	
	Acc acc = {};
	read(fd,&acc,sizeof(Acc));

	acc.balance += ctos.acc.balance;
	lseek(fd,0,SEEK_SET);
	write(fd,&acc,sizeof(Acc));
	close(fd);
	
	sprintf(stoc.info,"N:存款成功，当前余额为:%g!",acc.balance);
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		ctos.type = M_SAVE;
		rcv_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		save();
		
		stoc.type = ctos.pid;
		snd_msg(stoc_msgid,&stoc,sizeof(stoc));
	}
}

