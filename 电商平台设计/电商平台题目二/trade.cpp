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
		user = nullptr;
	}
	else {
		cout << "商品文件打开出错" << endl;
	}
}
User* Trade::getUser() {
	return user;
}
void Trade::buyCommodity() {
	showAllCommodity();
	cout << "请选择你想购买商品地序号以及购买数量" << endl;
	int num, cnt;
	cin >> num;
	cin >> cnt;
	if (num <= 0 || num > commodities.size()) {
		cout << "购买失败，输入不符合规定范围或余额不足" << endl;
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

		/* 买家和卖家是同一个人，则账户金额无需改变 */
		if (user->getAccount() == (*it)->getAccount()) {
			cout << "购买成功" << endl;
			return;
		}
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
		cout << "购买成功" << endl;
	}
	else {
		cout << "购买失败，输入不符合规定范围或余额不足" << endl;
	}
}
void Trade::printInitialInterface() {
	cout << "||==============================================||" << endl;
	cout << "               电商交易平台初始菜单				   " << endl;
	cout << "               0 -	打印菜单                        " << endl;
	cout << "               1 -	用户登录					       " << endl;
	cout << "               2 -	用户注册					       " << endl;
	cout << "               3 -	展示商品信息				       " << endl;
	cout << "               4 -	搜索商品信息				       " << endl;
	cout << "               5 -	退出						       " << endl;
	cout << "||==============================================||" << endl;
}
void Trade::printUserInterface() {
	cout << "||==============================================||" << endl;
	cout << "               电商交易平台商家菜单				   " << endl;
	cout << "               0 -	打印菜单                        " << endl;
	cout << "               1 -	购买商品  					   " << endl;
	cout << "               2 -	修改账户密码					   " << endl;
	cout << "               3 -	余额查询 					   " << endl;
	cout << "               4 -	余额充值 					   " << endl;
	cout << "               5 -	展示我的商品信息				   " << endl;
	cout << "               6 -	展示所有商品信息				   " << endl;
	cout << "               7 -	搜索商品信息				       " << endl;
	cout << "               8 -	添加商品					       " << endl;	//seller
	//cout << "               9 -	删除商品					       " << endl;	//seller
	cout << "               9 -	商品信息修改				       " << endl;	//seller
	cout << "              10 -	管理购物车					   " << endl;
	cout << "              11 -	查看购物车					   " << endl;
	cout << "              12 -	生成订单					       " << endl;
	cout << "              13 -	网上支付					       " << endl;
	cout << "              14 -	退出						       " << endl;
	cout << "||==============================================||" << endl;
}
bool Trade::userSignIn() {
	cout << "请输入您的账号：" << endl;
	string inuptAccount;
	cin >> inuptAccount;
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
		string password = inputPassword(1);
		if (info.back() == password) {
			cout << "登录成功" << endl;
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
			return true;
		}
		else {
			cout << "密码错误，请重新登录" << endl;
			file.close();
		}
	}
	else {
		cout << "账号不存在，请您检查账号输入是否正确" << endl;
	}
	return false;
}
bool Trade::userSignUp() {
	cout << "请输入您想注册的账号:" << endl;
	string inputAccount;
	cin >> inputAccount;
	ifstream file;
	file.open("./用户/" + inputAccount + ".txt");
	if (file) {
		cout << "账号已存在，请换个账号重新注册" << endl;
		file.close();
	}
	else {
		ofstream ofs;
		ofs.open("./用户/" + inputAccount + ".txt", ofstream::out);
		if (ofs) {
			ofs << "Account: " << inputAccount << endl;
			string password1, password2, kind;
			while (true) {
				password1 = inputPassword(1);
				password2 = inputPassword(2);
				if (password1 == password2) {
					break;
				}
				else {
					cout << "密码不一致，请重新输入" << endl;
				}
			}
			ofs << "Password: " << password1 << endl;
			ofs << "Balance: 0" << endl;
			cout << "请选择您想注册的账号类型:" << endl;
			cout << "0 - 消费者" << endl;
			cout << "1 - 商家" << endl;
			cin >> kind;
			ofs << "AccountKind: " << kind << endl;
			cout << "注册成功" << endl;
			ofs.close();
			return true;
		}
		else {
			cout << "注册失败" << endl;
		}
	}
	return false;
}
void Trade::showAllCommodity() {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "商品序号" << setw(14) << "商品名称" << setw(14) << "所属帐户"
		<< setw(14) << "商品种类" << setw(14) << "商品价格" << setw(14) << "商品库存" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;
	int num = 1;
	for (const auto& pcom : commodities) {
		cout << setiosflags(ios::left) << setw(14) << num++ << setw(14) << pcom->getName() << setw(14) << pcom->getAccount()
			<< setw(14) << pcom->getKind() << setw(14) << pcom->getValue() << setw(14) << pcom->getStock()
			<< endl;
	}
	cout << "------------------------------------------------------------------------------------" << endl;
}
void Trade::searchCommoddity() {
	cout << "请输入搜索关键词" << endl;
	string t;
	cin >> t;
	bool exist = false;
	cout << "搜索结果如下：" << endl;
	int num = 1;
	cout << "----------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "商品序号" << setw(14) << "商品种类" << setw(14) << "所属帐户"
		<< setw(14) << "商品种类" << setw(14) << "商品价格" << setw(14) << "商品库存" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	for (const auto& pcom : commodities) {
		string s = pcom->getName();
		if (KMPcompare(s, t)) {
			exist = true;
			cout << setiosflags(ios::left) << setw(14) << num++ << setw(14) << pcom->getName() << setw(14) << pcom->getAccount()
				<< setw(14) << pcom->getKind() << setw(14) << pcom->getValue() << setw(14) << pcom->getStock()
				<< endl;
		}
	}
	if (!exist)	cout << "无搜索结果" << endl;
	cout << "----------------------------------------------------------------------" << endl;
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

void Trade::addCommodity() {
	if (user->getUserKind() == BUYER) {
		cout << "当前登陆账户类型为消费者，无权添加商品" << endl;
		return;
	}
	vector<string> info;
	string n, a, k, v, s;
	cout << "请输入你所添加商品的名称:" << endl;
	cin >> n;
	info.push_back(n);
	/* 添加所属账号 */
	a = user->getAccount();
	info.push_back(a);
	cout << "请输入你所添加商品的种类:" << endl;
	cout << "book or clothes or food" << endl;
	cin >> k;
	info.push_back(k);
	cout << "请输入你所添加商品的价格" << endl;
	cin >> v;
	info.push_back(v);
	cout << "请输入你所添加商品的数量" << endl;
	cin >> s;
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
	cout << "添加成功" << endl;
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
void Trade::changeCommodityInfo() {
	string k = user->changeCommodityInfo();
	if (k != "*") {
		updateCommodityFile("./商品/" + k + ".txt", k);
	} 
}

/* 题目二新加功能 */
void Trade::manageCart() {
	cout << "请选择你想要进行的操作" << endl;
	int way;
	cout << "1 - 添加商品至购物车   2 - 删除购物车中商品" << endl;
	cin >> way;
	switch (way) {
	case 1:
		addComToCart();
		break;
	case 2:
		subComToCart();
		break;
	default:
		cout << "错误选项，修改失败" << endl;
		break;
	}
}
void Trade::makeOrders() {
	Cart& cart = user->cart;
	if (cart.items.size() == 0) {
		cout << "购物车为空，生成订单失败" << endl;
		return;
	}
	/* 打印购物车内容 */
	cart.showCart();
	vector<int> nums;
	cout << "请输入想要结算的商品序号加入生成订单(输入不符合规范序号结束加入)" << endl;
	int num;
	set<int> set;
	cin >> num;
	while (num > 0 && num <= cart.items.size()) {
		if (!set.count(num)) {
			set.insert(num);
		}
		cin >> num;
	}

	if (set.size() == 0) {
		cout << "无输入商品，生成订单失败" << endl;
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

	cout << "生成订单成功如下：" << endl;
	cout << "--------------------------------" << endl;
	int x = 1;
	for (Item item : order.items) {
		cout << x++ << " " << item.pcom->getName() << " × " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
		/* 生成订单改变内存中的商品数量，不更新文件夹 */
		order.totalMoney += item.pcom->getPrice(item.nums);
		item.pcom->changeStock(-item.nums);
	}
	cout << "总计金额: " << order.totalMoney << "元" << endl;
	cout << "--------------------------------" << endl;

	cart.orders.push_back(order);
}
void Trade::onlinePayment() {
	Cart& cart = user->cart;
	if (cart.orders.size() == 0) {
		cout << "没有订单,支付失败" << endl;
		return;
	}

	cart.showOrders();
	cout << "请选择您想结算的订单序号" << endl;
	int seq;
	cin >> seq;
	if (seq <= 0 || seq > cart.orders.size()) {
		cout << "无此订单，支付失败" << endl;
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
		cout << "您的余额不足,支付失败" << endl;
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

		/* 如果卖家买了自己的产品，重新更新账号 */
		if (seller.getAccount() == user->getAccount()) {
			delete user;
			user = nullptr;
			/* 订单不能减少 */
			user = new Seller(seller);
			auto it = tempOrders.begin();
			for (int i = 0; i < tempOrders.size(); ++i) {
				user->cart.orders.push_back(*it);
				++it;
			}
		}
	}

	/* 支付成功删除此订单 */
	cout << "支付成功" << endl;
}

/* 释放掉list中new出来的元素,并清空list */
Trade::~Trade() {
	for (list<Commodity*>::iterator it = commodities.begin(); it != commodities.end();) {
		delete *it;
		commodities.erase(it++);
	}
	if (user != nullptr) {
		delete user;
		user = nullptr;
	}
}

void Trade::addComToCart() {
	showAllCommodity();
	Cart& cart = user->cart;
	while (true) {
		cout << "请输入你想加入购物车商品的序号和数量(输入序号不合法，例如小于最小序号或大于最大序号结束添加)" << endl;
		int num, cnt;
		cin >> num;
		cin >> cnt;
		if (num <= 0 || num > commodities.size()) {
			cout << "输入序号不合法，已退出添加商品" << endl;
			break;
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
			cout << "添加成功" << endl;
		}
		else {
			cout << "添加失败，请查看商品数量是否规范" << endl;
		}
	}
	cout << "购物车添加商品结束" << endl;
}
void Trade::subComToCart() {
	Cart& cart = user->cart;
	cout << "请选择你想删除的方法" << endl;
	cout << "1 - 直接删除指定商品    2 - 删除指定商品的拟购买数量" << endl;
	int way;
	cin >> way;
	cart.showCart();
	if (way == 1) {
		while (true) {
			if (cart.items.size() == 0) {
				cout << "购物车已空，自动退出删除" << endl;
			}
			cout << "请输入你想直接删除购物车中商品的序号(输入序号不合法将退出删除)" << endl;
			int num;
			cin >> num;
			if (num <= 0 || num > cart.items.size()) {
				cout << "输入序号不合法，已退出删除" << endl;
				break;
			}
			list<Item>::iterator it = cart.items.begin();
			for (; it != cart.items.end() && num > 1; ++it)		--num;
			if (num == 1 && it != cart.items.end()) {
				cart.items.erase(it);
				cout << "删除成功" << endl;
				user->updateUserFile();
			}
			else {
				cout << "删除失败，请查看输入序号是否符合规范" << endl;
			}
		}
	}
	else if (way == 2) {
		while (true) {
			if (cart.items.size() == 0) {
				cout << "购物车已空，自动退出删除" << endl;
			}
			cout << "请输入你想删除的在购物车中的商品序号以及数量(输入序号不合法将退出删除)" << endl;
			int num, cnt;
			cin >> num;
			cin >> cnt;
			if (num <= 0 || num > cart.items.size()) {
				cout << "输入序号不合法，已退出删除" << endl;
				break;
			}
			list<Item>::iterator it = cart.items.begin();
			for (; it != cart.items.end() && num > 1; ++it)		--num;
			if (num == 1 && it != cart.items.end() && cnt <= (*it).nums && cnt > 0) {
				(*it).nums -= cnt;
				if ((*it).nums == 0) {
					cart.items.erase(it);
				}
				user->updateUserFile();
				cout << "删除成功" << endl;
			}
			else {
				cout << "删除失败，请查看输入数量是否符合规范" << endl;
			}
		}
	}
	else {
		cout << "无此选项，删除失败" << endl;
	}
	cout << "购物车删除商品结束" << endl;
}