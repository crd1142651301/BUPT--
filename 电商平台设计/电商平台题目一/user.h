#include "commodity.h"
#include<list>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<iomanip>
#define BUYER 0
#define SELLER 1

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
protected:
	string account;							//账户
	string password;						//密码
	int balance;							//余额
	int kind;								//账号类型
	vector<string>	record;					//交易记录
	void updateUserFile();
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
	Buyer(vector<string>& info);
	int getUserKind() const;

	//对消费者无用
	void addCommodity(Commodity* pcom) {}
	string changeCommodityInfo() { return ""; }
	int showMyCommodity() { return 0; }
};
