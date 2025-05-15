#pragma once
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;

class Canvas {
    string line[MAXLINES];
    int xMax, yMax;
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' ');
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            if (val.empty()) val = ". ";
            else if (val.size() > 2) val = val.substr(0, 2);
            else if (val.size() < 2) val += " ";
            line[y].replace(x * 2, 2, val);
        }
    }
    void clear(string val = ". ") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char *title = "<My Canvas>") {
        system("clear"); // 리눅스용 화면 클리어, 윈도우는 system("cls");
        cout << title << endl;
        for (int y = 0; y < yMax; y++)
            cout << line[y] << endl;
        cout << endl;
    }
};
