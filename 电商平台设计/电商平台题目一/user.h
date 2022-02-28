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
protected:
	string account;							//�˻�
	string password;						//����
	int balance;							//���
	int kind;								//�˺�����
	vector<string>	record;					//���׼�¼
	void updateUserFile();
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
	Buyer(vector<string>& info);
	int getUserKind() const;

	//������������
	void addCommodity(Commodity* pcom) {}
	string changeCommodityInfo() { return ""; }
	int showMyCommodity() { return 0; }
};
