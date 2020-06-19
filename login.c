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

void login(void)
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
		sprintf(stoc.info,"N:服务器正在升级，登陆失败!");
		return;
	}
	
	Acc acc = {};
	read(fd,&acc,sizeof(Acc));
	
	if(acc.islock >= 3)
	{
		sprintf(stoc.info,"N:此账号已经锁定，请解锁!");
		return;
	}
	
	if(strcmp(ctos.acc.pass,acc.pass))
	{
		acc.islock++;
		sprintf(stoc.info,"N:密码错误，重新登陆（您还有%d次机会）!",3-acc.islock);
		if(acc.islock >= 3)
		{
			sprintf(stoc.info,"N:此账号已经锁定，请解锁!");
		}
	}
	else
	{
		acc.islock = 0;
		sprintf(stoc.info,"Y:恭喜您登陆成功!");
	}

	lseek(fd,0,SEEK_SET);
	write(fd,&acc,sizeof(Acc));
	close(fd);
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		ctos.type = M_LOGIN;
		rcv_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		login();
		
		stoc.type = ctos.pid;
		snd_msg(stoc_msgid,&stoc,sizeof(stoc));
	}
}

