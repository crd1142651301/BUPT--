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
	string name;		//��Ʒ����
	string acc;			//�����˺�
	string kind;		//��Ʒ����
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
	vector<Item> items;				//�����е���Ʒ
	int totalMoney;					//�ܽ��
};
class Cart {
public:
	void showCart();
	void showOrders();
	list<Order> orders;			//���������ж��
	list<Item> items;			//���ﳵ�д洢����Ʒ����Ӧ����
};
class User {
public:
	virtual int getUserKind() const = 0;		//�õ��˺�����
	virtual void addCommodity(Commodity* pcom) = 0;
	virtual int showMyCommodity() = 0;
	virtual string changeCommodityInfo() = 0;
	void changePassword();					//�޸�����	
	int getBalance() const;				    //��ȡ�˺ŵ�ǰ���
	bool recharge(int money);				//��ֵ
	bool consume(int money);				//����
	string getAccount() const;				//�����˻�
	string getPassword() const;				//��������
	void updateUserFile();					//�����ļ���Ϣ
	Cart cart;								//���ﳵ
protected:
	string account;							//�˻�
	string password;						//����
	int balance;							//���
	int kind;								//�˺�����
};

class Seller : public User {
private:
	list<Commodity*> coms;					//���̼ҵĲ�Ʒ
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
