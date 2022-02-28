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
	void changeCommodityInfo();
	~Trade();
private:
	list<Commodity*> commodities;
	User* user;
	string inputPassword(int type);
	bool KMPcompare(string s, string t);
	void updateCommodityFile(string filename, string kind);
};
