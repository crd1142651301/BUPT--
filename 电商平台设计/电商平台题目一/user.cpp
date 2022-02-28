#include "user.h"


/*User�������Ķ���*/
void User::updateUserFile() {
	ofstream ofs("./�û�/" + account + ".txt", ofstream::out);
	ofs << "Account: " << account << endl;
	ofs << "Password: " << password << endl;
	ofs << "Balance: " << balance << endl;
	ofs << "AccountKind: " << kind << endl;
}
void User::changePassword() {
	cout << "�����뵱ǰ���룺" << endl;
	string curPassword;
	cin >> curPassword;
	if (curPassword == password) {
		string p1;
		cout << "������������:" << endl;
		cin >> p1;
		password = p1;
		updateUserFile();
		cout << "�޸ĳɹ�" << endl;
	}
	else {
		cout << "��������޸�ʧ��" << endl;
	}
}
bool User::recharge(int money) {
	if (money > 0) {
		balance += money;
		updateUserFile();
		return true;
	}
	return false;
}
bool User::consume(int money) {
	if (money >= 0) {
		balance -= money;
		updateUserFile();
		return true;
	}
	return false;
}
int User::getBalance() const {
	return balance;
}
string User::getAccount() const {
	return account;
}
string User::getPassword() const {
	return password;
}

/*Seller�̼���Ķ���*/
int Seller::getUserKind() const {
	return kind;
}
Seller::Seller(vector<string>& info, list<Commodity*>& commodities) {
	account = info[0];
	password = info[1];
	balance = string_to_int(info[2]);
	kind = string_to_int(info[3]);
	for (int i = 4; i < info.size(); ++i) {
		record.push_back(info[i]);
	}
	for (auto it : commodities) {
		if (it->getAccount() == account) {
			coms.push_back(it);
		}
	}
}
void Seller::addCommodity(Commodity* pcom) {
	coms.push_back(pcom);
}
int Seller::showMyCommodity() {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "��Ʒ���" << setw(14) << "��Ʒ����" << setw(14) << "�����ʻ�"
		<< setw(14) << "��Ʒ����" << setw(14) << "��Ʒ�۸�" << setw(14) << "��Ʒ���" << endl;
	int num = 1;
	cout << "-----------------------------------------------------------------------------------" << endl;
	for (const auto& pcom : coms) {
		cout << setiosflags(ios::left) << setw(14) << num++ << setw(14) << pcom->getName() << setw(14) << pcom->getAccount()
			<< setw(14) << pcom->getKind() << setw(14) << pcom->getValue() << setw(14) << pcom->getStock()
			<< endl;
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	return coms.size();
}
/*Buyer�̼���Ķ���*/
int Buyer::getUserKind() const {
	return kind;
}
Buyer::Buyer(vector<string>& info) {
	account = info[0];
	password = info[1];
	balance = string_to_int(info[2]);
	kind = string_to_int(info[3]);
	for (int i = 4; i < info.size(); ++i) {
		record.push_back(info[i]);
	}
}
string Seller::changeCommodityInfo() {
	cout << "�����Ʒ���£�" << endl;
	showMyCommodity();
	cout << "��ѡ�������޸���Ʒ�����" << endl;
	int num;
	cin >> num;
	if (num > coms.size() || num <= 0) {
		cout << "�޴���Ŷ�Ӧ����Ʒ���޸�ʧ��" << endl;
		return "*";
	}
	cout << "��ѡ�������޸���Ʒ����Ϣ" << endl;
	cout << "1 - �۸����   2 - ʣ��������  3 - ���ƹ���  4 - �ۿ����͹���" << endl;
	int way;
	cin >> way;
	switch (way) {
	case 1: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "�������������ӻ���ٶ��ټ۸�" << endl;
		int x;
		cin >> x;
		bool success = (*it)->changeValue(x);
		if (!success) {
			cout << "�۸��ܽ�Ϊ�������޸�ʧ��" << endl;
			return "*";
		}
		cout << "�޸ĳɹ�" << endl;
		return (*it)->getKind();
	}
		  break;
	case 2: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "�������������ӻ���ٶ�����Ʒ����" << endl;
		int x;
		cin >> x;
		bool success = (*it)->changeStock(x);
		if (!success) {
			cout << "��Ʒ��������Ϊ��, �޸�ʧ��" << endl;
			return "*";
		}
		cout << "�޸ĳɹ�" << endl;
		return (*it)->getKind();
	}
		  break;
	case 3: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "����������Ϊ��Ʒ���޸ĵ�����" << endl;
		string x;
		cin >> x;
		bool success = (*it)->changeName(x);
		if (!success) {
			cout << "��Ʒ���Ʋ���Ϊ��,�޸�ʧ��" << endl;
			return "*";
		}
		cout << "�޸ĳɹ�" << endl;
		return (*it)->getKind();
	}
		  break;
	case 4: {
		cout << "������������۵�����(clothes food book)" << endl;
		string k;
		cin >> k;
		if (!(k == CLOTHES || k == FOOD || k == BOOK)) {
			cout << "�޴�����,�޸�ʧ��" << endl;
			return "*";
		}
		cout << "������������۵��ۿ�(1 - 9)" << endl;
		int discount;
		cin >> discount;
		if (discount < 1 || discount > 9) {
			cout << "����Υ�棬�޸�ʧ��" << endl;
			return "*";
		}
		for (list<Commodity*>::iterator _it = coms.begin(); _it != coms.end(); ++_it) {
			if ((*_it)->getAccount() == account && (*_it)->getKind() == k) {
				(*_it)->changeDiscount(discount);
			}
		}
		cout << "�޸ĳɹ�" << endl;
		return "*";
	}
		  break;
	default:
		cout << "�޴˲������޸�ʧ��" << endl;
		return "*";
		break;
	}
}



