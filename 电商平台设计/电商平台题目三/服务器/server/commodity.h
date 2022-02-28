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
	virtual int getPrice(int n);			//�麯�����������ռ۸�
	string getAccount() const;				//�õ���Ʒ�����˻�
	string getKind() const;					//�õ���Ʒ����
	string getName() const;					//�õ���Ʒ����
	int getValue() const;					//�õ���Ʒ�۸�
	int getStock() const;					//�õ���Ʒ�����
	bool changeName(string n);				//�޸���Ʒ����
	bool changeValue(int num);			    //�޸���Ʒ�۸�
	bool changeStock(int num);				//�޸���Ʒ���,num>0�Ǽۣ�num<0���ۣ����ռ۸���С��0��
	bool changeDiscount(int num);
protected:
	string name;			//��Ʒ����
	string account;			//����Ʒ�������˻�
	string kind;			//��Ʒ����
	int value;				//��Ʒ�۸�
	int stock;				//��	Ʒ�����
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