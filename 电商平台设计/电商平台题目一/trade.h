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
	void changeCommodityInfo();
	~Trade();
private:
	list<Commodity*> commodities;
	User* user;
	string inputPassword(int type);
	bool KMPcompare(string s, string t);
	void updateCommodityFile(string filename, string kind);
};
