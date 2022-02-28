#include<iostream>
using namespace std;

class Matrix {
public:
    Matrix(int r, int c) {
        row = r;
        col = c;
        matrix = new int* [row];
        for (int i = 0; i < row; ++i) {
            matrix[i] = new int[col];
        }
    }
    int getRow() const {
        return row;
    }
    int getCol() const {
        return col;
    }
    int** getMatrix() const {
        return matrix;
    }
    Matrix(const Matrix& m) {
        row = m.getRow();
        col = m.getCol();
        matrix = new int* [row];
        for (int i = 0; i < row; i++) {
            matrix[i] = new int[col];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = m.matrix[i][j];
            }
        }
    }
    ~Matrix() {
        if (matrix != nullptr) {
            for (int i = 0; i < row; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = nullptr;
        }
    }
    void inputMatrix() {
        cout << "请输入一个" << row << "行" << col << "列" << "的矩阵" << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cin >> matrix[i][j];
            }
        }
    }
    void outputMatrix() {
        cout << "所得矩阵为:" << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void addMatrix(const Matrix& m1, const Matrix& m2) {
        if (m1.getRow() == m2.getRow() && m1.getCol() == m2.getCol() && row == m1.getRow() && col == m1.getCol()) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    this->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
                }
            }
        }
        else {
            cout << "相加矩阵不匹配" << endl;
        }
    }
    void subMatrix(const Matrix& m1, const Matrix& m2) {
        if (m1.getRow() == m2.getRow() && m1.getCol() == m2.getCol() && row == m1.getRow() && col == m1.getCol()) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    this->matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
                }
            }
        }
        else {
            cout << "相减矩阵不匹配" << endl;
        }
    }
    Matrix& operator=(const Matrix& m) {
        //通过比较地址是否相同来检查是否是自赋值
        if (this == &m) {
            return *this;
        }
        //释放矩阵中旧元素
        if (matrix != nullptr) {
            for (int i = 0; i < row; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = nullptr;
        }
        //新元素并且进行赋值
        matrix = new int* [row];
        for (int i = 0; i < row; i++) {
            matrix[i] = new int[col];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                this->matrix[i][j] = m.matrix[i][j];
            }
        }
        return *this;
    }
private:
    int** matrix;
    int row, col;//矩阵大小
};

int main(void) {
    int row, col;
    cout << "请依次输入矩阵的行数和列数:" << endl;
    cin >> row >> col;
    Matrix A1(row, col), A2(row, col), A3(row, col);
    cout << "请输入矩阵A1:" << endl;
    A1.inputMatrix();
    cout << "请输入矩阵A2:" << endl;
    A2.inputMatrix();
    A3.addMatrix(A1, A2);
    cout << "矩阵A3 = A1 + A2:" << endl;
    A3.outputMatrix();
    A3.subMatrix(A1, A2);
    cout << "矩阵A3 = A1 - A2:" << endl;
    A3.outputMatrix();
    //new分配得到的是一个指针
    Matrix* pA1 = new Matrix(A1);
    Matrix* pA2 = new Matrix(A2);
    Matrix* pA3 = new Matrix(A3);
    cout << "请输入矩阵pA1:" << endl;
    pA1->inputMatrix();
    cout << "请输入矩阵pA2:" << endl;
    pA2->inputMatrix();
    pA3->addMatrix(*pA1, *pA2);
    cout << "矩阵pA3 = pA1 + pA2:" << endl;
    pA3->outputMatrix();
    pA3->subMatrix(*pA1, *pA2);
    cout << "矩阵pA3 = pA1 - pA2:" << endl;
    pA3->outputMatrix();
    //释放动态分配的指针
    delete pA1;
    delete pA2;
    delete pA3;
    pA1 = nullptr;
    pA2 = nullptr;
    pA3 = nullptr;
    return 0;
}