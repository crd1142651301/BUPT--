#include<iostream>
#include<string>
using namespace std;

class Shape {
public:
    Shape() {
        cout << "Shape的构造函数" << endl;
    }
    virtual double getArea() const {
        return 0;
    }
    ~Shape() {
        cout << "Shape的析构函数" << endl;
    }
};

class Rectangle : public Shape {
public:
    Rectangle(int a, int b) {
        cout << "Rectangle的构造函数" << endl;
        x = a;
        y = b;
    };
    int getX() const { return x; }
    int getY() const { return y; }
    double getArea() const {
        return x * y;
    }
    ~Rectangle() {
        cout << "Rectangle的析构函数" << endl;
    }
private:
    int x;
    int y;
};

class Circle : public Shape {
public:
    Circle(int a) {
        cout << "Circle的构造函数" << endl;
        r = a;
    }
    double getArea() const {
        return pi * r * r;
    }
    int getR() const { return r; }
    ~Circle() {
        cout << "Circle的析构函数" << endl;
    }
private:
    double pi = 3.1415926;
    int r;
};

class Square : public Rectangle {
public:
    Square(int a) : Rectangle(a, a) {
        cout << "Square的构造函数" << endl;
    }
    ~Square() {
        cout << "Square的析构函数" << endl;
    }
};

int main(void) {
    int x, y;
    cout << "请输入的矩阵的长和宽:" << endl;
    cin >> x >> y;
    Rectangle rec(x, y);
    cout << "该矩阵的面积为: " << rec.getArea() << endl;
    int r;
    cout << "请输入圆的半径" << endl;
    cin >> r;
    Circle c(r);
    cout << "该圆的面积为: " << c.getArea() << endl;
    cout << "请输入正方形的边长" << endl;
    cin >> x;
    Square squ(x);
    cout << "该正方形的面积为: " << squ.getArea() << endl;
    return 0;
}