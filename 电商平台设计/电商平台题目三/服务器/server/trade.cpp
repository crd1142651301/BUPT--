#include "trade.h"
#include<set>

Trade::Trade() {
	ifstream file1, file2, file3;
	file1.open("./��Ʒ/book.txt", ifstream::in);
	file2.open("./��Ʒ/clothes.txt", ifstream::in);
	file3.open("./��Ʒ/food.txt", ifstream::in);
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
		cout << "��Ʒ�ļ��򿪳���" << endl;
	}
}
void Trade::userSignIn(char* sendbuf,User*& user, char recvbuf[], int& offset) {
	char _account[16] = {};
	char _password[16] = {};
	memcpy(_account, &(recvbuf[4]), sizeof(char) * 16);
	memcpy(_password, &(recvbuf[20]), sizeof(char) * 16);
	string inuptAccount(_account);
	ifstream file;
	file.open("./�û�/" + inuptAccount + ".txt");
	if (file) {
		string line, temp1, temp2, temp3, temp4;
		vector<string> info;
		int i = 0;
		/* �����˺ź����� */
		while (getline(file, line) && i < 2) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
			++i;
		}
		string password(_password);
		if (info.back() == password) {
			/* ����֮ǰ�����ˣ��ٶ���һ�У�������� */
			istringstream record1(line);
			record1 >> temp1;
			record1 >> temp2;
			info.push_back(temp2);
			/* ������������ */
			getline(file, line);
			istringstream record2(line);
			record2 >> temp1;
			record2 >> temp2;
			info.push_back(temp2);
			/* ���빺�ﳵ */
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
			if (string_to_int(info[3]) == BUYER) {		//���
				Buyer buyer(info, commodities);
				user = new Buyer(buyer);
			}
			else {
				Seller seller(info, commodities);
				user = new Seller(seller);
			}
			char s[50] = "��¼�ɹ�!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return; 
		}
		else {
			char s[50] = "������������µ�¼!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			file.close();
		}
	}
	else {
		char s[50] = "�˺Ų����ڣ���������˺������Ƿ���ȷ!";
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
	file.open("./�û�/" + inputAccount + ".txt");
	if (file) {
		char s[50] = "�˺��Ѵ��ڣ��뻻���˺�����ע��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		file.close();
	}
	else {
		ofstream ofs;
		ofs.open("./�û�/" + inputAccount + ".txt", ofstream::out);
		if (ofs) {
			ofs << "Account: " << inputAccount << endl;
			ofs << "Password: " << password << endl;
			ofs << "Balance: 0" << endl;
			ofs << "AccountKind: " << kind << endl;
			ofs.close();
			char s[50] = "ע��ɹ�!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return true;
		}
		else {
			char s[50] = "ע��ʧ��!";
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
//KMP�㷨ʵ�������ַ���ƥ��
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
	//�����ڱ�
	s.insert(s.begin(), ' ');
	p.insert(p.begin(), ' ');
	vector<int> next(m + 1);
	//Ԥ����next����
	for (int i = 2, j = 0; i <= m; i++) {
		while (j and p[i] != p[j + 1]) j = next[j];
		if (p[i] == p[j + 1]) j++;
		next[i] = j;
	}
	//ƥ�����
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
		cout << "����������(��ĸ���ֻ��ַ�)��" << endl;
	}
	else {
		cout << "������ȷ������(��ĸ���ֻ��ַ�)��" << endl;
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


/* ��¼�� */
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
		char s[50] = "����ʧ�ܣ����벻���Ϲ涨��Χ������!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	list<Commodity*>::iterator it = commodities.begin();
	for (; it != commodities.end() && num > 1; ++it)	--num;
	int total = (*it)->getPrice(cnt);
	if (cnt > 0 && cnt <= (*it)->getStock() && total <= user->getBalance()) {
		/* ֧���ɹ���������Ʒ�ļ��� */
		(*it)->changeStock(-cnt);
		string kind = (*it)->getKind();
		updateCommodityFile("./��Ʒ/" + kind + ".txt", kind);

		/* ��Һ�������ͬһ���ˣ����˻��������ı� 
		if (user->getAccount() == (*it)->getAccount()) {
			char s[50] = "����ɹ�!";
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			return;
		}*/

		/* ��ȥ��һ��Ѳ���������ļ� */
		user->consume(total);

		/* ������˻�һ��������Ϊ�̼��˻���֧���ɹ��ı��������̼��ļ��� */
		string account = (*it)->getAccount();
		ifstream file("./�û�/" + account + ".txt", ifstream::in);
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
		char s[50] = "����ɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
	else {
		char s[50] = "����ʧ�ܣ����벻���Ϲ涨��Χ������!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
}
void Trade::addCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	if (user->getUserKind() == BUYER) {
		char s[50] = "��ǰ��½�˻�����Ϊ�����ߣ���Ȩ�����Ʒ!";
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
		updateCommodityFile("./��Ʒ/food.txt", "food");
	}
	else if (k == CLOTHES) {
		Clothes clothes(info);
		pcom = new Clothes(clothes);
		commodities.push_back(pcom);
		user->addCommodity(pcom);
		updateCommodityFile("./��Ʒ/clothes.txt", "clothes");
	}
	else if (k == BOOK) {
		Book book(info);
		pcom = new Book(book);
		commodities.push_back(pcom);
		user->addCommodity(pcom);
		updateCommodityFile("./��Ʒ/book.txt", "book");
	}
	user->addCommodity(pcom);
	char _s[50] = "��ӳɹ�!";
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
		updateCommodityFile("./��Ʒ/" + k + ".txt", k);
	}
}



/* ��Ŀ���¼ӹ��� */
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
		cout << "����ѡ��޸�ʧ��" << endl;
		break;
	}
}
void Trade::makeOrders(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	if (cart.items.size() == 0) {
		char s[50] = "���ﳵΪ�գ����ɶ���ʧ��!";
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
		char s[50] = "������Ʒ����,���ɶ���ʧ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	/* �����¶��������� */
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
	/* ����ɾ�����ﳵ����ļ� */
	user->updateUserFile();

	for (Item item : order.items) {
		//cout << x++ << " " << item.pcom->getName() << " �� " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
		/* ���ɶ����ı��ڴ��е���Ʒ�������������ļ��� */
		order.totalMoney += item.pcom->getPrice(item.nums);
		item.pcom->changeStock(-item.nums);
	}
	//cout << "�ܼƽ��: " << order.totalMoney << "Ԫ" << endl;
	//cout << "--------------------------------" << endl;

	cart.orders.push_back(order);

	char s[50] = "���ɶ����ɹ�!";
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
}
void Trade::onlinePayment(char* sendbuf, User*& user, char recvbuf[], int& offset) {
	Cart& cart = user->cart;
	if (cart.orders.size() == 0) {
		char s[50] = "����ǰ�޶���,֧��ʧ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	int* pID = new int;
	memcpy(pID, &(recvbuf[4]), sizeof(int));
	int seq = ntohl(*pID);
	delete pID;
	pID = nullptr;
	
	if (seq <= 0 || seq > cart.orders.size()) {
		char s[50] = "�޴˶�����֧��ʧ��!";
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
		char s[50] = "��������,֧��ʧ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	/* ��ȥ��ǰ����˻����ѵķ��ò������ļ� */
	user->consume(totalMoney);

	for (Item item : items) {

		/* ֧���ɹ���������Ʒ�ļ��� */
		string kind = item.pcom->getKind();
		updateCommodityFile("./��Ʒ/" + kind + ".txt", kind);

		/* ������˻�һ��������Ϊ�̼��˻���֧���ɹ��ı��������̼��ļ��� */
		string account = item.pcom->getAccount();
		ifstream file("./�û�/" + account + ".txt", ifstream::in);
		vector<string> info;
		string line, temp1, temp2;
		while (getline(file, line)) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
		}
		file.close();

		/* ���������˻��������ֵ��Ӧ�Ľ����µ��ļ� */
		Seller seller(info, commodities);
		seller.recharge(item.pcom->getPrice(item.nums));

		/* ������������Լ��Ĳ�Ʒ�����¸����˺� 
		if (seller.getAccount() == user->getAccount()) {
			delete user;
			user = nullptr;
			/* �������ܼ��� 
			user = new Seller(seller);
			auto it = tempOrders.begin();
			for (int i = 0; i < tempOrders.size(); ++i) {
				user->cart.orders.push_back(*it);
				++it;
			}
		}*/
	}

	/* ֧���ɹ�ɾ���˶��� */
	char s[50] = "֧���ɹ�!";
	memcpy(sendbuf + offset, s, sizeof(char) * 50);
}

/* �ͷŵ�list��new������Ԫ��,�����list */
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
		char s[50] = "������Ų��Ϸ������˳������Ʒ!";
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
		if (_it == cart.items.end()) {	//���ﳵ���޴���Ʒ
			Item item;
			item.nums = cnt;
			item.name = (*it)->getName();
			item.acc = (*it)->getAccount();
			item.kind = (*it)->getKind();
			item.pcom = *it;
			cart.items.push_back(item);
		}
		else {	//���ﳵ���Ѿ����ڴ���Ʒ��ֻ�����Ŀ
			(*_it).nums += cnt;
		}
		user->updateUserFile();
		char s[50] = "��ӳɹ�!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
	}
	else {
		char s[50] = "���ʧ�ܣ���鿴��Ʒ�����Ƿ�淶!";
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
		char s[50] = "���ﳵΪ�գ��޷�ɾ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}
	if (num <= 0 || num > cart.items.size()) {
		char s[50] = "������Ų��Ϸ������˳�ɾ��!";
		memcpy(sendbuf + offset, s, sizeof(char) * 50);
		return;
	}

	list<Item>::iterator it = cart.items.begin();
	for (; it != cart.items.end() && num > 1; ++it)		--num;

	if (way == 1) {
		if (num == 1 && it != cart.items.end()) {
			cart.items.erase(it);
			user->updateUserFile();
			char s[50] = "ɾ���ɹ�!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
		else {
			char s[50] = "ɾ��ʧ�ܣ���鿴���������Ƿ���Ϲ淶!";
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
			char s[50] = "ɾ���ɹ�!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
		else {
			char s[50] = "ɾ��ʧ�ܣ���鿴���������Ƿ���Ϲ淶!";
			memcpy(sendbuf, s, sizeof(char) * 50);
		}
	}
	else {
		char s[50] = "�޴�ɾ�����࣬ɾ��ʧ��!";
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
	file.open("./�û�/" + _account + ".txt");
	if (file) {
		string line, temp1, temp2, temp3, temp4;
		vector<string> info;
		int i = 0;
		/* �����˺ź����� */
		while (getline(file, line) && i < 2) {
			istringstream record(line);
			record >> temp1;
			record >> temp2;
			info.push_back(temp2);
			++i;
		}
		string password(_password);
		if (info.back() == password) {
			/* ����֮ǰ�����ˣ��ٶ���һ�У�������� */
			istringstream record1(line);
			record1 >> temp1;
			record1 >> temp2;
			info.push_back(temp2);
			/* ������������ */
			getline(file, line);
			istringstream record2(line);
			record2 >> temp1;
			record2 >> temp2;
			info.push_back(temp2);
			/* ���빺�ﳵ */
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
			if (string_to_int(info[3]) == BUYER) {		//���
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
			//cout << "�˺Ÿ��³ɹ�" << endl;
			return true;
		}
	}
	else {
		cout << "�˺Ÿ���ʧ��" << endl;
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

	if (!user) {			//δ��¼
		switch (choice) {
		case 0: 			//��ӡ�˵�������������
			break;
		case 1: {			//��¼����ȡ�˺�����,����Ƿ��¼�ɹ�
			userSignIn(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 2: {			//ע�ᣬ��ȡ�˺����룬����Ƿ�ע��ɹ�
			userSignUp(sendbuf, recvbuf, offset);
		}
			  break;
		case 3: {			//���������Ʒ��Ϣ
			showAllCommodity(sendbuf, offset);
		}
			  break;
		case 4: {			//��ȡ�����ַ��������������Ʒ���
			searchCommoddity(sendbuf, offset, recvbuf);
		}
			  break;
		default:
			break;
		}
	}
	else {					//�ѵ�¼
		switch (choice) {
		case 0:				//��ӡ�˵�������������
			break;
		case 1: {			//������Ʒ�������Ʒ�ظ���Ϣ�����
			buyCommodity(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 2: {			//�޸��˻����룬����Ƿ��޸ĳɹ�
			user->changePassword(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 3: {			//����ѯ������˻����
			int balance = user->getBalance();
			string t = "��ǰ�������Ϊ" + to_string(balance) + "Ԫ!";
			char s[50] = {};
			t.copy(s, t.size());
			memcpy(sendbuf + offset, s, sizeof(char) * 50);
			offset += sizeof(char) * 50;
		}
			  break;
		case 4: {			//����ֵ������ֵ���
			int* pID = new int;
			memcpy(pID, &(recvbuf[4]), sizeof(int));
			int money = ntohl(*pID);
			delete pID;
			pID = nullptr;
			bool success = user->recharge(money);
			if (success) {
				char s[50] = "��ֵ�ɹ�!";
				memcpy(sendbuf + offset, s, sizeof(char) * 50);
				offset += sizeof(char) * 50;
			}
			else {
				char s[50] = "��ֵʧ��!";
				memcpy(sendbuf + offset, s, sizeof(char) * 50);
				offset += sizeof(char) * 50;
			}
		}
			  break;
		case 5: {			//չʾ�ҵ���Ʒ��Ϣ������ҵ���Ʒ
			user->showMyCommodity(sendbuf, offset);
		}
			  break;
		case 6: {			//չʾ������Ʒ��Ϣ�����������Ʒ
			showAllCommodity(sendbuf, offset);
		}
			  break;
		case 7: {			//������Ʒ��Ϣ������������
			searchCommoddity(sendbuf, offset, recvbuf);
		}
			  break;
		case 8: {			//�����Ʒ����������Ʒ�Ľ��
			addCommodity(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 9: {			//��Ʒ��Ϣ�޸ģ������Ϣ�޸Ľ��
			changeCommodityInfo(sendbuf, user, recvbuf, offset);
		}
			  break;
		case 10: {			//���ﳵ������������
			manageCart(sendbuf, user, recvbuf, offset);
		}
			   break;
		case 11: {			//�鿴���ﳵ����乺�ﳵ����
			user->cart.showCart(sendbuf, offset);
		}
			   break;
		case 12: {			//���ɶ�����������ɽ��
			makeOrders(sendbuf, user, recvbuf, offset);
		}
			   break;
		case 13: {			//�鿴��������䶩������
			user->cart.showOrders(sendbuf, offset);
		}
			   break;
		case 14: {			//����֧�������֧�����
			onlinePayment(sendbuf, user, recvbuf, offset);
		}
			   break;
		default:
			break;
		}
	}
}

