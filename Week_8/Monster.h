#pragma once
#include "Canvas.h"
#include <unistd.h> // usleep() 함수를 사용하기 위한 헤더
#define DIM 40

class Monster {
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
    void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8; // 아이템을 먹으면 에너지 8 증가
        } else {
            nEnergy -= 1; // 아이템을 먹지 못하면 에너지 1 감소
            if (nEnergy < 0) nEnergy = 0; // 에너지 최솟값 0 유지
        }
    }
public:
    Monster(string n = "몬스터", string i = "%", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { // 초기화 리스트에 에너지를 100으로 초기화
        count++; // 추가: 생성 시 몬스터 수 증가
    }
    ~Monster() { 
        cout << "Monster 하나가 굶어죽습니다" << endl;
        usleep(1000000); // 1초 대기
        cout << "\t" << name << icon << " 소멸되었습니다~~~\n";
        usleep(1000000); // 1초 대기
        count--; // 추가: 소멸 시 몬스터 수 감소
    }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    void move(int** map, int maxx, int maxy) {
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
        nEnergy -= 1; // 이동할 때 에너지 1 소모 = 에너지를 먹지 못하면 1 소모
        if (nEnergy < 0) nEnergy = 0; // 에너지가 음수가 되지 않도록
    }
    void print() { 
        cout << "\t" << name << " " << icon << ":" << nItem << " E:" << nEnergy << endl;
    }
    int getEnergy() { return nEnergy; } // nEnergy를 반환하는 getter 함수
    static void printCount() { // 추가: 현재 몬스터 수 출력
        cout << "전체 몬스터 수 = " << count << endl;
    }
};

// 정적 멤버 변수 정의
int Monster::count = 0; // 추가: count 초기화