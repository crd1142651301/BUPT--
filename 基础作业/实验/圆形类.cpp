#include<iostream>
#include<math.h>
using namespace std;

class Point {
public:
    Point() {
        cout << "ִ��Point����޲������캯��" << endl;
        x = 0;
        y = 0;
    }
    Point(int a, int b) {
        cout << "ִ��Point��ĺ��������캯��" << endl;
        x = a;
        y = b;
    }
    double getDistance(int x1, int y1, int x2, int y2) {
        int dx = x1 - x2;
        int dy = y1 - y2;
        return sqrt(dx * dx + dy * dy);
    }
    int getX() { return x; }
    int getY() { return y; }
    ~Point() {
        cout << "ִ��Point�����������" << endl;
    }
private:
    int x, y;
};

class Circle {
public:
    Circle() {
        cout << "ִ��Circle����޲ι��캯��" << endl;
        r = 0;
    }
    Circle(int a, int b, int c) : p(a, b) {
        cout << "ִ��Circle��ĺ��ι��캯��" << endl;
        r = c;
    }
    int getX() { return p.getX(); }
    int getY() { return p.getY(); }
    int getR() { return r; }
    ~Circle() {
        cout << "ִ��Circle�����������" << endl;
    }
private:
    Point p;
    int r;
};

int main(void) {
    int x, y, r;
    cout << "�������һ��Բ��Բ�ĺ��������Լ���뾶��" << endl;
    cin >> x >> y >> r;
    Circle c1(x, y, r);
    cout << "������ڶ���Բ��Բ�ĺ��������Լ���뾶��" << endl;
    cin >> x >> y >> r;
    Circle c2(x, y, r);
    Point p;
    double d = p.getDistance(c1.getX(), c1.getY(), c2.getX(), c2.getY());
    if (d < c1.getR() + c2.getR()) {
        cout << "��Բ�ཻ" << endl;
    }
    else {
        cout << "��Բ���ཻ" << endl;
    }
    return 0;
}