#include<iostream>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h>
#include <iomanip>
#include <set>
//ws2_32.lib��
#pragma comment(lib,"ws2_32.lib")
//��������4996
#pragma warning(disable : 4996)
using namespace std;
extern int getNum();	//��ȷ������һ�����֣��Բ�����������б�����
extern bool isSignIn;	//�Ƿ��¼�ر�־

class Trade {
public:
	bool getSendBuf(char* buf);										    //���췢������
	bool solveRecvBuf(char recvbuf[]);									//�����õ��Ļش�
	void printInitialInterface();										//��ӡδ��¼����
	void printUserInterface();											//��ӡ��¼����
	void getResult(char buf[]);											//�õ��ظ���Ϣ
	void buyCommodity(char* buf, int& offset);							//���򵥸���Ʒ
	void changePassword(char* buf, int& offset);						//�ı�����
	void rechargeMoney(char* buf, int& offset);							//��ֵ
	void userSignIn(char* buf, int& offset);							//�û���¼
	void userSignUp(char* buf, int& offset);							//�û�ע��
	void addCommodity(char* buf, int& offset);							//�����Ʒ
	void showCommodity(char buf[], int type);							//��ʾ������Ʒ��Ϣ
	void searchCommoddity(char* buf,int& offset);						//������Ʒ
	void changeCommodityInfo(char* buf, int& offset);					//�޸���Ʒ��Ϣ
	void manageCart(char* buf, int& offset);							//�����ﳵ
	void showCart(char buf[]);											//�鿴���ﳵ
	void makeOrders(char* buf, int& offset);							//���ɶ���
	void showOrders(char buf[]);										//�鿴����
	void onlinePayment(char* buf, int& offset);							//����֧��
};

