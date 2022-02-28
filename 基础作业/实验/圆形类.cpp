#include<iostream>
#include<math.h>
using namespace std;

class Point {
public:
    Point() {
        cout << "执行Point类的无参数构造函数" << endl;
        x = 0;
        y = 0;
    }
    Point(int a, int b) {
        cout << "执行Point类的含参数构造函数" << endl;
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
        cout << "执行Point类的析构函数" << endl;
    }
private:
    int x, y;
};

class Circle {
public:
    Circle() {
        cout << "执行Circle类的无参构造函数" << endl;
        r = 0;
    }
    Circle(int a, int b, int c) : p(a, b) {
        cout << "执行Circle类的含参构造函数" << endl;
        r = c;
    }
    int getX() { return p.getX(); }
    int getY() { return p.getY(); }
    int getR() { return r; }
    ~Circle() {
        cout << "执行Circle类的析构函数" << endl;
    }
private:
    Point p;
    int r;
};

int main(void) {
    int x, y, r;
    cout << "请输入第一个圆的圆心横纵坐标以及其半径：" << endl;
    cin >> x >> y >> r;
    Circle c1(x, y, r);
    cout << "请输入第二个圆的圆心横纵坐标以及其半径：" << endl;
    cin >> x >> y >> r;
    Circle c2(x, y, r);
    Point p;
    double d = p.getDistance(c1.getX(), c1.getY(), c2.getX(), c2.getY());
    if (d < c1.getR() + c2.getR()) {
        cout << "两圆相交" << endl;
    }
    else {
        cout << "两圆不相交" << endl;
    }
    return 0;
}