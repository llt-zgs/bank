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

void repass(void)
{
	char path[256] = {};
	sprintf(path,"%s%s",ACC_PATH,ctos.acc.bank);
	
	int fd = open(path,O_WRONLY);
	if(0 > fd)
	{
		error("open");
		sprintf(stoc.info,"N:服务器正在升级，查询失败!");
		return;
	}
	
	Acc acc = {};
	read(fd,&acc,sizeof(Acc));
	strcpy(acc.pass,ctos.acc.pass);
	write(fd,&acc,sizeof(Acc));
	
	sprintf(stoc.info,"N:修改密码成功!");
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		ctos.type = M_REPASS;
		rcv_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		repass();
		
		stoc.type = ctos.pid;
		snd_msg(stoc_msgid,&stoc,sizeof(stoc));
	}
}

