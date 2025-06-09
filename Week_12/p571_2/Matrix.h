#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

// Matrix: 게임 맵을 2차원 숫자 배열로 관리
class Matrix {
    int rows, cols; // 맵의 행, 열 크기
    int** mat;      // 2차원 배열 (아이템: 1, 빈칸: 0)

public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
        if (rows <= 0 || cols <= 0) return;
        mat = new int*[rows];
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols]();
    }
    ~Matrix() {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }
    int& elem(int x, int y) { return mat[x][y]; }
    int Rows() { return rows; }
    int Cols() { return cols; }
    int** Data() { return mat; }
    void print(const char *str = "Mat") {
        cout << str << " " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];
            cout << "\n";
        }
    }
    void setRand(int val = 100) {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = rand() % val;
        }
    }
};