#include "user.h"


class Trade {
public:
	Trade();
	void handleBuf(char recvbuf[], char* sendbuf, User*& user);								//�����յ��İ�������Ҫ��Ӧ�İ�
	void buyCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset);				//���򵥸���Ʒ
	void userSignIn(char* sendbuf,User*& user, char recvbuf[], int& offset);				//�û���¼
	bool userSignUp(char* sendbuf, char recvbuf[], int& offset);							//�û�ע��
	void addCommodity(char* sendbuf, User*& user, char recvbuf[], int& offset);				//�����Ʒ
	void showAllCommodity(char* sendbuf, int& offset);										//��ʾ������Ʒ��Ϣ
	void searchCommoddity(char* sendbuf, int& offset, char recvbuf[]);						//������Ʒ
	void changeCommodityInfo(char* sendbuf, User*& user, char recvbuf[], int& offset);		//�޸���Ʒ��Ϣ
	void manageCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//�����ﳵ
	void makeOrders(char* sendbuf, User*& user, char recvbuf[], int& offset);				//���ɶ���
	void onlinePayment(char* sendbuf, User*& user, char recvbuf[], int& offset);			//����֧��
	bool updateMyData(User*& user);
	~Trade();
private:
	list<Commodity*> commodities;															//�����Ʒ
	string inputPassword(int type);															//����*****
	bool KMPcompare(string s, string t);													//KMPʵ������
	void updateCommodityFile(const string& filename, const string& kind);					//������Ʒ�ļ�
	void addComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//���빺�ﳵ��Ʒ
	void subComToCart(char* sendbuf, User*& user, char recvbuf[], int& offset);				//ɾ�����ﳵ��Ʒ
};
