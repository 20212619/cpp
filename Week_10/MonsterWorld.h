#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>

#define MAXMONS 8

// 비동기 키 입력 함수
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char getch(void) {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }
    bool isDone() { return countItems() == 0 || nMon == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void checkStarvation() {
        for (int i = 0; i < nMon;) {
            if (pMon[i]->getEnergy() == 0) {
                delete pMon[i];
                for (int j = i; j < nMon - 1; j++) {
                    pMon[j] = pMon[j + 1];
                }
                nMon--;
            } else {
                i++;
            }
        }
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "O");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (움직이는 몬스터) ]");

        std::cerr << " 전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << " 남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
        std::cout << "전체 몬스터의 수 : " << nMon << std::endl;
    }
public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }
    void add(Monster* m) {
        if (nMon < MAXMONS)
            pMon[nMon++] = m;
    }
    void play(int maxwalk, int wait) {
        print();
        std::cerr << " 시작하려면 엔터키 입력하세요...";
        getchar();

        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon - 2; k++)
                pMon[k]->move(world.Data(), xMax, yMax);

            if (kbhit()) {
                char ch = getch();
                if (ch == '\033') { // 화살표 키 시작
                    getch(); // '[' 건너뛰기
                    char arrow = getch();
                    pMon[nMon - 1]->move(world.Data(), xMax, yMax, arrow); // 오른쪽 경기자
                } else {
                    pMon[nMon - 2]->move(world.Data(), xMax, yMax, ch); // 왼쪽 경기자
                }
            }

            nMove++;
            print();
            checkStarvation();
            if (isDone()) break;
            usleep(wait * 1000);
        }
    }
};