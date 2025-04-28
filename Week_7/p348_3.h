// p348_3.h
#ifndef P348_3_H
#define P348_3_H

#include <string>
using namespace std;

class Canvas; // 전방 선언

class Monster {
    string name;
    string icon;
    int x, y;
    int nEnergy; // 에너지
public:
    Monster(const string& n, const string& i, int x_, int y_)
        : name(n), icon(i), x(x_), y(y_), nEnergy(100) {}

    void move(int xMax, int yMax); // 랜덤 이동
    void move(int dx, int dy, int xMax, int yMax); // 수동 이동
    bool eat(int xFood, int yFood); // 먹기
    void print() const; // 정보 출력
    void draw(Canvas& canvas) const; // 화면에 그리기
    int getX() const { return x; }
    int getY() const { return y; }
    int getEnergy() const { return nEnergy; }
    string getName() const { return name; }
};

#endif
