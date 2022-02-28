#include "trade.h"
#include<Windows.h>

int main(void) {
	Trade myTrade;
	myTrade.printInitialInterface();
	bool exit = false;
	int choose = -1;
	while (true) {
		Sleep(500);
		cout << "������˵�ѡ��" << endl;
		cin >> choose;
		if (cin.fail())//�������ݳ���int_max
		{
			cin.clear(); //���std::cin�Ĵ���״̬
			cin.sync(); //������뻺����
			cin.ignore(10000, '\n');
			cout << "�������" << endl;
			continue;
		}
		if (myTrade.getUser() == nullptr) {
			switch (choose) {
			case 0: {
				myTrade.printInitialInterface();
			}
				  break;
			case 1: {
				myTrade.userSignIn();
				if (myTrade.getUser() != nullptr)	myTrade.printUserInterface();
			}
				  break;
			case 2: {
				myTrade.userSignUp();
			}
				  break;
			case 3: {
				myTrade.showAllCommodity();
			}
				  break;
			case 4: {
				myTrade.searchCommoddity();
			}
				  break;
			case 5: {
				exit = true;
			}
				  break;
			default: {
				cout << "�޴�ѡ�������ѡ��" << endl;
			}
				   break;
			}
		}
		else {
			switch (choose) {
			case 0: {
				myTrade.printUserInterface();
			}
				  break;
			case 1: {
				myTrade.buyCommodity();
			}
				  break;
			case 2: {
				myTrade.getUser()->changePassword();
			}
				  break;
			case 3: {
				string account = myTrade.getUser()->getAccount();
				int balance = myTrade.getUser()->getBalance();
				cout << "�˺�" << account << "����" << balance << "Ԫ" << endl;
			}
				  break;
			case 4: {
				int money;
				cout << "����������Ҫ��ֵ����Ԫ" << endl;
				cin >> money;
				if (myTrade.getUser()->recharge(money)) {
					cout << "��ֵ�ɹ�" << endl;
				}
				else {
					cout << "��ֵʧ��" << endl;
				}
			}
				  break;
			case 5: {
				if (myTrade.getUser()->getUserKind() == SELLER) {
					myTrade.getUser()->showMyCommodity();
				}
				else {
					cout << "������ң�����Ʒ" << endl;
				}
			}
				  break;
			case 6: {
				myTrade.showAllCommodity();
			}
				  break;
			case 7: {
				myTrade.searchCommoddity();
			}
				  break;
			case 8: {
				myTrade.addCommodity();
			}
				  break;
			case 9: {
				if (myTrade.getUser()->getUserKind() == SELLER) {
					myTrade.changeCommodityInfo();
				}
				else {
					cout << "������ң���Ȩ��" << endl;
				}
			}
				  break;
			case 10: {
				myTrade.manageCart();
			}
				   break;
			case 11: {
				myTrade.getUser()->cart.showCart();
			}
				   break;
			case 12: {
				myTrade.makeOrders();
			}
				   break;
			case 13: {
				myTrade.onlinePayment();
			}
				   break;
			case 14: {
				exit = true;
			}
				   break;
			default: {
				cout << "�޴�ѡ�������ѡ��" << endl;
			}
				   break;
			}
		}
		if (exit)	break;
		//system("CLS");
	}
	return 0;
}