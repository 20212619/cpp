#pragma once
#include "Canvas.h"
#include <iostream>
#include <unistd.h>
#include <string>

class Monster {
protected:
    std::string name, icon;
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
    Monster(std::string n = "몬스터", std::string i = "%", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {
        count++;
    }
    virtual ~Monster() {
        std::cout << "Monster 하나가 굶어죽습니다" << std::endl;
        usleep(1000000);
        std::cout << "\t" << name << icon << " 소멸되었습니다~~~\n";
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
    virtual void move(int** map, int maxx, int maxy, char ch) {}
    virtual void print() {
        std::cout << "\t" << name << " " << icon << ":" << nItem << " E:" << nEnergy << std::endl;
    }
    int getEnergy() { return nEnergy; }
    static void printCount() {
        std::cout << "전체 몬스터 수 = " << count << std::endl;
    }
};
int Monster::count = 0;

class Jiangshi : public Monster {
public:
    Jiangshi(std::string n = "장시", std::string i = "J", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        switch (dir) {
            case 0: y--; break;
            case 1: x++; break;
            case 2: y++; break;
            case 3: x--; break;
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};

class Smombi : public Monster {
public:
    Smombi(std::string n = "스몸비", std::string i = "S", int px = 0, int py = 0)
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

class Siangshi : public Jiangshi {
    bool horizontal;
    int turnCount;
    const int switchInterval = 10;
public:
    Siangshi(std::string n = "샹시", std::string i = "X", int px = 0, int py = 0)
        : Jiangshi(n, i, px, py), horizontal(true), turnCount(0) {}
    void move(int** map, int maxx, int maxy) override {
        if (turnCount % switchInterval == 0) {
            horizontal = !horizontal;
        }
        turnCount++;
        int dir = 0;
        if (horizontal) {
            dir = (rand() % 2 == 0) ? 1 : 3;
        } else {
            dir = (rand() % 2 == 0) ? 0 : 2;
        }
        switch (dir) {
            case 0: y--; break;
            case 1: x++; break;
            case 2: y++; break;
            case 3: x--; break;
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
};

class Dragon : public Jiangshi {
    int jumpCount;
public:
    Dragon(std::string n = "드래곤", std::string i = "D", int px = 0, int py = 0)
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

class Tuman : public Monster {
public:
    Tuman(std::string n = "인간", std::string i = "좌", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void moveHuman(int** map, int maxx, int maxy, char ch) {
        int prevX = x, prevY = y;
        if (icon == "좌") {
            switch (ch) {
                case 'w': y--; break;
                case 's': y++; break;
                case 'a': x--; break;
                case 'd': x++; break;
            }
        } else if (icon == "우") {
            switch (ch) {
                case 'A': y--; break; // 위 (리눅스 화살표 키: \033[A -> 'A')
                case 'B': y++; break; // 아래
                case 'D': x--; break; // 왼쪽
                case 'C': x++; break; // 오른쪽
            }
        }
        clip(maxx, maxy);
        eat(map);
        nEnergy -= 1;
        if (nEnergy < 0) nEnergy = 0;
    }
    void move(int** map, int maxx, int maxy) override {}
    void move(int** map, int maxx, int maxy, char ch) override {
        moveHuman(map, maxx, maxy, ch);
    }
};