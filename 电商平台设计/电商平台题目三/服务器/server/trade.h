#include "user.h"


class Trade {
public:
	Trade();
	void handleBuf(char recvbuf[], char* sendbuf, User*& user);								//处理收到的包并构造要响应的包
	void buyCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset);				//购买单个商品
	void userSignIn(char* sendbuf,User*& user, char recvbuf[], int& offset);				//用户登录
	bool userSignUp(char* sendbuf, char recvbuf[], int& offset);							//用户注册
	void addCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset);				//添加商品
	void showAllCommodity(char* sendbuf, int& offset);										//显示所有商品信息
	void searchCommoddity(char* sendbuf, int& offset, char recvbuf[]);						//搜索商品
	void changeCommodityInfo(char* sendbuf, User*& user, char recvbuf[], int& offset);		//修改商品信息
	void manageCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//管理购物车
	void makeOrders(char* sendbuf, User*& user, char recvbuf[], int& offset);				//生成订单
	void onlinePayment(char* sendbuf, User*& user, char recvbuf[], int& offset);			//网上支付
	bool updateMyData(User*& user);
	~Trade();
private:
	list<Commodity*> commodities;															//存放商品
	string inputPassword(int type);															//回显*****
	bool KMPcompare(string s, string t);													//KMP实现搜索
	void updateCommodityFile(const string& filename, const string& kind);					//更新商品文件
	void addComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//加入购物车商品
	void subComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//删除购物车商品
};
