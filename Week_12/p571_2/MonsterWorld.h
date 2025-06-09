#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include "VariousMonsters.h"
#include "Human.h"
#include <unistd.h>
#include <termios.h> // 추가
#include <fcntl.h>   // 추가
#define DIM 40
#define MAXMONS 10

// MonsterWorld: 게임 세계 관리 (맵, 몬스터, 플레이어 동작, 출력)
class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(y, x); }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void checkStarvation() {
        for (int k = 0; k < nMon - 2; k++) {
            if (pMon[k]->getEnergy() == 0) {
                cout << "Monster 하나가 굶어죽습니다" << endl;
                cout.flush();
                delete pMon[k];
                cout.flush();
                pMon[k] = pMon[nMon - 3];
                pMon[nMon - 3] = pMon[nMon - 2];
                pMon[nMon - 2] = pMon[nMon - 1];
                nMon--;
                k--;
                usleep(500000);
            }
        }
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "■");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (여유있는 삶) ]");
        cout << " 전체 이동 횟수 = " << nMove << endl;
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
        Monster::printCount();
    }

public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }
    void add(Monster* m) {
        if (nMon < MAXMONS) pMon[nMon++] = m;
    }
    void play(int maxwalk, int wait) {
        print();
        cout << " 엔터를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            if (nMon >= 2) {
                for (int k = 0; k < nMon - 2; k++)
                    pMon[k]->move(world.Data(), xMax, yMax);
                if (kbhit()) {
                    struct termios oldt, newt;
                    tcgetattr(STDIN_FILENO, &oldt);
                    newt = oldt;
                    newt.c_lflag &= ~(ICANON | ECHO);
                    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                    unsigned char ch = getchar();
                    if (ch == 27 && nMon > 1) {
                        getchar();
                        ch = getchar();
                        ((Tuman*)(pMon[nMon - 1]))->moveHuman(world.Data(), xMax, yMax, ch);
                    } else if (nMon > 0) {
                        ((Tuman*)(pMon[nMon - 2]))->moveHuman(world.Data(), xMax, yMax, ch);
                    }
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                }
            }
            nMove++;
            checkStarvation();
            print();
            if (isDone() || nMon < 2) break;
            usleep(wait * 1000);
        }
    }
    Monster* getMonster(int index) const { return pMon[index]; }
    int getNMon() const { return nMon; }
};