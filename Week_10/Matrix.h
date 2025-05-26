#pragma once
#include <iostream>
#include <iomanip>

class Matrix {
    int rows, cols;
    int** mat;
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(nullptr) {
        mat = new int*[rows];
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols];
    }
    ~Matrix() {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }
    int& elem(int x, int y) { return mat[y][x]; }
    int Rows() { return rows; }
    int Cols() { return cols; }
    int** Data() { return mat; }
    void print(const char *str = "Mat") {
        std::cout << str << " " << rows << "x" << cols << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                std::cout << std::setw(4) << mat[i][j];
            std::cout << "\n";
        }
    }
    void setRand(int val = 100) {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = (rand() % val);
        }
    }
};