#include "trade.h"
#include<Windows.h>

int main(void) {
	Trade myTrade;
	myTrade.printInitialInterface();
	bool exit = false;
	int choose = -1;
	while (true) {
		Sleep(500);
		cout << "请输入菜单选项" << endl;
		cin >> choose;
		if (cin.fail())//输入数据超过int_max
		{
			cin.clear(); //清除std::cin的错误状态
			cin.sync(); //清空输入缓冲区
			cin.ignore(10000, '\n');
			cout << "输入错误" << endl;
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
				cout << "无此选项，请重新选择" << endl;
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
				cout << "账号" << account << "余额还有" << balance << "元" << endl;
			}
				  break;
			case 4: {
				int money;
				cout << "请输入你想要充值多少元" << endl;
				cin >> money;
				if (myTrade.getUser()->recharge(money)) {
					cout << "充值成功" << endl;
				}
				else {
					cout << "充值失败" << endl;
				}
			}
				  break;
			case 5: {
				if (myTrade.getUser()->getUserKind() == SELLER) {
					myTrade.getUser()->showMyCommodity();
				}
				else {
					cout << "您是买家，无商品" << endl;
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
					cout << "你是买家，无权限" << endl;
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
				cout << "无此选项，请重新选择" << endl;
			}
				   break;
			}
		}
		if (exit)	break;
		//system("CLS");
	}
	return 0;
}