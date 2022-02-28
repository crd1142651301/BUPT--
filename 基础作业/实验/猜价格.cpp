#include<iostream>
#include<random>
#include<ctime>
using namespace std;

int main(void) {
    static default_random_engine e((unsigned)time(0));
    static uniform_int_distribution<int> u(1, 1000);
    int price = 0, num = 0;
    cout << "请输入你猜想的价格(1-1000)" << endl;
    bool first = true;
    while (true) {
        cin >> num;
        if (num > 1000 || num < 1 || cin.fail()) {
            if (cin.fail()) {
                cin.clear();
                cin.sync();
                cin.ignore(10000, '\n');
            }
            cout << "输入无效！！！请输入有效的在1-1000以内的数字:" << endl;
        }
        else {
            if (first) {
                first = false;
                for (int i = 0; i < num; i++)    price = u(e);
                //cout << "随机数为：" << price << endl;
            }
            if (num > price) {
                cout << "啊哦，猜高了，换低一点吧" << endl;
            }
            else if (num < price) {
                cout << "啊哦，猜低了，换高一点吧" << endl;
            }
            else {
                cout << "恭喜你猜对了!!" << endl;
                break;
            }
        }
    }
    return 0;
}