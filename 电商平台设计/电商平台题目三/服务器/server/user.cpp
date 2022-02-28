#include "user.h"


/* 购物车 */
void Cart::showCart(char* sendbuf, int& offset) {
	int num = items.size();
	int _num = ntohl(num);
	memcpy(sendbuf + offset, &_num, sizeof(int));
	offset += sizeof(int);

	for (Item item : items) {
		string t = item.pcom->getName() + " × " + to_string(item.nums) + " = " + to_string(item.pcom->getPrice(item.nums));
		char s[50] = {};
		t.copy(s, t.size());
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}

}
	
void Cart::showOrders(char* sendbuf, int& offset) {
	/* 首先填充订单个数 */
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
/* 订单 */
void Order::showOrder(char* sendbuf, int& offset) {
	/* 填充每个订单的商品个数 */
	int num = items.size();
	int _num = ntohl(num);
	memcpy(sendbuf + offset, &_num, sizeof(int));
	offset += sizeof(int);

	for (Item item : items) {
		string t = item.pcom->getName() + " × " + to_string(item.nums) + " = " + to_string(item.pcom->getPrice(item.nums));
		char s[50] = {};
		t.copy(s, t.size());
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}
	string t = "总计金额: " + to_string(totalMoney) + "元";
	char s[50] = {};
	t.copy(s, t.size());
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
	offset += sizeof(char) * 50;
}
/*User抽象基类的定义*/
void User::updateUserFile() {
	ofstream ofs("./用户/" + account + ".txt", ofstream::out);
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
		cout << "修改成功" << endl;
		updateUserFile();
		char s[50] = "修改成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		offset += sizeof(char) * 50;
	}
	else {
		char s[50] = "密码错误，修改失败!";
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

/*Seller商家类的定义*/
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
/*Buyer商家类的定义*/
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
			char s[50] = "无此种类,修改失败!";
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
			char s[50] = "无此序号对应的商品，修改失败!";
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
			char s[50] = "商品价格不能为负, 修改失败!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "修改价格成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return (*it)->getKind();
	}
		  break;
	case 2: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		bool success = (*it)->changeStock(x);
		if (!success) {
			char s[50] = "商品数量不能为负, 修改失败!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "修改数量成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return (*it)->getKind();
	}
		  break;
	case 3: {
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		bool success = (*it)->changeName(n);
		if (!success) {
			char s[50] = "商品名称不能为空,修改失败!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return "*";
		}
		char s[50] = "修改数量成功!";
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
		char s[50] = "修改折扣成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return k;
	}
		  break;
	default: {
		char s[50] = "无此操作，修改失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		delete pID;
		pID = nullptr;
		return "*";
	}
		break;
	}
}
