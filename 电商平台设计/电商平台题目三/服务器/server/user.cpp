#include "user.h"


/* ���ﳵ */
void Cart::showCart(char* sendbuf, int& offset) {
	int num = items.size();
	int _num = ntohl(num);
	memcpy(sendbuf + offset, &_num, sizeof(int));
	offset += sizeof(int);

	for (Item item : items) {
		string t = item.pcom->getName() + " �� " + to_string(item.nums) + " = " + to_string(item.pcom->getPrice(item.nums));
		char s[50] = {};
		t.copy(s, t.size());
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}

}
	
void Cart::showOrders(char* sendbuf, int& offset) {
	/* ������䶩������ */
	int num = orders.size();
	int _num = ntohl(num);
	memcpy(sendbuf + offset, &_num, sizeof(int));
	offset += sizeof(int);

	list<Order>::iterator it = orders.begin();
	for (int i = 0; i < orders.size(); ++i) {
		(*it).showOrder(sendbuf, offset);
		++it;
	}
}
/* ���� */
void Order::showOrder(char* sendbuf, int& offset) {
	/* ���ÿ����������Ʒ���� */
	int num = items.size();
	int _num = ntohl(num);
	memcpy(sendbuf + offset, &_num, sizeof(int));
	offset += sizeof(int);

	for (Item item : items) {
		string t = item.pcom->getName() + " �� " + to_string(item.nums) + " = " + to_string(item.pcom->getPrice(item.nums));
		char s[50] = {};
		t.copy(s, t.size());
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}
	string t = "�ܼƽ��: " + to_string(totalMoney) + "Ԫ";
	char s[50] = {};
	t.copy(s, t.size());
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
	offset += sizeof(char) * 50;
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
void User::changePassword(char* sendbuf, User* user, char recvbuf[], int& offset) {
	char pre[16] = {};
	char now[16] = {};
	memcpy(pre, &(recvbuf[4]), sizeof(char) * 16);
	memcpy(now, &(recvbuf[20]), sizeof(char) * 16);
	string curPassword(pre);
	if (curPassword == password) {
		string p1(now);
		password = p1;
		cout << "�޸ĳɹ�" << endl;
		updateUserFile();
		char s[50] = "�޸ĳɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}
	else {
		char s[50] = "��������޸�ʧ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
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
int Seller::showMyCommodity(char* sendbuf, int& offset) {
	int num = 0;
	int _offset = offset;
	offset += sizeof(int);
	for (const auto& pcom : coms) {
		++num;
		char name[16] = {}, account[16] = {}, kind[16] = {}, value[8] = {}, stock[8] = {};
		pcom->getName().copy(name, pcom->getName().length(), 0);
		pcom->getAccount().copy(account, pcom->getAccount().length(), 0);
		pcom->getKind().copy(kind, pcom->getKind().length(), 0);
		string t1 = to_string(pcom->getValue());
		string t2 = to_string(pcom->getStock());
		t1.copy(value, t1.size());
		t2.copy(stock, t2.size());
		memcpy(sendbuf + offset, name, sizeof(char) * 16);
		offset += sizeof(char) * 16;
		memcpy(sendbuf + offset, account, sizeof(char) * 16);
		offset += sizeof(char) * 16;
		memcpy(sendbuf + offset, kind, sizeof(char) * 16);
		offset += sizeof(char) * 16;
		memcpy(sendbuf + offset, value, sizeof(char) * 8);
		offset += sizeof(char) * 8;
		memcpy(sendbuf + offset, stock, sizeof(char) * 8);
		offset += sizeof(char) * 8;
	}
	int _num = htonl(num);
	memcpy(sendbuf + _offset, &_num, sizeof(int));
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

string Seller::changeCommodityInfo(char* sendbuf, User* user, char recvbuf[], int& offset) {

	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	int way = ntohl(*pID);
	int num, x;
	char kind[16] = {}, name[16] = {};
	string k;
	string n;

	if (way == 4) {
		memcpy(kind, &(recvbuf[8]), sizeof(char) * 16);
		k = kind;
		if (!(k == CLOTHES || k == FOOD || k == BOOK)) {
			char s[50] = "�޴�����,�޸�ʧ��!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		memcpy(pID, &(recvbuf[24]), sizeof(int));
		x = ntohl(*pID);
	}
	else {
		memcpy(pID, &(recvbuf[8]), sizeof(int));
		num = ntohl(*pID);
		if (num > coms.size() || num <= 0) {
			char s[50] = "�޴���Ŷ�Ӧ����Ʒ���޸�ʧ��!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		
		if (way == 3) {
			memcpy(name, &(recvbuf[12]), sizeof(char) * 16);
			n = name;
		}
		else {
			memcpy(pID, &(recvbuf[12]), sizeof(int));
			x = ntohl(*pID);
		}
	}
	delete pID;
	pID = nullptr;

	switch (way) {
	case 1: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		bool success = (*it)->changeValue(x);
		if (!success) {
			char s[50] = "��Ʒ�۸���Ϊ��, �޸�ʧ��!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "�޸ļ۸�ɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return (*it)->getKind();
	}
		  break;
	case 2: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		bool success = (*it)->changeStock(x);
		if (!success) {
			char s[50] = "��Ʒ��������Ϊ��, �޸�ʧ��!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "�޸������ɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return (*it)->getKind();
	}
		  break;
	case 3: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		bool success = (*it)->changeName(n);
		if (!success) {
			char s[50] = "��Ʒ���Ʋ���Ϊ��,�޸�ʧ��!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "�޸������ɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return (*it)->getKind();
	}
		  break;
	case 4: {
		for (list<Commodity*>::iterator _it = coms.begin(); _it != coms.end(); ++_it) {
			if ((*_it)->getAccount() == account && (*_it)->getKind() == k) {
				(*_it)->changeDiscount(x);
			}
		}
		char s[50] = "�޸��ۿ۳ɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return k;
	}
		  break;
	default: {
		char s[50] = "�޴˲������޸�ʧ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		delete pID;
		pID = nullptr;
		return "*";
	}
		break;
	}
}
