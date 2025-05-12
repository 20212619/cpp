#pragma once
#include <iostream>
#include <string>
using namespace std;

#define DIM 40

class Monster {
    string name, icon; // 몬스터 이름과 아이콘
    int x, y, nItem;   // 위치 및 아이템 개수
    int nEnergy;       // 에너지
    static int monsterCount;  // 몬스터 수 관리

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

public:
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {
        monsterCount++;  // 몬스터 수 증가
    }

    ~Monster() {
        cout << "\t" << name << icon << " 물러갑니다~~~\n";
        monsterCount--;  // 몬스터 수 감소
    }

    static int getMonsterCount() {
        return monsterCount;
    }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    
    void move(int map[DIM][DIM], int maxx, int maxy) {
        if (nEnergy <= 0) return;  // 에너지가 0이면 이동하지 않음

        // 이동 방향
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
    }

    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) { // 아이템을 먹음
            map[y][x] = 0;  // 아이템 제거
            nItem++;
            nEnergy += 8;  // 아이템 먹으면 에너지 증가
        } else {
            nEnergy -= 1;  // 아이템을 못 먹으면 에너지 감소
            if (nEnergy < 0) nEnergy = 0;  // 에너지는 0 이하로 가지 않음
        }

        if (nEnergy == 0) {
            cout << name << "이(가) 굶어 죽었습니다.\n";
            monsterCount--;  // 몬스터 수 감소
        }
    }

    void print() {
        if (nEnergy > 0)
            cout << "\t" << name << icon << " : 아이템=" << nItem << " 에너지=" << nEnergy << endl;
        else
            cout << "\t" << name << icon << " (죽음)\n";
    }

    int getEnergy() const { return nEnergy; }
};

int Monster::monsterCount = 0;  // 몬스터 수 초기화
