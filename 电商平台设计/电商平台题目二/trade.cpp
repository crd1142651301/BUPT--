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
		user = nullptr;
	}
	else {
		cout << "��Ʒ�ļ��򿪳���" << endl;
	}
}
User* Trade::getUser() {
	return user;
}
void Trade::buyCommodity() {
	showAllCommodity();
	cout << "��ѡ�����빺����Ʒ������Լ���������" << endl;
	int num, cnt;
	cin >> num;
	cin >> cnt;
	if (num <= 0 || num > commodities.size()) {
		cout << "����ʧ�ܣ����벻���Ϲ涨��Χ������" << endl;
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

		/* ��Һ�������ͬһ���ˣ����˻��������ı� */
		if (user->getAccount() == (*it)->getAccount()) {
			cout << "����ɹ�" << endl;
			return;
		}
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
		cout << "����ɹ�" << endl;
	}
	else {
		cout << "����ʧ�ܣ����벻���Ϲ涨��Χ������" << endl;
	}
}
void Trade::printInitialInterface() {
	cout << "||==============================================||" << endl;
	cout << "               ���̽���ƽ̨��ʼ�˵�				   " << endl;
	cout << "               0 -	��ӡ�˵�                        " << endl;
	cout << "               1 -	�û���¼					       " << endl;
	cout << "               2 -	�û�ע��					       " << endl;
	cout << "               3 -	չʾ��Ʒ��Ϣ				       " << endl;
	cout << "               4 -	������Ʒ��Ϣ				       " << endl;
	cout << "               5 -	�˳�						       " << endl;
	cout << "||==============================================||" << endl;
}
void Trade::printUserInterface() {
	cout << "||==============================================||" << endl;
	cout << "               ���̽���ƽ̨�̼Ҳ˵�				   " << endl;
	cout << "               0 -	��ӡ�˵�                        " << endl;
	cout << "               1 -	������Ʒ  					   " << endl;
	cout << "               2 -	�޸��˻�����					   " << endl;
	cout << "               3 -	����ѯ 					   " << endl;
	cout << "               4 -	����ֵ 					   " << endl;
	cout << "               5 -	չʾ�ҵ���Ʒ��Ϣ				   " << endl;
	cout << "               6 -	չʾ������Ʒ��Ϣ				   " << endl;
	cout << "               7 -	������Ʒ��Ϣ				       " << endl;
	cout << "               8 -	�����Ʒ					       " << endl;	//seller
	//cout << "               9 -	ɾ����Ʒ					       " << endl;	//seller
	cout << "               9 -	��Ʒ��Ϣ�޸�				       " << endl;	//seller
	cout << "              10 -	�����ﳵ					   " << endl;
	cout << "              11 -	�鿴���ﳵ					   " << endl;
	cout << "              12 -	���ɶ���					       " << endl;
	cout << "              13 -	����֧��					       " << endl;
	cout << "              14 -	�˳�						       " << endl;
	cout << "||==============================================||" << endl;
}
bool Trade::userSignIn() {
	cout << "�����������˺ţ�" << endl;
	string inuptAccount;
	cin >> inuptAccount;
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
		string password = inputPassword(1);
		if (info.back() == password) {
			cout << "��¼�ɹ�" << endl;
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
			return true;
		}
		else {
			cout << "������������µ�¼" << endl;
			file.close();
		}
	}
	else {
		cout << "�˺Ų����ڣ���������˺������Ƿ���ȷ" << endl;
	}
	return false;
}
bool Trade::userSignUp() {
	cout << "����������ע����˺�:" << endl;
	string inputAccount;
	cin >> inputAccount;
	ifstream file;
	file.open("./�û�/" + inputAccount + ".txt");
	if (file) {
		cout << "�˺��Ѵ��ڣ��뻻���˺�����ע��" << endl;
		file.close();
	}
	else {
		ofstream ofs;
		ofs.open("./�û�/" + inputAccount + ".txt", ofstream::out);
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
					cout << "���벻һ�£�����������" << endl;
				}
			}
			ofs << "Password: " << password1 << endl;
			ofs << "Balance: 0" << endl;
			cout << "��ѡ������ע����˺�����:" << endl;
			cout << "0 - ������" << endl;
			cout << "1 - �̼�" << endl;
			cin >> kind;
			ofs << "AccountKind: " << kind << endl;
			cout << "ע��ɹ�" << endl;
			ofs.close();
			return true;
		}
		else {
			cout << "ע��ʧ��" << endl;
		}
	}
	return false;
}
void Trade::showAllCommodity() {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "��Ʒ���" << setw(14) << "��Ʒ����" << setw(14) << "�����ʻ�"
		<< setw(14) << "��Ʒ����" << setw(14) << "��Ʒ�۸�" << setw(14) << "��Ʒ���" << endl;
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
	cout << "�����������ؼ���" << endl;
	string t;
	cin >> t;
	bool exist = false;
	cout << "����������£�" << endl;
	int num = 1;
	cout << "----------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "��Ʒ���" << setw(14) << "��Ʒ����" << setw(14) << "�����ʻ�"
		<< setw(14) << "��Ʒ����" << setw(14) << "��Ʒ�۸�" << setw(14) << "��Ʒ���" << endl;
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
	if (!exist)	cout << "���������" << endl;
	cout << "----------------------------------------------------------------------" << endl;
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

void Trade::addCommodity() {
	if (user->getUserKind() == BUYER) {
		cout << "��ǰ��½�˻�����Ϊ�����ߣ���Ȩ�����Ʒ" << endl;
		return;
	}
	vector<string> info;
	string n, a, k, v, s;
	cout << "���������������Ʒ������:" << endl;
	cin >> n;
	info.push_back(n);
	/* ��������˺� */
	a = user->getAccount();
	info.push_back(a);
	cout << "���������������Ʒ������:" << endl;
	cout << "book or clothes or food" << endl;
	cin >> k;
	info.push_back(k);
	cout << "���������������Ʒ�ļ۸�" << endl;
	cin >> v;
	info.push_back(v);
	cout << "���������������Ʒ������" << endl;
	cin >> s;
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
	cout << "��ӳɹ�" << endl;
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
		updateCommodityFile("./��Ʒ/" + k + ".txt", k);
	} 
}

/* ��Ŀ���¼ӹ��� */
void Trade::manageCart() {
	cout << "��ѡ������Ҫ���еĲ���" << endl;
	int way;
	cout << "1 - �����Ʒ�����ﳵ   2 - ɾ�����ﳵ����Ʒ" << endl;
	cin >> way;
	switch (way) {
	case 1:
		addComToCart();
		break;
	case 2:
		subComToCart();
		break;
	default:
		cout << "����ѡ��޸�ʧ��" << endl;
		break;
	}
}
void Trade::makeOrders() {
	Cart& cart = user->cart;
	if (cart.items.size() == 0) {
		cout << "���ﳵΪ�գ����ɶ���ʧ��" << endl;
		return;
	}
	/* ��ӡ���ﳵ���� */
	cart.showCart();
	vector<int> nums;
	cout << "��������Ҫ�������Ʒ��ż������ɶ���(���벻���Ϲ淶��Ž�������)" << endl;
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
		cout << "��������Ʒ�����ɶ���ʧ��" << endl;
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

	cout << "���ɶ����ɹ����£�" << endl;
	cout << "--------------------------------" << endl;
	int x = 1;
	for (Item item : order.items) {
		cout << x++ << " " << item.pcom->getName() << " �� " << item.nums << " = " << item.pcom->getPrice(item.nums) << endl;
		/* ���ɶ����ı��ڴ��е���Ʒ�������������ļ��� */
		order.totalMoney += item.pcom->getPrice(item.nums);
		item.pcom->changeStock(-item.nums);
	}
	cout << "�ܼƽ��: " << order.totalMoney << "Ԫ" << endl;
	cout << "--------------------------------" << endl;

	cart.orders.push_back(order);
}
void Trade::onlinePayment() {
	Cart& cart = user->cart;
	if (cart.orders.size() == 0) {
		cout << "û�ж���,֧��ʧ��" << endl;
		return;
	}

	cart.showOrders();
	cout << "��ѡ���������Ķ������" << endl;
	int seq;
	cin >> seq;
	if (seq <= 0 || seq > cart.orders.size()) {
		cout << "�޴˶�����֧��ʧ��" << endl;
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
		cout << "��������,֧��ʧ��" << endl;
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

		/* ������������Լ��Ĳ�Ʒ�����¸����˺� */
		if (seller.getAccount() == user->getAccount()) {
			delete user;
			user = nullptr;
			/* �������ܼ��� */
			user = new Seller(seller);
			auto it = tempOrders.begin();
			for (int i = 0; i < tempOrders.size(); ++i) {
				user->cart.orders.push_back(*it);
				++it;
			}
		}
	}

	/* ֧���ɹ�ɾ���˶��� */
	cout << "֧���ɹ�" << endl;
}

/* �ͷŵ�list��new������Ԫ��,�����list */
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
		cout << "������������빺�ﳵ��Ʒ����ź�����(������Ų��Ϸ�������С����С��Ż���������Ž������)" << endl;
		int num, cnt;
		cin >> num;
		cin >> cnt;
		if (num <= 0 || num > commodities.size()) {
			cout << "������Ų��Ϸ������˳������Ʒ" << endl;
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
			cout << "��ӳɹ�" << endl;
		}
		else {
			cout << "���ʧ�ܣ���鿴��Ʒ�����Ƿ�淶" << endl;
		}
	}
	cout << "���ﳵ�����Ʒ����" << endl;
}
void Trade::subComToCart() {
	Cart& cart = user->cart;
	cout << "��ѡ������ɾ���ķ���" << endl;
	cout << "1 - ֱ��ɾ��ָ����Ʒ    2 - ɾ��ָ����Ʒ���⹺������" << endl;
	int way;
	cin >> way;
	cart.showCart();
	if (way == 1) {
		while (true) {
			if (cart.items.size() == 0) {
				cout << "���ﳵ�ѿգ��Զ��˳�ɾ��" << endl;
			}
			cout << "����������ֱ��ɾ�����ﳵ����Ʒ�����(������Ų��Ϸ����˳�ɾ��)" << endl;
			int num;
			cin >> num;
			if (num <= 0 || num > cart.items.size()) {
				cout << "������Ų��Ϸ������˳�ɾ��" << endl;
				break;
			}
			list<Item>::iterator it = cart.items.begin();
			for (; it != cart.items.end() && num > 1; ++it)		--num;
			if (num == 1 && it != cart.items.end()) {
				cart.items.erase(it);
				cout << "ɾ���ɹ�" << endl;
				user->updateUserFile();
			}
			else {
				cout << "ɾ��ʧ�ܣ���鿴��������Ƿ���Ϲ淶" << endl;
			}
		}
	}
	else if (way == 2) {
		while (true) {
			if (cart.items.size() == 0) {
				cout << "���ﳵ�ѿգ��Զ��˳�ɾ��" << endl;
			}
			cout << "����������ɾ�����ڹ��ﳵ�е���Ʒ����Լ�����(������Ų��Ϸ����˳�ɾ��)" << endl;
			int num, cnt;
			cin >> num;
			cin >> cnt;
			if (num <= 0 || num > cart.items.size()) {
				cout << "������Ų��Ϸ������˳�ɾ��" << endl;
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
				cout << "ɾ���ɹ�" << endl;
			}
			else {
				cout << "ɾ��ʧ�ܣ���鿴���������Ƿ���Ϲ淶" << endl;
			}
		}
	}
	else {
		cout << "�޴�ѡ�ɾ��ʧ��" << endl;
	}
	cout << "���ﳵɾ����Ʒ����" << endl;
}