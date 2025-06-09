#pragma once
#include "Canvas.h"
#include "Point.h"
#define DIM 40

// Monster: 몬스터의 기본 속성과 동작(이동, 아이템 먹기, 에너지 관리) 정의
class Monster {
protected:
    string name, icon; // 이름과 화면에 표시할 아이콘
    Point q, p;        // q: 이전 위치, p: 현재 위치
    int nItem;         // 먹은 아이템 수
    int nEnergy;       // 에너지 (기본 100)
    int nSleep;        // 휴식 횟수
    double dist;       // 현재 이동 거리
    double total;      // 총 이동 거리
    static int nMonsters; // 전체 몬스터 수

    void clip(int maxx, int maxy) {
        p(maxx, maxy);
    }
    void eat(int** map) {
        if (map[p[1]][p[0]] == 1) {
            map[p[1]][p[0]] = 0;
            nItem++;
            nEnergy += 8;
        } else {
            nEnergy = max(0, nEnergy - 1);
        }
        dist += (double)(p - q);
        total += (double)(p - q);
        q = p;
        if (dist > 20) {
            dist = 0;
            nSleep = 10;
        }
    }
    bool isSleep() {
        if (nSleep > 0) {
            nSleep--;
            return true;
        }
        return false;
    }

public:
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), p(px, py), q(px, py), nItem(0), nEnergy(100), nSleep(0), dist(0.0), total(0.0) {
        nMonsters++;
    }
    virtual ~Monster() {
        cout << "\t" << name << icon << " " << nItem << " E:" << nEnergy << "\t거리:" << total << endl;
        nMonsters--;
    }
    void draw(Canvas &canvas) { canvas.draw(p, icon); }
    virtual void move(int** map, int maxx, int maxy) {
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
    void print() {
        cout << "\t" << name << icon << " :" << nItem << " E:" << nEnergy << " Sleep:" << nSleep << endl;
    }
    int getEnergy() { return nEnergy; }
    static void printCount() { cout << "  전체 몬스터의 수:" << nMonsters << endl; }
    int getNItem() const { return nItem; }
    double getTotal() const { return total; }
};

int Monster::nMonsters = 0;