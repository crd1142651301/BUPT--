#include "trade.h"
bool isSignIn;

int getNum() {
	int num;
	cin >> num;
	while (true) {
		if (cin.fail())		//�������ݳ���int_max
		{
			cin.clear();	//���std::cin�Ĵ���״̬
			cin.sync();		//������뻺����
			cin.ignore(10000, '\n');
			cout << "�������" << endl;
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
	cout << "              13 -	�鿴����					       " << endl;
	cout << "              14 -	����֧��						   " << endl;
	cout << "              15 -	�˳�						       " << endl;
	cout << "||==============================================||" << endl;
}
void Trade::userSignIn(char* buf, int& offset) {
	char account[16] = {};
	char password[16] = {};
	cout << "��������Ҫ��¼���˺ţ�" << endl;
	cin >> account;
	cout << "�������˺�����" << endl;
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
	cout << "��������Ҫע����˺ţ�" << endl;
	cin >> account;
	cout << "������ע���˺ŵ�����" << endl;
	cin >> password;
	cout << "��ѡ����Ҫע����˻����ͣ�" << endl;
	cout << "0 - ������        1 - �̼�" << endl;
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
		cout << "����Ʒ" << endl;
		return;
	}
	if (type == 0) {
		cout << "ȫ����Ʒ����:" << endl;
	}
	else if (type == 1) {
		cout << "������Ʒ����:" << endl;
	}
	else {
		cout << "������Ʒ����" << endl;
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "��Ʒ���" << setw(14) << "��Ʒ����" << setw(14) << "�����ʻ�"
		<< setw(14) << "��Ʒ����" << setw(14) << "��Ʒ�۸�" << setw(14) << "��Ʒ���" << endl;
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
	cout << "��������Ҫ����������" << endl;
	cin >> name;
	memcpy(buf + offset, name, sizeof(char) * 16);
	offset += sizeof(char) * 16;
}
void Trade::buyCommodity(char* buf, int& offset) {
	cout << "����������Ҫ������Ʒ����ţ�" << endl;
	int seq = getNum();
	cout << "���������������Ʒ��������" << endl;
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
	cout << "�����뵱ǰ���룺" << endl;
	cin >> pre;
	cout << "��������Ҫ�޸ĵ����룺" << endl;
	cin >> now;
	memcpy(buf + offset, pre, sizeof(char) * 16);
	offset += sizeof(char) * 16;
	memcpy(buf + offset, now, sizeof(char) * 16);
	offset += sizeof(char) * 16;
}
void Trade::rechargeMoney(char* buf, int& offset) {
	cout << "����������Ҫ��ֵ�Ľ��:" << endl;
	int money = getNum();
	while (money <= 0) {
		cout << "��ֵ����С�ڵ���0,����������" << endl;
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
	cout << "�����������Ʒ������:" << endl;
	cin >> name;
	cout << "�����������Ʒ������(book, clothes, food):" << endl;
	cin >> kind;
	cout << "�����������Ʒ�ļ۸�" << endl;
	cin >> value;
	cout << "�����������Ʒ������" << endl;
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
	cout << "��ѡ����Ʒ��Ϣ�޸ĵ�����:" << endl;
	cout << "1 - �۸����   2 - ʣ��������  3 - ���ƹ���  4 - �ۿ����͹���" << endl;
	int way = getNum();
	while (way < 1 || way > 4) {
		cout << "�޴�ѡ�������ѡ��" << endl;
		way = getNum();
	}
	int _way = htonl(way);
	memcpy(buf + offset, &_way, sizeof(int));
	offset += sizeof(int);

	if (way == 4) {
		char kind[16] = {};
		cout << "������Ҫ���ۿ۵�����(clothes kind book):" << endl;
		cin >> kind;
		memcpy(buf + offset, kind, sizeof(char) * 16);
		offset += sizeof(char) * 16;
	}
	else {
		cout << "������Ҫ�ı���Ʒ�����:" << endl;
		int seq = getNum();
		int _seq = htonl(seq);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);
	}

	switch (way) {
	case 1: {
		cout << "��������Ҫ���ӻ���ٶ��ټ۸�" << endl;
		int num;
		num = getNum();
		int _num = htonl(num);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
		  break;
	case 2: {
		cout << "��������Ҫ���Ӻͼ��ٶ�������" << endl;
		int num;
		num = getNum();
		int _num = htonl(num);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
		  break;
	case 3: {
		cout << "��������Ҫ�޸ĵ�����" << endl;
		char name[16] = {};
		cin >> name;
		memcpy(buf + offset, name, sizeof(char) * 16);
		offset += sizeof(char) * 16;
	}
		  break;
	case 4: {
		cout << "��������Ҫ���õ��ۿ�(1 - 9)" << endl;
		int num;
		num = getNum();
		while (num < 1 || num > 9) {
			cout << "�ۿ۷�Χ���ԣ�����������" << endl;
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
	cout << "��ѡ������Թ��ﳵ���еĲ�����" << endl;
	cout << "1 - �����Ʒ�����ﳵ    2 - ɾ�����ﳵ����Ʒ" << endl;
	int way = getNum();
	while (way < 1 || way > 2) {
		cout << "�޴�ѡ�������ѡ��" << endl;
		way = getNum();
	}

	int way_ = htonl(way);
	memcpy(buf + offset, &way_, sizeof(int));
	offset += sizeof(int);

	if (way == 1) {
		cout << "��������Ҫ��ӵ����ﳵ����Ʒ���" << endl;
		int seq = getNum();
		cout << "��������Ҫ��Ӹø���Ʒ������" << endl;
		int num = getNum();
		int _seq = htonl(seq);
		int _num = htonl(num);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);
		memcpy(buf + offset, &_num, sizeof(int));
		offset += sizeof(int);
	}
	else {
		cout << "��ѡ������ɾ����ʽ:" << endl;
		cout << "1 - ֱ��ɾ��    2 - ɾ������" << endl;

		int _way = getNum();
		while (_way < 1 || _way > 2) {
			cout << "�޴�ѡ�����������" << endl;
			_way = getNum();
		}
		int _way_ = htonl(_way);
		memcpy(buf + offset, &_way_, sizeof(int));
		offset += sizeof(int);

		cout << "������ɾ����Ʒ�����" << endl;
		int seq = getNum();
		int _seq = htonl(seq);
		memcpy(buf + offset, &_seq, sizeof(int));
		offset += sizeof(int);

		if (_way == 2) {
			cout << "��ѡ��ɾ������Ʒ����" << endl;
			int num = getNum();
			int _num = htonl(num);
			memcpy(buf + offset, &_num, sizeof(int));
			offset += sizeof(int);
		}
	}
}
void Trade::makeOrders(char* buf, int& offset) {
	cout << "��������뵱ǰ�����Ĺ��ﳵ����Ʒ���(����-1����������������ͬ�����)" << endl;
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
	cout << "��������Ҫ֧���Ķ�����" << endl;
	int num = getNum();
	int _num = htonl(num);
	memcpy(buf + offset, &_num, sizeof(int));
	offset += sizeof(int);
}
void Trade::getResult(char buf[]) {
	char s[50] = {};
	memcpy(s, &(buf[4]), 50);
	if (!strcmp(s, "��¼�ɹ�!") && !isSignIn) {
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
		cout << "  ����ǰ���ﳵΪ��" << endl;
		return;
	}

	int x = 8;
	cout << "���ﳵ�������£�" << endl;
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
		cout << "  ����ǰ�޶���" << endl;
		return;
	}

	int x = 8;
	cout << "���ж�������:" << endl;
	for (int i = 0; i < num; ++i) {
		memcpy(pID, &(buf[x]), sizeof(int));
		int cnt = ntohl(*pID);
		x += sizeof(int);
		cout << "����" << i + 1 << ":" << endl;
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
	cout << "���������ѡ��:" << endl;
	int choice;
	int offset = 0;
	/* ��Ϊ�ǵ�¼״̬�͵�¼״̬���� */
	if (!isSignIn) {
		choice = getNum();
		while (choice < 0 || choice > 5) {
			cout << "������Ч����������" << endl;
			choice = getNum();
		}

		int _choice = htonl(choice);
		memcpy(buf + offset, &_choice, sizeof(int));
		offset += sizeof(int);

		switch (choice) {
		case 0: {		//��ӡ�˵���������Ϣ

		}
			  break;
		case 1: {		//��¼����Ҫһ���˺ţ�һ������
			userSignIn(buf, offset);
		}
			  break;
		case 2: {		//ע�ᣬ��ҪЯ��һ���˻���һ������
			userSignUp(buf, offset);
		}
			  break;
		case 3: {		//չʾ��������Ϣ

		}
			  break;
		case 4: {		//��������ҪЯ��һ���ַ���
			searchCommoddity(buf, offset);
		}
			  break;
		case 5: {		//�˳��ı�־
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
			cout << "������Ч����������" << endl;
			choice = getNum();
		}
		int _choice = htonl(choice);

		memcpy(buf + offset, &_choice, sizeof(int));
		offset += sizeof(int);

		switch (choice) {
		case 0: {				//��ӡ�˵���������Ϣ

		}
			  break;
		case 1: {				//������Ʒ����ҪЯ�����
			buyCommodity(buf, offset);
		}
			  break;
		case 2: {				//�޸��˻����룬��ҪЯ��֮ǰ�����룬���ڵ�����
			changePassword(buf, offset);
		}
			  break;
		case 3: {				//����ѯ������Я��

		}
			  break;
		case 4: {				//����ֵ��Я�����
			rechargeMoney(buf, offset);
		}
			  break;
		case 5: {				//չʾ�ҵ���Ʒ��Ϣ����Я��

		}
			  break;
		case 6: {				//չʾ������Ʒ��Ϣ����Я��

		}
			  break;
		case 7: {				//������Ʒ��Я���ַ���
			searchCommoddity(buf, offset);
		}
			  break;
		case 8: {				//�����Ʒ,��ҪЯ����Ʒ��Ϣ
			addCommodity(buf, offset);
		}
			  break;
		case 9: {				//��Ʒ��Ϣ�޸ģ���ҪЯ���޸��������Ϣ
			changeCommodityInfo(buf, offset);
		}
			  break;
		case 10: {				//�����ﳵ����ҪЯ���������Ϣ
			manageCart(buf, offset);
		}
			   break;
		case 11: {				//�鿴���ﳵ,����Я����Ϣ

		}
			   break;
		case 12: {				//���ɶ�������ҪЯ�����ﳵ�е���Ʒ���
			makeOrders(buf, offset);
		}
			   break;
		case 13: {				//�鿴�����Լ������ţ�����Я��	

		}
			   break;
		case 14: {				//����֧��,��ҪЯ���������
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