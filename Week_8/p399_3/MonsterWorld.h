#pragma once
#include "Canvas.h"
#include "Monster.h"
#include <unistd.h>
#define DIM 40
#define MAXMONS 5

class MonsterWorld {
    int map[DIM][DIM];
    int xMax, yMax, nMon, nMove;
    Monster mon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return map[y][x]; }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "■");
        for (int i = 0; i < nMon; i++)
            mon[i].draw(canvas);
        canvas.print("[ Monster World (Basic) ]");

        cout << " 전체 이동 횟수 = " << nMove << endl;
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            mon[i].print();
    }

    void checkStarvation() {
        for (int i = 0; i < nMon; i++) {
            if (mon[i].getEnergy() <= 0) {
                cout << "몬스터 " << i + 1 << "이(가) 굶어 죽었습니다. 몬스터 수: " << Monster::getMonsterCount() << endl;
                mon[i] = mon[nMon - 1];  // 죽은 몬스터를 맨 뒤 몬스터로 교체
                nMon--;  // 몬스터 수 감소
            }
        }
    }

public:
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }

    ~MonsterWorld() {}

    void add(const Monster& m) {
        if (nMon < MAXMONS) mon[nMon++] = m;
    }

    void play(int maxwalk, int wait) {
        print();
        cout << " 엔터를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                mon[k].move(map, xMax, yMax);  // 몬스터 이동
            nMove++;
            checkStarvation();  // 굶어 죽은 몬스터 체크
            print();
            if (isDone()) break;
            usleep(wait * 1000);
        }
    }
};
