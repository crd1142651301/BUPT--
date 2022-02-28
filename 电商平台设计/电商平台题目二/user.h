#include "commodity.h"
#include<list>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<iomanip>
#define BUYER 0
#define SELLER 1

class Item {
public:
	Item() {
		nums = 0;
		pcom = nullptr;
	}
	Commodity* pcom;
	string name;		//商品名称
	string acc;			//所属账号
	string kind;		//商品种类
	int nums;
};
class Order {
public:
	Order() {
		totalMoney = 0;
	}
	Order(vector<Item>& a, int& b) {
		for (int i = 0; i < a.size(); ++i) {
			items.push_back(a[i]);
		}
		totalMoney = b;
	}
	void showOrder();
	vector<Item> items;				//订单中的商品
	int totalMoney;					//总金额
};
class Cart {
public:
	void showCart();
	void showOrders();
	list<Order> orders;			//订单可以有多个
	list<Item> items;			//购物车中存储的商品及对应数量
};
class User {
public:
	virtual int getUserKind() const = 0;		//得到账号类型
	virtual void addCommodity(Commodity* pcom) = 0;
	virtual int showMyCommodity() = 0;
	virtual string changeCommodityInfo() = 0;
	void changePassword();					//修改密码	
	int getBalance() const;				    //获取账号当前余额
	bool recharge(int money);				//充值
	bool consume(int money);				//消费
	string getAccount() const;				//返回账户
	string getPassword() const;				//返回密码
	void updateUserFile();					//更新文件信息
	Cart cart;								//购物车
protected:
	string account;							//账户
	string password;						//密码
	int balance;							//余额
	int kind;								//账号类型
};

class Seller : public User {
private:
	list<Commodity*> coms;					//该商家的产品
public:
	Seller();
	Seller(vector<string>& info, list<Commodity*>& commodities);
	void addCommodity(Commodity* pcom);
	string changeCommodityInfo();
	int showMyCommodity();
	int getUserKind() const;
};

class Buyer : public User {
public:
	Buyer();
	Buyer(vector<string>& info, list<Commodity*>& commodities);
	int getUserKind() const;
	void addCommodity(Commodity* pcom) {}
	string changeCommodityInfo() { return " "; }
	int showMyCommodity() { return 0; }
};
