#include "trade.h"
bool isSignIn;

int getNum() {
	int num;
	cin >> num;
	while (true) {
		if (cin.fail())		//输入数据超过int_max
		{
			cin.clear();	//清除std::cin的错误状态
			cin.sync();		//清空输入缓冲区
			cin.ignore(10000, '\n');
			cout << "输入错误" << endl;
			continue;
		}
		else {
			return num;
		}
	}
	return 0;
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
	cout << "              13 -	查看订单					       " << endl;
	cout << "              14 -	网上支付						   " << endl;
	cout << "              15 -	退出						       " << endl;
	cout << "||==============================================||" << endl;
}
void Trade::userSignIn(char* buf, int& offset) {
	char account[16] = {};
	char password[16] = {};
	cout << "请输入想要登录的账号：" << endl;
	cin >> account;
	cout << "请输入账号密码" << endl;
	cin >> password;
	memcpy(buf + offset, account, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, password, sizeof(char) * 16);
	offset += sizeof(char) * 16;
}
void Trade::userSignUp(char* buf, int& offset) {
	char account[16] = {};
	char password[16] = {};
	char kind;
	cout << "请输入想要注册的账号：" << endl;
	cin >> account;
	cout << "请输入注册账号的密码" << endl;
	cin >> password;
	cout << "请选择想要注册的账户类型：" << endl;
	cout << "0 - 消费者        1 - 商家" << endl;
	cin >> kind;
	memcpy(buf + offset, account, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, password, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, &kind, sizeof(char));
	offset += sizeof(char);
}
void Trade::showCommodity(char buf[], int type) {
	int* pID = new int;
	memcpy(pID, &(buf[4]), sizeof(int));
	int num = ntohl(*pID);
	delete pID;
	pID = nullptr;
	if (num == 0) {
		cout << "无商品" << endl;
		return;
	}
	if (type == 0) {
		cout << "全部商品如下:" << endl;
	}
	else if (type == 1) {
		cout << "搜索商品如下:" << endl;
	}
	else {
		cout << "您的商品如下" << endl;
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "商品序号" << setw(14) << "商品名称" << setw(14) << "所属帐户"
		<< setw(14) << "商品种类" << setw(14) << "商品价格" << setw(14) << "商品库存" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;
	int x = 1;
	int index = 8;
	for (int i = 0; i < num; ++i) {
		char name[16] = {};
		char account[16] = {};
		char kind[16] = {};
		char value[8] = {};
		char stock[8] = {};
		memcpy(name, &(buf[index]), sizeof(char) * 16);
		index += 16;
		memcpy(account, &(buf[index]), sizeof(char) * 16);
		index += 16;
		memcpy(kind, &(buf[index]), sizeof(char) * 16);
		index += 16;
		memcpy(value, &(buf[index]), sizeof(char) * 8);
		index += 8;
		memcpy(stock, &(buf[index]), sizeof(char) * 8);
		index += 8;
		cout << setiosflags(ios::left) << setw(14) << x++ << setw(14) << name << setw(14) << account
			<< setw(14) << kind << setw(14) << value << setw(14) << stock << endl;
	}
	cout << "------------------------------------------------------------------------------------" << endl;
}
void Trade::searchCommoddity(char* buf, int& offset) {
	char name[16] = {};
	cout << "请输入想要搜索的名称" << endl;
	cin >> name;
	memcpy(buf + offset, name, sizeof(char) * 16);
	offset += sizeof(char) * 16;
}
void Trade::buyCommodity(char* buf, int& offset) {
	cout << "请输入您想要购买商品的序号：" << endl;
	int seq = getNum();
	cout << "请输入您购买该商品的数量：" << endl;
	int num = getNum();
	int _seq = htonl(seq);
	int _num = htonl(num);
	memcpy(buf + offset, &_seq, sizeof(int));
	offset += sizeof(int);
	memcpy(buf + offset, &_num, sizeof(int));
	offset += sizeof(int);
}
void Trade::changePassword(char* buf, int& offset) {
	char pre[16] = {};
	char now[16] = {};
	cout << "请输入当前密码：" << endl;
	cin >> pre;
	cout << "请输入想要修改的密码：" << endl;
	cin >> now;
	memcpy(buf + offset, pre, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, now, sizeof(char) * 16);
	offset += sizeof(char) * 16;
}
void Trade::rechargeMoney(char* buf, int& offset) {
	cout << "请输入您想要充值的金额:" << endl;
	int money = getNum();
	while (money <= 0) {
		cout << "充值金额不能小于等于0,请重新输入" << endl;
		money = getNum();
	}
	int _money = htonl(money);
	memcpy(buf + offset, &_money, sizeof(int));
	offset += sizeof(int);
}
void Trade::addCommodity(char* buf, int& offset) {
	char name[16] = {};
	char kind[16] = {};
	char value[8] = {};
	char stock[8] = {};
	cout << "请输入添加商品的名称:" << endl;
	cin >> name;
	cout << "请输入添加商品的种类(book, clothes, food):" << endl;
	cin >> kind;
	cout << "请输入添加商品的价格" << endl;
	cin >> value;
	cout << "请输入添加商品的数量" << endl;
	cin >> stock;
	memcpy(buf + offset, name, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, kind, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, value, sizeof(char) * 8);
	offset += sizeof(char) * 8;
	memcpy(buf + offset, stock, sizeof(char) * 8);
	offset += sizeof(char) * 8;
}
void Trade::changeCommodityInfo(char* buf, int& offset) {
	cout << "请选择商品信息修改的种类:" << endl;
	cout << "1 - 价格管理   2 - 剩余量管理  3 - 名称管理  4 - 折扣类型管理" << endl;
	int way = getNum();
	while (way < 1 || way > 4) {
		cout << "无此选项，请重新选择" << endl;
		way = getNum();
	}
	int _way = htonl(way);
	memcpy(buf + offset, &_way, sizeof(int));
	offset += sizeof(int);

	if (way == 4) {
		char kind[16] = {};
		cout << "请输入要打折扣的种类(clothes kind book):" << endl;
		cin >> kind;
		memcpy(buf + offset, kind, sizeof(char) * 16);
		offset += sizeof(char) * 16;
	}
	else {
		cout << "请输入要改变商品的序号:" << endl;
		int seq = getNum();
		int _seq = htonl(seq);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);
	}

	switch (way) {
	case 1: {
		cout << "请输入想要增加或减少多少价格" << endl;
		int num;
		num = getNum();
		int _num = htonl(num);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
		  break;
	case 2: {
		cout << "请输入想要增加和减少多少数量" << endl;
		int num;
		num = getNum();
		int _num = htonl(num);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
		  break;
	case 3: {
		cout << "请输入想要修改的名称" << endl;
		char name[16] = {};
		cin >> name;
		memcpy(buf + offset, name, sizeof(char) * 16);
		offset += sizeof(char) * 16;
	}
		  break;
	case 4: {
		cout << "请输入想要设置的折扣(1 - 9)" << endl;
		int num;
		num = getNum();
		while (num < 1 || num > 9) {
			cout << "折扣范围不对，请重新输入" << endl;
			num = getNum();
		}
		int _num = htonl(num);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
		  break;
	default:
		break;
	}
}
void Trade::manageCart(char* buf, int& offset) {
	cout << "请选择您想对购物车进行的操作：" << endl;
	cout << "1 - 添加商品到购物车    2 - 删除购物车中商品" << endl;
	int way = getNum();
	while (way < 1 || way > 2) {
		cout << "无此选项，请重新选择" << endl;
		way = getNum();
	}

	int way_ = htonl(way);
	memcpy(buf + offset, &way_, sizeof(int));
	offset += sizeof(int);

	if (way == 1) {
		cout << "请输入想要添加到购物车的商品序号" << endl;
		int seq = getNum();
		cout << "请输入想要添加该该商品的数量" << endl;
		int num = getNum();
		int _seq = htonl(seq);
		int _num = htonl(num);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
	else {
		cout << "请选择哪种删除方式:" << endl;
		cout << "1 - 直接删除    2 - 删除数量" << endl;

		int _way = getNum();
		while (_way < 1 || _way > 2) {
			cout << "无此选项，请重新输入" << endl;
			_way = getNum();
		}
		int _way_ = htonl(_way);
		memcpy(buf + offset, &_way_, sizeof(int));
		offset += sizeof(int);

		cout << "请输入删除商品的序号" << endl;
		int seq = getNum();
		int _seq = htonl(seq);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);

		if (_way == 2) {
			cout << "请选择删除的商品数量" << endl;
			int num = getNum();
			int _num = htonl(num);
			memcpy(buf + offset, &_num, sizeof(int));
			offset += sizeof(int);
		}
	}
}
void Trade::makeOrders(char* buf, int& offset) {
	cout << "请输入加入当前订单的购物车中商品序号(输入-1结束，不能输入相同的序号)" << endl;
	int seq = getNum();
	set<int> set;
	int num = 0;
	offset += sizeof(int);
	while (seq != -1) {
		if (!set.count(seq)) {
			++num;
			int _seq = htonl(seq);
			memcpy(buf + offset, &_seq, sizeof(int));
			offset += sizeof(int);
			set.insert(seq);
		}
		seq = getNum();
	}

	int _num = htonl(num);
	memcpy(buf + 4, &_num, sizeof(int));
}
void Trade::onlinePayment(char* buf, int& offset) {
	cout << "请输入想要支付的订单号" << endl;
	int num = getNum();
	int _num = htonl(num);
	memcpy(buf + offset, &_num, sizeof(int));
	offset += sizeof(int);
}
void Trade::getResult(char buf[]) {
	char s[50] = {};
	memcpy(s, &(buf[4]), 50);
	if (!strcmp(s, "登录成功!") && !isSignIn) {
		printUserInterface();
		isSignIn = true;
	}
	cout << s << endl;
}
void Trade::showCart(char buf[]) {
	int* pID = new int;
	memcpy(pID, &(buf[4]), sizeof(int));
	int num = ntohl(*pID);
	delete pID;
	pID = nullptr;

	if (num == 0) {
		cout << "  您当前购物车为空" << endl;
		return;
	}

	int x = 8;
	cout << "购物车内容如下：" << endl;
	cout << "--------------------------" << endl;
	for (int i = 0; i < num; ++i) {
		char s[50] = {};
		memcpy(s, &(buf[x]), sizeof(char) * 50);
		x += sizeof(char) * 50;
		cout << i + 1 << "    " << s << endl;
	}
	cout << "--------------------------" << endl;
}
void Trade::showOrders(char buf[]) {
	int* pID = new int;
	memcpy(pID, &(buf[4]), sizeof(int));
	int num = ntohl(*pID);

	if (num == 0) {
		cout << "  您当前无订单" << endl;
		return;
	}

	int x = 8;
	cout << "所有订单如下:" << endl;
	for (int i = 0; i < num; ++i) {
		memcpy(pID, &(buf[x]), sizeof(int));
		int cnt = ntohl(*pID);
		x += sizeof(int);
		cout << "订单" << i + 1 << ":" << endl;
		cout << "--------------------------" << endl;
		for (int j = 0; j <= cnt; ++j) {
			char s[50] = {};
			memcpy(s, &(buf[x]), sizeof(char) * 50);
			x += sizeof(char) * 50;
			cout << "    " << s << endl;
		}
		cout << "--------------------------" << endl;
	}

	delete pID;
	pID = nullptr;
}
bool Trade::getSendBuf(char* buf){
	cout << "请输入你的选项:" << endl;
	int choice;
	int offset = 0;
	/* 分为非登录状态和登录状态两种 */
	if (!isSignIn) {
		choice = getNum();
		while (choice < 0 || choice > 5) {
			cout << "输入无效，重新输入" << endl;
			choice = getNum();
		}

		int _choice = htonl(choice);
		memcpy(buf + offset, &_choice, sizeof(int));
		offset += sizeof(int);

		switch (choice) {
		case 0: {		//打印菜单，无需信息

		}
			  break;
		case 1: {		//登录，需要一个账号，一个密码
			userSignIn(buf, offset);
		}
			  break;
		case 2: {		//注册，需要携带一个账户，一个密码
			userSignUp(buf, offset);
		}
			  break;
		case 3: {		//展示，无需信息

		}
			  break;
		case 4: {		//搜索，需要携带一个字符串
			searchCommoddity(buf, offset);
		}
			  break;
		case 5: {		//退出的标志
			return false;
		}
			  break;
		default:
			break;
		}
	}
	else {
		choice = getNum();
		while (choice < 0 || choice > 15) {
			cout << "输入无效，重新输入" << endl;
			choice = getNum();
		}
		int _choice = htonl(choice);

		memcpy(buf + offset, &_choice, sizeof(int));
		offset += sizeof(int);

		switch (choice) {
		case 0: {				//打印菜单，无需信息

		}
			  break;
		case 1: {				//购买商品，需要携带序号
			buyCommodity(buf, offset);
		}
			  break;
		case 2: {				//修改账户密码，需要携带之前的密码，现在的密码
			changePassword(buf, offset);
		}
			  break;
		case 3: {				//余额查询，无需携带

		}
			  break;
		case 4: {				//余额充值，携带金额
			rechargeMoney(buf, offset);
		}
			  break;
		case 5: {				//展示我的商品信息，无携带

		}
			  break;
		case 6: {				//展示所有商品信息，无携带

		}
			  break;
		case 7: {				//搜索商品，携带字符串
			searchCommoddity(buf, offset);
		}
			  break;
		case 8: {				//添加商品,需要携带商品信息
			addCommodity(buf, offset);
		}
			  break;
		case 9: {				//商品信息修改，需要携带修改种类等信息
			changeCommodityInfo(buf, offset);
		}
			  break;
		case 10: {				//管理购物车，需要携带种类等信息
			manageCart(buf, offset);
		}
			   break;
		case 11: {				//查看购物车,无需携带信息

		}
			   break;
		case 12: {				//生成订单，需要携带购物车中的商品序号
			makeOrders(buf, offset);
		}
			   break;
		case 13: {				//查看订单以及订单号，无需携带	

		}
			   break;
		case 14: {				//网上支付,需要携带订单序号
			onlinePayment(buf, offset);
		}
			   break;
		case 15: {
			return false;
		}
			   break;
		default:
			break;
		}
	}
	return true;
}
bool Trade::solveRecvBuf(char recvbuf[]) {

	int* pID = new int;
	memcpy(pID, recvbuf, sizeof(int));
	int choice = ntohl(*pID);
	delete pID;
	pID = nullptr;
	int n = sizeof(char) * strlen(recvbuf);

	if (!isSignIn) {
		switch (choice) {
		case 0:
			printInitialInterface();
			break;
		case 1:
			getResult(recvbuf);
			break;
		case 2:
			getResult(recvbuf);
			break;
		case 3:
			showCommodity(recvbuf, 0);
			break;
		case 4:
			showCommodity(recvbuf, 1);
			break;
		default:
			break;
		}
	}
	else {
		switch (choice) {
		case 0:
			printUserInterface();
			break;
		case 1:
			getResult(recvbuf);
			break;
		case 2:
			getResult(recvbuf);
			break;
		case 3:
			getResult(recvbuf);
			break;
		case 4:
			getResult(recvbuf);
			break;
		case 5:
			showCommodity(recvbuf, 2);
			break;
		case 6:
			showCommodity(recvbuf, 0);
			break;
		case 7:
			showCommodity(recvbuf, 1);
			break;
		case 8:
			getResult(recvbuf);
			break;
		case 9:
			getResult(recvbuf);
			break;
		case 10:
			getResult(recvbuf);
			break;
		case 11:
			showCart(recvbuf);
			break;
		case 12:
			getResult(recvbuf);
			break;
		case 13:
			showOrders(recvbuf);
			break;
		case 14:
			getResult(recvbuf);
			break;
		default:
			break;
		}
	}

	return true;
}