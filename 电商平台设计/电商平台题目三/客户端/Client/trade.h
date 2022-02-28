#include<iostream>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h>
#include <iomanip>
#include <set>
//ws2_32.lib库
#pragma comment(lib,"ws2_32.lib")
//消除报错4996
#pragma warning(disable : 4996)
using namespace std;
extern int getNum();	//正确地输入一个数字，对不正常输入进行报错处理
extern bool isSignIn;	//是否登录地标志

class Trade {
public:
	bool getSendBuf(char* buf);										    //构造发送请求
	bool solveRecvBuf(char recvbuf[]);									//分析得到的回答
	void printInitialInterface();										//打印未登录界面
	void printUserInterface();											//打印登录界面
	void getResult(char buf[]);											//得到回复消息
	void buyCommodity(char* buf, int& offset);							//购买单个商品
	void changePassword(char* buf, int& offset);						//改变密码
	void rechargeMoney(char* buf, int& offset);							//充值
	void userSignIn(char* buf, int& offset);							//用户登录
	void userSignUp(char* buf, int& offset);							//用户注册
	void addCommodity(char* buf, int& offset);							//添加商品
	void showCommodity(char buf[], int type);							//显示所有商品信息
	void searchCommoddity(char* buf,int& offset);						//搜索商品
	void changeCommodityInfo(char* buf, int& offset);					//修改商品信息
	void manageCart(char* buf, int& offset);							//管理购物车
	void showCart(char buf[]);											//查看购物车
	void makeOrders(char* buf, int& offset);							//生成订单
	void showOrders(char buf[]);										//查看订单
	void onlinePayment(char* buf, int& offset);							//网上支付
};

