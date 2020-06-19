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

void open_acc(void)
{
	// 获取银行卡号
	sprintf(ctos.acc.bank,"%d",get_bank(BANK_PATH));
	// 设置初始密码
	sprintf(ctos.acc.pass,"123456");
	// 设置锁定状态
	ctos.acc.islock = 0;
	
	char path[256] = {};
	sprintf(path,"%s%s",ACC_PATH,ctos.acc.bank);
	
	int fd = open(path,O_WRONLY|O_CREAT|O_EXCL,0644);
	if(0 > fd)
	{
		error("open");
		sprintf(stoc.info,"N:服务器正在升级，开户失败");
		return;
	}
	
	write(fd,&ctos.acc,sizeof(ctos.acc));
	sprintf(stoc.info,"Y:开户成功，卡号:%s 密码:%s",ctos.acc.bank,ctos.acc.pass);
	close(fd);
}

int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	for(;;)
	{
		ctos.type = M_OPEN;
		rcv_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		open_acc();
		
		stoc.type = ctos.pid;
		snd_msg(stoc_msgid,&stoc,sizeof(stoc));
	}
}

