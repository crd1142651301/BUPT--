#include "trade.h"
#include<set>

Trade::Trade() {
	ifstream file1, file2, file3;
	file1.open("./商品/book.txt", ifstream::in);
	file2.open("./商品/clothes.txt", ifstream::in);
	file3.open("./商品/food.txt", ifstream::in);
	if (file1 && file2 && file3) {
		string line;
		while (getline(file1, line)) {
			//string name, account, kind, value, stock;
			vector<string> info;
			istringstream record(line);
			for (int i = 0; i < 5; ++i) {
				string temp;
				record >> temp;
				info.push_back(temp);
			}
			Book book(info);
			Commodity* pCom = new Book(book);
			commodities.push_back(pCom);
		}
		while (getline(file2, line)) {
			//string name, account, kind, value, stock;
			vector<string> info;
			istringstream record(line);
			for (int i = 0; i < 5; ++i) {
				string temp;
				record >> temp;
				info.push_back(temp);
			}
			Clothes clothes(info);
			Commodity* pCom = new Clothes(info);
			commodities.push_back(pCom);
		}
		while (getline(file3, line)) {
			//string name, account, kind, value, stock;
			vector<string> info;
			istringstream record(line);
			for (int i = 0; i < 5; ++i) {
				string temp;
				record >> temp;
				info.push_back(temp);
			}
			Food food(info);
			Commodity* pCom = new Food(food);
			commodities.push_back(pCom);
		}
		file1.close();
		file2.close();
		file3.close();
	}
	else {
		cout << "商品文件打开出错" << endl;
	}
}
void Trade::userSignIn(char* sendbuf,User*& user, char recvbuf[], int& offset) {
	char _account[16] = {};
	char _password[16] = {};
	memcpy(_account, &(recvbuf[4]), sizeof(char) * 16);
	memcpy(_password, &(recvbuf[20]), sizeof(char) * 16);
	string inuptAccount(_account);
	ifstream file;
	file.open("./用户/" + inuptAccount + ".txt");
	if (file) {
		string line, temp1, temp2, temp3, temp4;
		vector<string> info;
		int i = 0;
		/* 读入账号和密码 */
		while (getline(file, line) && i < 2) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
			++i;
		}
		string password(_password);
		if (info.back() == password) {
			/* 这里之前出错了，少读了一行，读入余额 */
			istringstream record1(line);
			record1 >> temp1;
			record1 >> temp2;
			info.push_back(temp2);
			/* 读入类型种类 */
			getline(file, line);
			istringstream record2(line);
			record2 >> temp1;
			record2 >> temp2;
			info.push_back(temp2);
			/* 读入购物车 */
			while (getline(file, line)) {
				istringstream record(line);
				record >> temp1;
				record >> temp2;
				record >> temp3;
				record >> temp4;
				info.push_back(temp1);
				info.push_back(temp2);
				info.push_back(temp3);
				info.push_back(temp4);
			}
			file.close();
			if (string_to_int(info[3]) == BUYER) {		//买家
				Buyer buyer(info, commodities);
				user = new Buyer(buyer);
			}
			else {
				Seller seller(info, commodities);
				user = new Seller(seller);
			}
			char s[50] = "登录成功!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return; 
		}
		else {
			char s[50] = "密码错误，请重新登录!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			file.close();
		}
	}
	else {
		char s[50] = "账号不存在，请您检查账号输入是否正确!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
}
bool Trade::userSignUp(char* sendbuf, char recvbuf[], int& offset) {
	char account[16] = {};
	char password[16] = {};
	memcpy(account, &(recvbuf[4]), sizeof(char) * 16);
	memcpy(password, &(recvbuf[20]), sizeof(char) * 16);
	char kind = recvbuf[36];
	string inputAccount(account);
	ifstream file;
	file.open("./用户/" + inputAccount + ".txt");
	if (file) {
		char s[50] = "账号已存在，请换个账号重新注册!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		file.close();
	}
	else {
		ofstream ofs;
		ofs.open("./用户/" + inputAccount + ".txt", ofstream::out);
		if (ofs) {
			ofs << "Account: " << inputAccount << endl;
			ofs << "Password: " << password << endl;
			ofs << "Balance: 0" << endl;
			ofs << "AccountKind: " << kind << endl;
			ofs.close();
			char s[50] = "注册成功!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return true;
		}
		else {
			char s[50] = "注册失败!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
		}
	}
	return false;
}
void Trade::showAllCommodity(char* sendbuf, int& offset) {
	int num = 0;
	int _offset = offset;
	offset += sizeof(int);
	for (const auto& pcom : commodities) {
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
}
void Trade::searchCommoddity(char* sendbuf, int& offset, char recvbuf[]) {
	char name[16] = {};
	memcpy(name, &(recvbuf[4]), sizeof(char) * 16);
	string t(name);
	int num = 0;
	int _offset = offset;
	offset += sizeof(int);
	for (const auto& pcom : commodities) {
		string s = pcom->getName();
		if (KMPcompare(s, t)) {
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
	}
	int _num = htonl(num);
	memcpy(sendbuf + _offset, &_num, sizeof(int));
}
//KMP算法实现搜索字符串匹配
bool Trade::KMPcompare(string s, string p) {
	for (char& ch : s) {
		if (ch >= 'A' && ch <= 'Z') {
			ch = ch + 'a' - 'A';
		}
	}
	for (char& ch : p) {
		if (ch >= 'A' && ch <= 'Z') {
			ch = ch + 'a' - 'A';
		}
	}
	int n = s.size(), m = p.size();
	if (m == 0) return 0;
	//设置哨兵
	s.insert(s.begin(), ' ');
	p.insert(p.begin(), ' ');
	vector<int> next(m + 1);
	//预处理next数组
	for (int i = 2, j = 0; i <= m; i++) {
		while (j and p[i] != p[j + 1]) j = next[j];
		if (p[i] == p[j + 1]) j++;
		next[i] = j;
	}
	//匹配过程
	for (int i = 1, j = 0; i <= n; i++) {
		while (j and s[i] != p[j + 1]) j = next[j];
		if (s[i] == p[j + 1]) j++;
		if (j == m) return true;
	}
	return false;
}
string Trade::inputPassword(int type) {
	string password;
	int length = 12;
	char ch;
	if (type == 1) {
		cout << "请输入密码(字母数字或字符)：" << endl;
	}
	else {
		cout << "请输入确认密码(字母数字或字符)：" << endl;
	}
	while (((ch = _getch()) != 13)) {
		if (ch == 8) {
			cout << "\b";
			cout << " ";
			cout << "\b";
			if (password.size() > 0)		password.pop_back();
		}
		else if (ch >= 33 && ch <= 126) {
			_putch('*');
			fflush(stdin);
			password += ch;
		}
	}
	cout << endl;
	return password;
}


/* 登录后 */
void Trade::buyCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	int num, cnt;
	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	num = ntohl(*pID);
	memcpy(pID, &(recvbuf[8]), sizeof(int));
	cnt = ntohl(*pID);
	delete pID;
	pID = nullptr;

	if (num <= 0 || num > commodities.size()) {
		char s[50] = "购买失败，输入不符合规定范围或余额不足!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	list<Commodity*>::iterator it = commodities.begin();
	for (; it != commodities.end() && num > 1; ++it)	--num;
	int total = (*it)->getPrice(cnt);
	if (cnt > 0 && cnt <= (*it)->getStock() && total <= user->getBalance()) {
		/* 支付成功，更新商品文件夹 */
		(*it)->changeStock(-cnt);
		string kind = (*it)->getKind();
		updateCommodityFile("./商品/" + kind + ".txt", kind);

		/* 买家和卖家是同一个人，则账户金额无需改变 
		if (user->getAccount() == (*it)->getAccount()) {
			char s[50] = "购买成功!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return;
		}*/

		/* 减去买家花费并更新买家文件 */
		user->consume(total);

		/* 这里的账户一定存在且为商家账户，支付成功改变余额并更新商家文件夹 */
		string account = (*it)->getAccount();
		ifstream file("./用户/" + account + ".txt", ifstream::in);
		vector<string> info;
		string line, temp1, temp2;
		while (getline(file, line)) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
		}
		file.close();
		Seller seller(info, commodities);
		seller.recharge(total);
		char s[50] = "购买成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
	else {
		char s[50] = "购买失败，输入不符合规定范围或余额不足!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
}
void Trade::addCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	if (user->getUserKind() == BUYER) {
		char s[50] = "当前登陆账户类型为消费者，无权添加商品!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	char name[16] = {}, kind[16] = {}, value[8] = {}, stock[8] = {};
	memcpy(name, &(recvbuf[4]), sizeof(char) * 16);
	memcpy(kind, &(recvbuf[20]), sizeof(char) * 16);
	memcpy(value, &(recvbuf[36]), sizeof(char) * 8);
	memcpy(stock, &(recvbuf[44]), sizeof(char) * 8);

	vector<string> info;
	string n(name), a(user->getAccount()), k(kind), v(value), s(stock);
	info.push_back(n);
	info.push_back(a);
	info.push_back(k);
	info.push_back(v);
	info.push_back(s);
	Commodity* pcom = nullptr;

	if (k == FOOD) {
		Food food(info);
		pcom = new Food(food);
		commodities.push_back(pcom);
		user->addCommodity(pcom);
		updateCommodityFile("./商品/food.txt", "food");
	}
	else if (k == CLOTHES) {
		Clothes clothes(info);
		pcom = new Clothes(clothes);
		commodities.push_back(pcom);
		user->addCommodity(pcom);
		updateCommodityFile("./商品/clothes.txt", "clothes");
	}
	else if (k == BOOK) {
		Book book(info);
		pcom = new Book(book);
		commodities.push_back(pcom);
		user->addCommodity(pcom);
		updateCommodityFile("./商品/book.txt", "book");
	}
	user->addCommodity(pcom);
	char _s[50] = "添加成功!";
	memcpy(sendbuf + offset, _s, sizeof(char) * 50);
}
void Trade::updateCommodityFile(const string& filename, const string& kind) {
	ofstream ofs(filename, ofstream::out);
	for (list<Commodity*>::iterator it = commodities.begin(); it != commodities.end(); ++it) {
		if ((*it)->getKind() == kind) {
			ofs << (*it)->getName() << " ";
			ofs << (*it)->getAccount() << " ";
			ofs << (*it)->getKind() << " ";
			ofs << (*it)->getValue() << " ";
			ofs << (*it)->getStock() << " ";
			ofs << endl;
		}
	}
}
void Trade::changeCommodityInfo(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	string k = user->changeCommodityInfo(sendbuf, user, recvbuf, offset);
	if (k != "*") {
		updateCommodityFile("./商品/" + k + ".txt", k);
	}
}



/* 题目二新加功能 */
void Trade::manageCart(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	int way = ntohl(*pID);
	delete pID;
	pID = nullptr;
	switch (way) {
	case 1:
		addComToCart(sendbuf, user, recvbuf, offset);
		break;
	case 2:
		subComToCart(sendbuf, user, recvbuf, offset);
		break;
	default:
		cout << "错误选项，修改失败" << endl;
		break;
	}
}
void Trade::makeOrders(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	if (cart.items.size() == 0) {
		char s[50] = "购物车为空，生成订单失败!";
		memcpy(sendbuf, s, sizeof(char) * 50);
		return;
	}


	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	int num = ntohl(*pID);
	set<int> set;
	int x = 4 + sizeof(int);
	for (int i = 0; i < num; ++i) {
		memcpy(pID, &(recvbuf[x]), sizeof(int));
		x += sizeof(int);
		int seq = ntohl(*pID);
		if (seq > 0 && seq <= cart.items.size()) {
			set.insert(seq);
		}
	}
	delete pID;
	pID = nullptr;

	if (set.size() == 0 || set.size() != num) {
		char s[50] = "输入商品错误,生成订单失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	/* 创建新订单并加入 */
	Order order;
	int seq = 1;
	for (list<Item>::iterator it = cart.items.begin(); it != cart.items.end(); ) {
		if (set.count(seq)) {
			order.items.push_back(*it);
			cart.items.erase(it++);
		}
		else {
			++it;
		}
		++seq;
	}
	/* 更新删除购物车后的文件 */
	user->updateUserFile();

	for (Item item : order.items) {
		//cout << x++ << " " << item.pcom->getName() << " × " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
		/* 生成订单改变内存中的商品数量，不更新文件夹 */
		order.totalMoney += item.pcom->getPrice(item.nums);
		item.pcom->changeStock(-item.nums);
	}
	//cout << "总计金额: " << order.totalMoney << "元" << endl;
	//cout << "--------------------------------" << endl;

	cart.orders.push_back(order);

	char s[50] = "生成订单成功!";
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
}
void Trade::onlinePayment(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	if (cart.orders.size() == 0) {
		char s[50] = "您当前无订单,支付失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	int seq = ntohl(*pID);
	delete pID;
	pID = nullptr;
	
	if (seq <= 0 || seq > cart.orders.size()) {
		char s[50] = "无此订单，支付失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	int x = 1;
	vector<Item> items;
	list<Order> tempOrders;
	int totalMoney = 0;
	for (list<Order>::iterator it = cart.orders.begin(); it != cart.orders.end(); ) {
		if (x == seq) {
			for (int i = 0; i < (*it).items.size(); ++i) {
				items.push_back((*it).items[i]);
			}
			totalMoney = (*it).totalMoney;
			cart.orders.erase(it++);
		}
		else {
			tempOrders.push_back(*it);
			++it;
		}
		++x;
	}


	if (user->getBalance() < totalMoney) {
		char s[50] = "您的余额不足,支付失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	/* 减去当前买家账户消费的费用并更新文件 */
	user->consume(totalMoney);

	for (Item item : items) {

		/* 支付成功，更新商品文件夹 */
		string kind = item.pcom->getKind();
		updateCommodityFile("./商品/" + kind + ".txt", kind);

		/* 这里的账户一定存在且为商家账户，支付成功改变余额并更新商家文件夹 */
		string account = item.pcom->getAccount();
		ifstream file("./用户/" + account + ".txt", ifstream::in);
		vector<string> info;
		string line, temp1, temp2;
		while (getline(file, line)) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
		}
		file.close();

		/* 建立卖家账户，对其充值相应的金额并更新到文件 */
		Seller seller(info, commodities);
		seller.recharge(item.pcom->getPrice(item.nums));

		/* 如果卖家买了自己的产品，重新更新账号 
		if (seller.getAccount() == user->getAccount()) {
			delete user;
			user = nullptr;
			/* 订单不能减少 
			user = new Seller(seller);
			auto it = tempOrders.begin();
			for (int i = 0; i < tempOrders.size(); ++i) {
				user->cart.orders.push_back(*it);
				++it;
			}
		}*/
	}

	/* 支付成功删除此订单 */
	char s[50] = "支付成功!";
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
}

/* 释放掉list中new出来的元素,并清空list */
Trade::~Trade() {
	for (list<Commodity*>::iterator it = commodities.begin(); it != commodities.end();) {
		delete* it;
		commodities.erase(it++);
	}
}

void Trade::addComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	int num, cnt;

	int* pID = new int;
	memcpy(pID, &(recvbuf[8]), sizeof(int));
	num = ntohl(*pID);
	memcpy(pID, &(recvbuf[12]), sizeof(int));
	cnt = ntohl(*pID);
	delete pID;
	pID = nullptr;

	if (num <= 0 || num > commodities.size()) {
		char s[50] = "输入序号不合法，已退出添加商品!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	list<Commodity*>::iterator it = commodities.begin();
	for (; it != commodities.end() && num > 1; ++it)	--num;
	if (num == 1 && it != commodities.end() && cnt <= (*it)->getStock() && cnt > 0) {
		list<Item>::iterator _it = cart.items.begin();
		for (; _it != cart.items.end(); ++_it) {
			if ((*it) == (*_it).pcom) {
				break;
			}
		}
		if (_it == cart.items.end()) {	//购物车中无此商品
			Item item;
			item.nums = cnt;
			item.name = (*it)->getName();
			item.acc = (*it)->getAccount();
			item.kind = (*it)->getKind();
			item.pcom = *it;
			cart.items.push_back(item);
		}
		else {	//购物车中已经存在此商品，只添加数目
			(*_it).nums += cnt;
		}
		user->updateUserFile();
		char s[50] = "添加成功!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
	else {
		char s[50] = "添加失败，请查看商品数量是否规范!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
}
void Trade::subComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	int way, num;
	int* pID = new int;
	memcpy(pID, &(recvbuf[8]), sizeof(int));
	way = ntohl(*pID);
	memcpy(pID, &(recvbuf[12]), sizeof(int));
	num = ntohl(*pID);

	if (cart.items.size() == 0) {
		char s[50] = "购物车为空，无法删除!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	if (num <= 0 || num > cart.items.size()) {
		char s[50] = "输入序号不合法，已退出删除!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	list<Item>::iterator it = cart.items.begin();
	for (; it != cart.items.end() && num > 1; ++it)		--num;

	if (way == 1) {
		if (num == 1 && it != cart.items.end()) {
			cart.items.erase(it);
			user->updateUserFile();
			char s[50] = "删除成功!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
		else {
			char s[50] = "删除失败，请查看输入数量是否符合规范!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
	}
	else if (way == 2) {
		memcpy(pID, &(recvbuf[16]), sizeof(int));
		int cnt = ntohl(*pID);

		if (num == 1 && it != cart.items.end() && cnt <= (*it).nums && cnt > 0) {
			(*it).nums -= cnt;
			if ((*it).nums == 0) {
				cart.items.erase(it);
			}
			user->updateUserFile();
			char s[50] = "删除成功!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
		else {
			char s[50] = "删除失败，请查看输入数量是否符合规范!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
	}
	else {
		char s[50] = "无此删除种类，删除失败!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}

	delete pID;
	pID = nullptr;
}

bool Trade::updateMyData(User*& user) {
	string _account = user->getAccount();
	string _password = user->getPassword();
	
	list<Order> orders;
	for (auto it = user->cart.orders.begin(); it != user->cart.orders.end(); ++it) {
		orders.push_back(*it);
	}

	delete user;
	user = nullptr;
	ifstream file;
	file.open("./用户/" + _account + ".txt");
	if (file) {
		string line, temp1, temp2, temp3, temp4;
		vector<string> info;
		int i = 0;
		/* 读入账号和密码 */
		while (getline(file, line) && i < 2) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
			++i;
		}
		string password(_password);
		if (info.back() == password) {
			/* 这里之前出错了，少读了一行，读入余额 */
			istringstream record1(line);
			record1 >> temp1;
			record1 >> temp2;
			info.push_back(temp2);
			/* 读入类型种类 */
			getline(file, line);
			istringstream record2(line);
			record2 >> temp1;
			record2 >> temp2;
			info.push_back(temp2);
			/* 读入购物车 */
			while (getline(file, line)) {
				istringstream record(line);
				record >> temp1;
				record >> temp2;
				record >> temp3;
				record >> temp4;
				info.push_back(temp1);
				info.push_back(temp2);
				info.push_back(temp3);
				info.push_back(temp4);
			}
			file.close();
			if (string_to_int(info[3]) == BUYER) {		//买家
				Buyer buyer(info, commodities);
				user = new Buyer(buyer);
			}
			else {
				Seller seller(info, commodities);
				user = new Seller(seller);
			}
			for (auto _it = orders.begin(); _it != orders.end(); ++_it) {
				user->cart.orders.push_back(*_it);
			}
			//cout << "账号更新成功" << endl;
			return true;
		}
	}
	else {
		cout << "账号更新失败" << endl;
	}
	return false;
}

void Trade::handleBuf(char recvbuf[], char* sendbuf, User*& user) {
	int offset = 0;
	memcpy(sendbuf + offset, recvbuf, sizeof(int));
	offset += sizeof(int);

	int* pID = new int;
	memcpy(pID, recvbuf, sizeof(int));
	int choice = ntohl(*pID);
	delete pID;
	pID = nullptr;

	if (!user) {			//未登录
		switch (choice) {
		case 0: 			//打印菜单，无需额外填充
			break;
		case 1: {			//登录，获取账号密码,填充是否登录成功
			userSignIn(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 2: {			//注册，获取账号密码，填充是否注册成功
			userSignUp(sendbuf, recvbuf, offset);
		}
			  break;
		case 3: {			//填充所有商品信息
			showAllCommodity(sendbuf, offset);
		}
			  break;
		case 4: {			//获取搜索字符串，填充搜索商品结果
			searchCommoddity(sendbuf, offset, recvbuf);
		}
			  break;
		default:
			break;
		}
	}
	else {					//已登录
		switch (choice) {
		case 0:				//打印菜单，无需额外填充
			break;
		case 1: {			//购买商品，填充商品回复信息及结果
			buyCommodity(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 2: {			//修改账户密码，填充是否修改成功
			user->changePassword(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 3: {			//余额查询，填充账户余额
			int balance = user->getBalance();
			string t = "当前您的余额为" + to_string(balance) + "元!";
			char s[50] = {};
			t.copy(s, t.size());
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			offset += sizeof(char) * 50;
		}
			  break;
		case 4: {			//余额充值，填充充值结果
			int* pID = new int;
			memcpy(pID, &(recvbuf[4]), sizeof(int));
			int money = ntohl(*pID);
			delete pID;
			pID = nullptr;
			bool success = user->recharge(money);
			if (success) {
				char s[50] = "充值成功!";
				memcpy(sendbuf + offset, s, sizeof(char) * 50);
				offset += sizeof(char) * 50;
			}
			else {
				char s[50] = "充值失败!";
				memcpy(sendbuf + offset, s, sizeof(char) * 50);
				offset += sizeof(char) * 50;
			}
		}
			  break;
		case 5: {			//展示我的商品信息，填充我的商品
			user->showMyCommodity(sendbuf, offset);
		}
			  break;
		case 6: {			//展示所有商品信息，填充所有商品
			showAllCommodity(sendbuf, offset);
		}
			  break;
		case 7: {			//搜索商品信息，填充搜索结果
			searchCommoddity(sendbuf, offset, recvbuf);
		}
			  break;
		case 8: {			//添加商品，填充添加商品的结果
			addCommodity(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 9: {			//商品信息修改，填充信息修改结果
			changeCommodityInfo(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 10: {			//购物车管理，填充管理结果
			manageCart(sendbuf, user, recvbuf, offset);
		}
			   break;
		case 11: {			//查看购物车，填充购物车内容
			user->cart.showCart(sendbuf, offset);
		}
			   break;
		case 12: {			//生成订单，填充生成结果
			makeOrders(sendbuf, user, recvbuf, offset);
		}
			   break;
		case 13: {			//查看订单，填充订单内容
			user->cart.showOrders(sendbuf, offset);
		}
			   break;
		case 14: {			//网上支付，填充支付结果
			onlinePayment(sendbuf, user, recvbuf, offset);
		}
			   break;
		default:
			break;
		}
	}
}

