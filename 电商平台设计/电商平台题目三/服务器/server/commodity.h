#include<string>
#include<vector>
#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#define FOOD "food"
#define CLOTHES "clothes"
#define BOOK "book"
using namespace std;

class Commodity {
public:
	Commodity() {};
	virtual int getPrice(int n);			//虚函数，计算最终价格
	string getAccount() const;				//得到商品所属账户
	string getKind() const;					//得到商品类型
	string getName() const;					//得到商品名称
	int getValue() const;					//得到商品价格
	int getStock() const;					//得到商品库存数
	bool changeName(string n);				//修改商品名称
	bool changeValue(int num);			    //修改商品价格
	bool changeStock(int num);				//修改商品库存,num>0涨价，num<0降价，最终价格不能小于0；
	bool changeDiscount(int num);
protected:
	string name;			//商品名称
	string account;			//该商品的所属账户
	string kind;			//商品种类
	int value;				//商品价格
	int stock;				//商	品库存量
	int discount;
};


class Food : public Commodity {
public:
	Food() {}
	Food(vector<string> info);
	int getPrice(int n);
};

class Book : public Commodity {
public:
	Book() {}
	Book(vector<string> info);
	int getPrice(int n);
};

class Clothes : public Commodity {
public:
	Clothes() {}
	Clothes(vector<string> info);
	int getPrice(int n);
};

extern int string_to_int(string s);