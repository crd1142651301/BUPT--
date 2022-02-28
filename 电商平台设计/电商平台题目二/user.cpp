#include "user.h"


/* 购物车 */
void Cart::showCart() {
	if (items.size() == 0) {
		cout << "购物车为空" << endl;
		return;
	}
	cout << "购物车内容如下：" << endl;
	cout << "---------------------------------" << endl;
	int x = 1;
	for (Item item : items) {
		cout << x++ << "   " << item.pcom->getName() << " × " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
	}
	cout << "----------------------------------" << endl;
}
void Cart::showOrders() {
	list<Order>::iterator it = orders.begin();
	for (int i = 0; i < orders.size(); ++i) {
		cout << "订单" << i + 1 << ":" << endl;
		(*it).showOrder();
		++it;
	}
}
/* 订单 */
void Order::showOrder() {
	cout << "---------------------------------" << endl;
	int x = 1;
	for (Item item : items) {
		cout << x++ << " " << item.pcom->getName() << " × " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
	}
	cout << "总计金额: " << totalMoney << "元" << endl;
	cout << "----------------------------------" << endl;
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
void User::changePassword() {
	cout << "请输入当前密码：" << endl;
	string curPassword;
	cin >> curPassword;
	if (curPassword == password) {
		string p1;
		cout << "请输入新密码:" << endl;
		cin >> p1;
		password = p1;
		cout << "修改成功" << endl;
		updateUserFile();
	}
	else {
		cout << "密码错误，修改失败" << endl;
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
int Seller::showMyCommodity() {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "商品序号" << setw(14) << "商品种类" << setw(14) << "所属帐户"
		<< setw(14) << "商品种类" << setw(14) << "商品价格" << setw(14) << "商品库存" << endl;
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

string Seller::changeCommodityInfo() {
	cout << "你的商品如下：" << endl;
	showMyCommodity();
	cout << "请选择你想修改商品的信息" << endl;
	cout << "1 - 价格管理   2 - 剩余量管理  3 - 名称管理  4 - 折扣类型管理" << endl;
	int way;
	cin >> way;
	switch (way) {
	case 1: {
		cout << "请选择你想修改商品的序号" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "无此序号对应的商品，修改失败" << endl;
			return "*";
		}
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "请输入你想增加或减少多少价格" << endl;
		int x;
		cin >> x;
		bool success = (*it)->changeValue(x);
		if (!success) {
			cout << "价格不能降为负数，修改失败" << endl;
			return "*";
		}
		cout << "修改成功" << endl;
		return (*it)->getKind();
	}
		  break;
	case 2: {
		cout << "请选择你想修改商品的序号" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "无此序号对应的商品，修改失败" << endl;
			return "*";
		}
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "请输入你想增加或减少多少商品数量" << endl;
		int x;
		cin >> x;
		bool success = (*it)->changeStock(x);
		if (!success) {
			cout << "商品数量不能为负, 修改失败" << endl;
			return "*";
		}
		cout << "修改成功" << endl;
		return (*it)->getKind();
	}
		  break;
	case 3: {
		cout << "请选择你想修改商品的序号" << endl;
		int num;
		cin >> num;
		if (num > coms.size() || num <= 0) {
			cout << "无此序号对应的商品，修改失败" << endl;
			return "*";
		}
		list<Commodity*>::iterator it = coms.begin();
		for (; it != coms.end() && num > 1; ++it)	--num;
		cout << "请输入你想为商品新修改的名称" << endl;
		string x;
		cin >> x;
		bool success = (*it)->changeName(x);
		if (!success) {
			cout << "商品名称不能为空,修改失败" << endl;
			return "*";
		}
		cout << "修改成功" << endl;
		return (*it)->getKind();
	}
		  break;
	case 4: {
		cout << "请输入你想打折的种类(clothes food book)" << endl;
		string k;
		cin >> k;
		if (!(k == CLOTHES || k == FOOD || k == BOOK)) {
			cout << "无此种类,修改失败" << endl;
			return "*";
		}
		cout << "请输入你想打折的折扣(1 - 9)" << endl;
		int discount;
		cin >> discount;
		if (discount < 1 || discount > 9) {
			cout << "输入违规，修改失败" << endl;
			return "*";
		}
		for (list<Commodity*>::iterator _it = coms.begin(); _it != coms.end(); ++_it) {
			if ((*_it)->getAccount() == account && (*_it)->getKind() == k) {
				(*_it)->changeDiscount(discount);
			}
		}
		cout << "修改成功" << endl;
		return k;
	}
		  break;
	default:
		cout << "无此操作，修改失败" << endl;
		return "*";
		break;
	}
}

