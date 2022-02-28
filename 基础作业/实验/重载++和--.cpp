#include<iostream>
using namespace std;

class Point {
public:
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    int getX() const { return x; }
    int getY() const { return y; }
    ~Point() {}
    Point& operator=(Point p) {
        this->x = p.getX();
        this->y = p.getY();
        return *this;
    }
    Point& operator++() {//ǰ�������
        ++this->x;
        ++this->y;
        return *this;
    }
    Point& operator--() {
        --this->x;
        --this->y;
        return *this;
    }
    Point operator++(int) {//���������
        Point ret = *this;
        ++this->x;
        ++this->y;
        return ret;
    }
    Point operator--(int) {
        Point ret = *this;
        --this->x;
        --this->y;
        return ret;
    }
private:
    int x, y;
};

void printXY(const Point& tmp, const Point& p) {
    cout << "�������صĽ��: (" << tmp.getX() << ", " << tmp.getY() << ")" << endl;
    cout << "��ǰ�������: (" << p.getX() << ", " << p.getY() << ")" << endl;
}

int main(void) {
    int a, b;
    cout << "�������ʼ������" << endl;
    cin >> a >> b;
    Point p(a, b);
    Point tmp;
    cout << "++p�Ľ��" << endl;
    tmp = ++p;
    printXY(tmp, p);
    cout << "p++�Ľ��" << endl;
    tmp = p++;
    printXY(tmp, p);
    cout << "--p�Ľ��" << endl;
    tmp = --p;
    printXY(tmp, p);
    cout << "p--�Ľ��" << endl;
    tmp = p--;
    printXY(tmp, p);
    return 0;
}