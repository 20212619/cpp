#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Point.h"
#define MAXLINES 100
using namespace std;

// Canvas: 게임 맵을 2차원 배열로 관리하고 화면에 출력
class Canvas {
    string grid[MAXLINES][MAXLINES]; // 맵의 각 칸에 문자열 저장
    int xMax, yMax;                 // 맵의 가로, 세로 크기

public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                grid[y][x] = ".";
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && x < xMax && y >= 0 && y < yMax)
            grid[y][x] = val;
    }
    void draw(Point p, string val) {
        if (p[0] >= 0 && p[0] < xMax && p[1] >= 0 && p[1] < yMax)
            grid[p[1]][p[0]] = val;
    }
    void clear(string val = ".") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                grid[y][x] = val;
    }
    void print(const char *title = "<My Canvas>") {
        system("clear");
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++)
                cout << grid[y][x] << " ";
            cout << endl;
        }
        cout << endl;
    }
};