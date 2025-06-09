#pragma once
#include "Monster.h"

// Zombie: 8방향 랜덤 이동 몬스터
class Zombie : public Monster {
public:
    Zombie(string n = "허접한좀비", string i = "§", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() { cout << " [Zombie]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 8;
            Point temp;
            switch (dir) {
                case 0: temp = Point(0, -1); break;
                case 1: temp = Point(1, -1); break;
                case 2: temp = Point(1, 0); break;
                case 3: temp = Point(1, 1); break;
                case 4: temp = Point(0, 1); break;
                case 5: temp = Point(-1, 1); break;
                case 6: temp = Point(-1, 0); break;
                case 7: temp = Point(-1, -1); break;
            }
            p += temp;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// Vampire: 상하좌우 4방향 이동 몬스터
class Vampire : public Monster {
public:
    Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { cout << " [Vampire]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 4;
            if (dir == 0) p[0]--;
            else if (dir == 1) p[0]++;
            else if (dir == 2) p[1]--;
            else p[1]++;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// KGhost: 랜덤 위치로 텔레포트
class KGhost : public Monster {
public:
    KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { cout << " [KGhost]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            p = Point(rand() % maxx, rand() % maxy);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// Jiangshi: 수평/수직으로 1~2칸 점프
class Jiangshi : public Monster {
protected:
    bool bHori;
public:
    Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { cout << " [Jiangshi]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 2;
            int jump = rand() % 2 + 1;
            if (bHori) p[0] += (dir == 0) ? -jump : jump;
            else p[1] += (dir == 0) ? -jump : jump;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// Smombi: 대각선 4방향 이동
class Smombi : public Monster {
public:
    Smombi(string n = "스몸비", string i = "↘", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Smombi() { cout << " [Smombi]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 4;
            if (dir == 0) { p[0]--; p[1]--; }
            else if (dir == 1) { p[0]++; p[1]--; }
            else if (dir == 2) { p[0]--; p[1]++; }
            else { p[0]++; p[1]++; }
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// Siangshi: 50번 이동마다 수평/수직 전환하며 점프
class Siangshi : public Jiangshi {
    int moveCount;
    const int switchInterval = 50;
public:
    Siangshi(string n = "수퍼강시", string i = "⇄", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
    ~Siangshi() { cout << " [Siangshi]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            moveCount++;
            if (moveCount >= switchInterval) {
                bHori = !bHori;
                moveCount = 0;
            }
            int dir = rand() % 2;
            int jump = rand() % 2 + 1;
            if (bHori) p[0] += (dir == 0) ? -jump : jump;
            else p[1] += (dir == 0) ? -jump : jump;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// KGhostold: 2번 이동마다 랜덤 텔레포트
class KGhostold : public KGhost {
    int moveCount;
public:
    KGhostold(string n = "노처녀귀신", string i = "♡", int x = 0, int y = 0)
        : KGhost(n, i, x, y), moveCount(0) {}
    ~KGhostold() { cout << " [KGhostold]"; }
    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            moveCount++;
            if (moveCount >= 2) {
                p = Point(rand() % maxx, rand() % maxy);
                moveCount = 0;
            }
            clip(maxx, maxy);
            eat(map);
        }
    }
};