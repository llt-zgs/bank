#ifndef CLIENT_H
#define CLIENT_H

// 主菜单
void main_menu(void);

// 开户
void open_acc(void);

// 登陆
void login(void);

// 销户
void destory(void);

// 子菜单
void sub_menu(void);

// 解锁
void unlock(void);

// 存款
void save(void);

// 取款
void take(void);

// 查询
void query(void);

// 转账
void transfer(void);

// 改密
void repass(void);

// 发服务端发送消息
void msg_send(void);

// 从服务端接收消息
void msg_recv(void);

#endif//CLIENT_H

