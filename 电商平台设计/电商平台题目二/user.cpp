#include "user.h"


/* ���ﳵ */
void Cart::showCart() {
	if (items.size() == 0) {
		cout << "���ﳵΪ��" << endl;
		return;
	}
	cout << "���ﳵ�������£�" << endl;
	cout << "---------------------------------" << endl;
	int x = 1;
	for (Item item : items) {
		cout << x++ << "   " << item.pcom->getName() << " �� " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
	}
	cout << "----------------------------------" << endl;
}
void Cart::showOrders() {
	list<Order>::iterator it = orders.begin();
	for (int i = 0; i < orders.size(); ++i) {
		cout << "����" << i + 1 << ":" << endl;
		(*it).showOrder();
		++it;
	}
}
/* ���� */
void Order::showOrder() {
	cout << "---------------------------------" << endl;
	int x = 1;
	for (Item item : items) {
		cout << x++ << " " << item.pcom->getName() << " �� " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
	}
	cout << "�ܼƽ��: " << totalMoney << "Ԫ" << endl;
	cout << "----------------------------------" << endl;
}
/*User�������Ķ���*/
void User::updateUserFile() {
	ofstream ofs("./�û�/" + account + ".txt", ofstream::out);
	ofs << "Account: " << account << endl;
	ofs << "Password: " << password << endl;
	ofs << "Balance: " << balance << endl;
	ofs << "AccountKind: " << kind << endl;
	for (auto it = cart.items.begin(); it != cart.items.end(); ++it) {
		ofs << it->name << " " << it->acc << " " << it->kind << " " << it->nums << endl;
	}
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
		cout << "�޸ĳɹ�" << endl;
		updateUserFile();
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
	Item item;
	int i = 4;
	while (i < info.size()) {
		item.pcom = nullptr;
		item.name = info[i++];
		item.acc = info[i++];
		item.kind = info[i++];
		item.nums = string_to_int(info[i++]);
		cart.items.push_back(item);
	}
	for (auto it : commodities) {
		if (it->getAccount() == account) {
			coms.push_back(it);
		}
		for (auto _it = cart.items.begin(); _it != cart.items.end(); ++_it) {
			if (_it->acc == it->getAccount() && _it->name == it->getName() && _it->kind == it->getKind()) {
				_it->pcom = it;
			}
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
Buyer::Buyer(vector<string>& info, list<Commodity*>& commodities) {
	account = info[0];
	password = info[1];
	balance = string_to_int(info[2]);
	kind = string_to_int(info[3]);
	Item item;
	int i = 4;
	while (i < info.size()) {
		item.pcom = nullptr;
		item.name = info[i++];
		item.acc = info[i++];
		item.kind = info[i++];
		item.nums = string_to_int(info[i++]);
		cart.items.push_back(item);
	}
	for (auto it : commodities) {
		for (auto _it = cart.items.begin(); _it != cart.items.end(); ++_it) {
			if (_it->acc == it->getAccount() && _it->name == it->getName() && _it->kind == it->getKind()) {
				_it->pcom = it;
			}
		}
	}
}

string Seller::changeCommodityInfo() {
	cout << "�����Ʒ���£�" << endl;
	showMyCommodity();
	cout << "��ѡ�������޸���Ʒ����Ϣ" << endl;
	cout << "1 - �۸����   2 - ʣ��������  3 - ���ƹ���  4 - �ۿ����͹���" << endl;
	int way;
	cin >> way;
	switch (way) {
	case 1: {
		cout << "��ѡ�������޸���Ʒ�����" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "�޴���Ŷ�Ӧ����Ʒ���޸�ʧ��" << endl;
			return "*";
		}
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
		cout << "��ѡ�������޸���Ʒ�����" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "�޴���Ŷ�Ӧ����Ʒ���޸�ʧ��" << endl;
			return "*";
		}
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
		cout << "��ѡ�������޸���Ʒ�����" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "�޴���Ŷ�Ӧ����Ʒ���޸�ʧ��" << endl;
			return "*";
		}
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
		return k;
	}
		  break;
	default:
		cout << "�޴˲������޸�ʧ��" << endl;
		return "*";
		break;
	}
}

