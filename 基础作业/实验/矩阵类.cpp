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
        cout << "������һ��" << row << "��" << col << "��" << "�ľ���" << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cin >> matrix[i][j];
            }
        }
    }
    void outputMatrix() {
        cout << "���þ���Ϊ:" << endl;
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
            cout << "��Ӿ���ƥ��" << endl;
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
            cout << "�������ƥ��" << endl;
        }
    }
    Matrix& operator=(const Matrix& m) {
        //ͨ���Ƚϵ�ַ�Ƿ���ͬ������Ƿ����Ը�ֵ
        if (this == &m) {
            return *this;
        }
        //�ͷž����о�Ԫ��
        if (matrix != nullptr) {
            for (int i = 0; i < row; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = nullptr;
        }
        //��Ԫ�ز��ҽ��и�ֵ
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
    int row, col;//�����С
};

int main(void) {
    int row, col;
    cout << "������������������������:" << endl;
    cin >> row >> col;
    Matrix A1(row, col), A2(row, col), A3(row, col);
    cout << "���������A1:" << endl;
    A1.inputMatrix();
    cout << "���������A2:" << endl;
    A2.inputMatrix();
    A3.addMatrix(A1, A2);
    cout << "����A3 = A1 + A2:" << endl;
    A3.outputMatrix();
    A3.subMatrix(A1, A2);
    cout << "����A3 = A1 - A2:" << endl;
    A3.outputMatrix();
    //new����õ�����һ��ָ��
    Matrix* pA1 = new Matrix(A1);
    Matrix* pA2 = new Matrix(A2);
    Matrix* pA3 = new Matrix(A3);
    cout << "���������pA1:" << endl;
    pA1->inputMatrix();
    cout << "���������pA2:" << endl;
    pA2->inputMatrix();
    pA3->addMatrix(*pA1, *pA2);
    cout << "����pA3 = pA1 + pA2:" << endl;
    pA3->outputMatrix();
    pA3->subMatrix(*pA1, *pA2);
    cout << "����pA3 = pA1 - pA2:" << endl;
    pA3->outputMatrix();
    //�ͷŶ�̬�����ָ��
    delete pA1;
    delete pA2;
    delete pA3;
    pA1 = nullptr;
    pA2 = nullptr;
    pA3 = nullptr;
    return 0;
}