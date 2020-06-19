#ifndef BANK_H
#define BANK_H

// 消息类型
#define M_EXIT		0 // 退出
#define M_OPEN 		1 // 开户
#define M_LOGIN 	2 // 登陆
#define M_DESTROY 	3 // 销户
#define M_UNLOCK	4 // 解锁
#define M_SAVE 		5 // 存款
#define M_TAKE 		6 // 取款
#define M_QUERY 	7 // 查询
#define M_TRANSFER 	8 // 转账
#define M_REPASS	9 // 改密 

// 账户信息存储路径
#define ACC_PATH	"account/"
// 银行卡号存储路径
#define BANK_PATH	"account/bank.dat"


// 账户信息结构体
typedef struct Account
{
	char 	bank[10];	// 银行卡号
	char 	card[10];	// 身份证号
	char 	pass[7];	// 密码
	float 	balance;	// 余额
	char	islock;		// 锁定
}Acc;

// 客户端到服务端的消息结构体
typedef struct Msg_ctos
{
	long 	type;		// 消息类型
	Acc 	acc;		// 账户

}Msg_ctos;

// 服务端到客户端的消息结构体
typedef struct Msg_stoc
{
	long type;			// 消息类型
	char info[256];		// 提示信息
}Msg_stoc;

#endif//BANK_H

