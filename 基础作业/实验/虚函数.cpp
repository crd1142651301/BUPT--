#include<iostream>
#include<string>
using namespace std;

class Shape {
public:
    Shape() {
        cout << "Shape�Ĺ��캯��" << endl;
    }
    virtual double getArea() const {
        return 0;
    }
    ~Shape() {
        cout << "Shape����������" << endl;
    }
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
    double getArea() const {
        return x * y;
    }
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
    double getArea() const {
        return pi * r * r;
    }
    int getR() const { return r; }
    ~Circle() {
        cout << "Circle����������" << endl;
    }
private:
    double pi = 3.1415926;
    int r;
};

class Square : public Rectangle {
public:
    Square(int a) : Rectangle(a, a) {
        cout << "Square�Ĺ��캯��" << endl;
    }
    ~Square() {
        cout << "Square����������" << endl;
    }
};

int main(void) {
    int x, y;
    cout << "������ľ���ĳ��Ϳ�:" << endl;
    cin >> x >> y;
    Rectangle rec(x, y);
    cout << "�þ�������Ϊ: " << rec.getArea() << endl;
    int r;
    cout << "������Բ�İ뾶" << endl;
    cin >> r;
    Circle c(r);
    cout << "��Բ�����Ϊ: " << c.getArea() << endl;
    cout << "�����������εı߳�" << endl;
    cin >> x;
    Square squ(x);
    cout << "�������ε����Ϊ: " << squ.getArea() << endl;
    return 0;
}