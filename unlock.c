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

void unlock(void)
{
	char path[256] = {};
	sprintf(path,"%s%s",ACC_PATH,ctos.acc.bank);
	
	// 判断银行卡号是否正确
	if(0 != access(path,F_OK))
	{
		sprintf(stoc.info,"N:卡号不存在，请检查!");
		return;
	}
	
	int fd = open(path,O_RDWR);
	if(0 > fd)
	{
		error("open");
		sprintf(stoc.info,"N:服务器正在升级，解锁失败!");
		return;
	}
	
	Acc acc = {};
	read(fd,&acc,sizeof(Acc));

	if(strcmp(acc.card,ctos.acc.card))
	{
		sprintf(stoc.info,"N:身份证号不正确，解锁失败!");
		return;
	}
	
	if(strcmp(acc.pass,ctos.acc.pass))
	{
		sprintf(stoc.info,"N:密码不正确，解锁失败!");
		return;
	}
	
	acc.islock = 0;
	lseek(fd,0,SEEK_SET);
	write(fd,&acc,sizeof(Acc));
	close(fd);
	
	sprintf(stoc.info,"N:解锁成功!");
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		ctos.type = M_UNLOCK;
		rcv_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		unlock();
		
		stoc.type = ctos.pid;
		snd_msg(stoc_msgid,&stoc,sizeof(stoc));
	}
}

