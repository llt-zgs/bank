#include "msg_queue.h"
#include "client.h"
#include "tools.h"
#include "bank.h"

// 通信消息
Msg_ctos ctos;
Msg_stoc stoc;

// 消息列队ID
int stoc_msgid = 0;
int ctos_msgid = 0;

// 主菜单
void main_menu(void)
{
	puts("********欢迎使用指针银行********");
	puts("            1.开户");
	puts("            2.登录");
	puts("            3.销户");
	puts("            4.解锁");
	puts("            0.退出");
}


// 开户
void open_acc(void)
{
	ctos.type = M_OPEN;
	printf("请输入身份证号：");
	get_str(ctos.acc.card,10);
	printf("请输入开户金额：");
	scanf("%f",&ctos.acc.balance);
}

// 登陆
void login(void)
{
	ctos.type = M_LOGIN;
	printf("请输入银行卡号：");
	get_str(ctos.acc.bank,10);
	printf("请输入密码：");
	get_pass(ctos.acc.pass,7,true);
	
	// 向服务端发送消息
	snd_msg(ctos_msgid,&ctos,sizeof(ctos));
		
	// 从服务端接收消息
	rcv_msg(stoc_msgid,&stoc,sizeof(stoc));

	if('Y' != stoc.info[0])
	{
		// 显服务端执行的结果
		puts(stoc.info);
		anykey_continue();
		return;
	}
	
	for(;;)
	{
		sub_menu();
		switch(get_cmd('1','6')-'0'+4)
		{
		case M_SAVE: 	save();		break;	// 存款
		case M_TAKE: 	take();		break;	// 取款
		case M_QUERY: 	query();	break;	// 查询
		case M_TRANSFER:transfer();	break;	// 转账
		case M_REPASS:	repass();	break;	// 改密
		default:		_Exit(0);		break;	// 退出
		}
		
		// 向服务端发送消息
	snd_msg(ctos_msgid,&ctos,sizeof(ctos));
		
	// 从服务端接收消息
	rcv_msg(stoc_msgid,&stoc,sizeof(stoc));

		
		// 显服务端执行的结果
		puts(stoc.info);
		anykey_continue();
	}
}

// 销户
void destroy(void)
{
	ctos.type = M_DESTROY;
	printf("请输入银行卡号：");
	get_str(ctos.acc.bank,10);
	printf("请输入身份证号：");
	get_str(ctos.acc.card,10);
	printf("请输入密码：");
	get_pass(ctos.acc.pass,7,true);
	
}


// 解锁
void unlock(void)
{
	ctos.type = M_UNLOCK;
	printf("请输入银行卡号：");
	get_str(ctos.acc.bank,10);
	printf("请输入身份证号：");
	get_str(ctos.acc.card,10);
	printf("请输入密码：");
	get_pass(ctos.acc.pass,7,true);
	
}

// 子菜单
void sub_menu(void)
{
	puts("*********恭喜您登录成功********");
	puts("            1.存款");
	puts("            2.取款");
	puts("            3.查询");
	puts("            4.转账");
	puts("            5.改密");
	puts("            6.退出");
}


// 存款
void save(void)
{
	ctos.type = M_SAVE;
	printf("请输入存款金额：");
	scanf("%f",&ctos.acc.balance);
}

// 取款
void take(void)
{
	ctos.type = M_TAKE;
	printf("请输入取款金额：");
	scanf("%f",&ctos.acc.balance);
}

// 查询
void query(void)
{
	ctos.type = M_QUERY;
}

// 转账
void transfer(void)
{
	ctos.type = M_TRANSFER;
	printf("请输入转账对象卡号：");
	get_str(ctos.acc.card,10);
	printf("请输入转账金额：");
	scanf("%f",&ctos.acc.balance);
}

// 改密
void repass(void)
{
	char pass1[10] = {} , pass2[10] = {};
	printf("请输入新密码：");
	get_pass(pass1,10,true);
	printf("请再次输入新密码：");
	get_pass(pass2,10,true);
	if(strcmp(pass1,pass2))
	{
		puts("两次输入的密码不相同，修改失败!");
	}
	else
	{
		ctos.type = M_REPASS;
		strcpy(ctos.acc.pass,pass1);
	}

}


int main()
{
	// 获取两个消息队列
	stoc_msgid = get_msg(STOC_KEY);
	ctos_msgid = get_msg(CTOS_KEY);
	
	// 确定返回的消息类型
	ctos.pid = stoc.type = getpid();
	
	for(;;)
	{
		main_menu();
		// 负责准备要发送的消息
		switch(get_cmd('0','7')-'0')
		{
		case M_EXIT:	return 0;	break;	// 退出
		case M_OPEN:	open_acc();	break;	// 开户
		case M_LOGIN: 	login();	continue;	// 登陆
		case M_DESTROY: destroy();	break;	// 销户
		case M_UNLOCK:	unlock();	break; 	// 解锁
		}
		
		// 向服务端发送消息
		snd_msg(ctos_msgid,&ctos,sizeof(ctos));
		
		// 从服务端接收消息
		rcv_msg(stoc_msgid,&stoc,sizeof(stoc));
		
		// 显服务端执行的结果
		puts(stoc.info);
		anykey_continue();

	}
}
