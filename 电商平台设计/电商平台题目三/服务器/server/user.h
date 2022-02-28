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
	void showOrder(char* sendbuf, int& offset);
	vector<Item> items;				//�����е���Ʒ
	int totalMoney;					//�ܽ��
};
class Cart {
public:
	void showCart(char* sendbuf, int& offset);
	void showOrders(char* sendbuf, int& offset);
	list<Order> orders;			//���������ж��
	list<Item> items;			//���ﳵ�д洢����Ʒ����Ӧ����
};
class User {
public:
	virtual int getUserKind() const = 0;															//�õ��˺�����
	virtual void addCommodity(Commodity* pcom) = 0;
	virtual int showMyCommodity(char* sendbuf, int& offset) = 0;
	virtual string changeCommodityInfo(char* sendbuf, User* user, char recvbuf[], int& offset) = 0;
	void changePassword(char* sendbuf, User* user, char recvbuf[], int& offset);					//�޸�����	
	int getBalance() const;																			//��ȡ�˺ŵ�ǰ���
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
	string changeCommodityInfo(char* sendbuf, User* user, char recvbuf[], int& offset);
	int showMyCommodity(char* sendbuf, int& offset);
	int getUserKind() const;
};

class Buyer : public User {
public:
	Buyer();
	Buyer(vector<string>& info, list<Commodity*>& commodities);
	int getUserKind() const;
	void addCommodity(Commodity* pcom) {}
	string changeCommodityInfo(char* sendbuf, User* user, char recvbuf[], int& offset) { return " "; }
	int showMyCommodity(char* sendbuf, int& offset) { return 0; }
};