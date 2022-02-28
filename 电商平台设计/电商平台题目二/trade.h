#include "user.h"

class Trade {
public:
	Trade();
	User* getUser();
	void printInitialInterface();	//��ӡδ��¼��ʼ����
	void printUserInterface();		//��ӡ��¼����
	void buyCommodity();			//���򵥸���Ʒ
    bool userSignIn();				//�û���¼
	bool userSignUp();				//�û�ע��
	void addCommodity();			//�����Ʒ
	void showAllCommodity();		//��ʾ������Ʒ��Ϣ
	void searchCommoddity();		//������Ʒ
	void changeCommodityInfo();		//�޸���Ʒ��Ϣ
	void manageCart();				//�����ﳵ
	void makeOrders();				//���ɶ���
	void onlinePayment();			//����֧��
	~Trade();
private:
	list<Commodity*> commodities;	//�洢��Ʒ
	User* user;						//�����û�
	string inputPassword(int type);	//����������Ļ����***********
	bool KMPcompare(string s, string t);	//KMP�㷨ʵ������
	void updateCommodityFile(const string& filename, const string& kind);	//���¶�Ӧ��Ʒ���ļ�
	void addComToCart();					//���빺�ﳵ��Ʒ
	void subComToCart();					//ɾ�����ﳵ��Ʒ
};
