#pragma once
#include "Canvas.h"
#include <iostream>
#include <unistd.h> // usleep()
#include <string>
using namespace std;

class Monster {
protected:
    string name, icon;
    int x, y, nItem;
    int nEnergy;
    static int count;

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    virtual void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8;
        } else {
            nEnergy -= 1;
            if (nEnergy < 0) nEnergy = 0;
        }
    }
public:
    Monster(string n = "몬스터", string i = "%", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {
        count++;
    }
    virtual ~Monster() {
        cout << "Monster 하나가 굶어죽습니다" << endl;
        usleep(1000000);
        cout << "\t" << name << icon << " 소멸되었습니다~~~\n";
        usleep(1000000);
        count--;
    }

    virtual void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    virtual void move(int** map, int maxx, int maxy) {
        switch (rand() % 8) {
            case 0: y--; break;
            case 1: x++; y--; break;
            case 2: x++; break;
            case 3: x++; y++; break;
            case 4: y++; break;
            case 5: x--; y++; break;
            case 6: x--; break;
            case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
    virtual void print() {
        cout << "\t" << name << " " << icon << ":" << nItem << " E:" << nEnergy << endl;
    }
    int getEnergy() { return nEnergy; }
    static void printCount() {
        cout << "전체 몬스터 수 = " << count << endl;
    }
};
int Monster::count = 0;

// Jiangshi 클래스 (Monster 상속)
class Jiangshi : public Monster {
public:
    Jiangshi(string n = "장시", string i = "J", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int** map, int maxx, int maxy) override {
        // 수직 또는 수평 이동만
        int dir = rand() % 4;
        switch (dir) {
            case 0: y--; break; // 위
            case 1: x++; break; // 오른쪽
            case 2: y++; break; // 아래
            case 3: x--; break; // 왼쪽
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};

// Smombi 클래스 (Monster 상속, 대각선 이동만)
class Smombi : public Monster {
public:
    Smombi(string n = "스몸비", string i = "S", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        switch (dir) {
            case 0: x++; y++; break;
            case 1: x--; y++; break;
            case 2: x++; y--; break;
            case 3: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};

// Siangshi 클래스 (Jiangshi 상속, 일정 시간마다 이동 방향 바꿈)
class Siangshi : public Jiangshi {
    bool horizontal; // true: 가로, false: 세로
    int turnCount;
    const int switchInterval = 10; // 10턴마다 방향 전환
public:
    Siangshi(string n = "샹시", string i = "X", int px = 0, int py = 0)
        : Jiangshi(n, i, px, py), horizontal(true), turnCount(0) {}

    void move(int** map, int maxx, int maxy) override {
        if (turnCount % switchInterval == 0) {
            horizontal = !horizontal;
        }
        turnCount++;

        int dir = 0;
        if (horizontal) {
            dir = (rand() % 2 == 0) ? 1 : 3; // 오른쪽 or 왼쪽
        } else {
            dir = (rand() % 2 == 0) ? 0 : 2; // 위 or 아래
        }

        switch (dir) {
            case 0: y--; break; // 위
            case 1: x++; break; // 오른쪽
            case 2: y++; break; // 아래
            case 3: x--; break; // 왼쪽
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};

// Dragon 클래스 (Jiangshi 상속, 5턴마다 2칸 점프)
class Dragon : public Jiangshi {
    int jumpCount;
public:
    Dragon(string n = "드래곤", string i = "D", int px = 0, int py = 0)
        : Jiangshi(n, i, px, py), jumpCount(0) {}

    void move(int** map, int maxx, int maxy) override {
        jumpCount++;
        if (jumpCount % 5 == 0) {
            int dir = rand() % 4;
            switch (dir) {
                case 0: y -= 2; break;
                case 1: x += 2; break;
                case 2: y += 2; break;
                case 3: x -= 2; break;
            }
        } else {
            Jiangshi::move(map, maxx, maxy);
            return;
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};
