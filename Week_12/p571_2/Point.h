#pragma once
#include <iostream>
#include <cmath>
using namespace std;

// Point: 게임 내 좌표(x, y)를 관리, 좌표 연산 지원
class Point {
    int x, y; // x, y 좌표
    friend class Monster; // Monster가 직접 접근 가능
    friend class Canvas;  // Canvas가 직접 접근 가능

public:
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
    int& operator[](int id) {
        if (id == 0) return x;
        if (id == 1) return y;
        exit(0);
    }
    operator double() { return sqrt((double)x * x + y * y); }
    void operator()(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    Point operator-() { return Point(-x, -y); }
    bool operator==(Point &p) { return x == p.x && y == p.y; }
    bool operator!=(Point &p) { return x != p.x || y != p.y; }
    Point operator-(Point &p) { return Point(x - p.x, y - p.y); }
    Point operator+(Point &p) { return Point(x + p.x, y + p.y); }
    void operator+=(Point &p) { x += p.x, y += p.y; }
    void operator-=(Point &p) { x -= p.x, y -= p.y; }
};