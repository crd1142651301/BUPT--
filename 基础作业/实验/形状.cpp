#include<iostream>
#include<string>
using namespace std;
const double PI = 3.1415926;

class Shape {
public:
    Shape() {
        area = 0;
        cout << "Shape�Ĺ��캯��" << endl;
    }
    void getArea(int r) {
        area = PI * r * r;
    }
    void getArea(int x, int y) {
        area = x * y;
    }
    double getArea() {
        return area;
    }
    ~Shape() {
        cout << "Shape����������" << endl;
    }
private:
    double area;
};

class Rectangle : public Shape {
public:
    Rectangle(int a, int b) {
        cout << "Rectangle�Ĺ��캯��" << endl;
        x = a;
        y = b;
    };
    int getX() const { return x; }
    int getY() const { return y; }
    ~Rectangle() {
        cout << "Rectangle����������" << endl;
    }
private:
    int x;
    int y;
};

class Circle : public Shape {
public:
    Circle(int a) {
        cout << "Circle�Ĺ��캯��" << endl;
        r = a;
    }
    int getR() const { return r; };
    ~Circle() {
        cout << "Circle����������" << endl;
    }
private:
    int r;
};

class Square : public Rectangle {
public:
    Square(int a) : Rectangle(a, a) {
        cout << "Square�Ĺ��캯��" << endl;
    }
    ~Square() {
        cout << "Square�Ĺ��캯��" << endl;
    }
};

int main(void) {
    int x, y;
    cout << "������ľ���ĳ��Ϳ�:" << endl;
    cin >> x >> y;
    Rectangle rec(x, y);
    rec.getArea(rec.getX(), rec.getY());
    cout << "�þ�������Ϊ: " << rec.getArea() << endl;
    int r;
    cout << "������Բ�İ뾶" << endl;
    cin >> r;
    Circle c(r);
    c.getArea(c.getR());
    cout << "��Բ�����Ϊ: " << c.getArea() << endl;
    cout << "�����������εı߳�" << endl;
    cin >> x;
    Square squ(x);
    squ.getArea(squ.getX(), squ.getY());
    cout << "�������ε����Ϊ: " << squ.getArea() << endl;
    return 0;
}