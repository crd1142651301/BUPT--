#include "user.h"

class Trade {
public:
	Trade();
	User* getUser();
	void printInitialInterface();	//打印未登录初始界面
	void printUserInterface();		//打印登录界面
	void buyCommodity();			//购买单个商品
    bool userSignIn();				//用户登录
	bool userSignUp();				//用户注册
	void addCommodity();			//添加商品
	void showAllCommodity();		//显示所有商品信息
	void searchCommoddity();		//搜索商品
	void changeCommodityInfo();		//修改商品信息
	void manageCart();				//管理购物车
	void makeOrders();				//生成订单
	void onlinePayment();			//网上支付
	~Trade();
private:
	list<Commodity*> commodities;	//存储商品
	User* user;						//保存用户
	string inputPassword(int type);	//输入密码屏幕回显***********
	bool KMPcompare(string s, string t);	//KMP算法实现搜索
	void updateCommodityFile(const string& filename, const string& kind);	//更新对应商品的文件
	void addComToCart();					//加入购物车商品
	void subComToCart();					//删除购物车商品
};
