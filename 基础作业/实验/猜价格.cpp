#include<iostream>
#include<random>
#include<ctime>
using namespace std;

int main(void) {
    static default_random_engine e((unsigned)time(0));
    static uniform_int_distribution<int> u(1, 1000);
    int price = 0, num = 0;
    cout << "�����������ļ۸�(1-1000)" << endl;
    bool first = true;
    while (true) {
        cin >> num;
        if (num > 1000 || num < 1 || cin.fail()) {
            if (cin.fail()) {
                cin.clear();
                cin.sync();
                cin.ignore(10000, '\n');
            }
            cout << "������Ч��������������Ч����1-1000���ڵ�����:" << endl;
        }
        else {
            if (first) {
                first = false;
                for (int i = 0; i < num; i++)    price = u(e);
                //cout << "�����Ϊ��" << price << endl;
            }
            if (num > price) {
                cout << "��Ŷ���¸��ˣ�����һ���" << endl;
            }
            else if (num < price) {
                cout << "��Ŷ���µ��ˣ�����һ���" << endl;
            }
            else {
                cout << "��ϲ��¶���!!" << endl;
                break;
            }
        }
    }
    return 0;
}