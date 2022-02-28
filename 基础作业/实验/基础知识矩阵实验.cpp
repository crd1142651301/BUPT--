#include<iostream>
using namespace std;
#define row 4
#define col 5
//new出一个矩阵并返回
int** newMatrix(int r, int c) {
    int** matrix = new int* [r];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}
void initMatrix(int** matrix) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> matrix[i][j];
        }
    }
}
void outputMatrix(int** const matrix) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}
void deleteMatrix(int** matrix) {
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
void addMatrixs(int** const matrix_1, int** const matrix_2, int** sumMatrix) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            sumMatrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }
}
void subMatrixs(int** const matrix_1, int** const matrix_2, int** subMatrix) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            subMatrix[i][j] = matrix_1[i][j] - matrix_2[i][j];
        }
    }
}
int main(void) {
    int** A1 = newMatrix(row, col);
    int** A2 = newMatrix(row, col);
    int** A3 = newMatrix(row, col);
    cout << "请输入矩阵A1：" << endl;
    initMatrix(A1);
    cout << "请输入矩阵A2：" << endl;
    initMatrix(A2);
    addMatrixs(A1, A2, A3);
    cout << "相加所得矩阵为：" << endl;
    outputMatrix(A3);
    subMatrixs(A1, A2, A3);
    cout << "相减所得矩阵为：" << endl;
    outputMatrix(A3);
    deleteMatrix(A1);
    deleteMatrix(A2);
    deleteMatrix(A3);
    return 0;
}