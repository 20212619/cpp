#pragma once
#include <string>
#include <iostream> // std::cout, std::endl 사용을 위해 추가

#define MAXLINES 100

class Canvas {
    std::string line[MAXLINES];
    int xMax, yMax;
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = std::string(xMax * 2, ' ');
    }
    void draw(int x, int y, std::string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            if (val.empty()) val = ". ";
            else if (val.size() > 2) val = val.substr(0, 2);
            else if (val.size() < 2) val += " ";
            line[y].replace(x * 2, 2, val);
        }
    }
    void clear(std::string val = ". ") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char *title = "<My Canvas>") {
        std::cout << "\033[2J\033[1;1H"; // ANSI 이스케이프 시퀀스로 화면 지우기
        std::cout << title << std::endl;
        for (int y = 0; y < yMax; y++)
            std::cout << line[y] << std::endl;
        std::cout << std::endl;
    }
};