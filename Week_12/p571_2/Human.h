#pragma once
#include "Monster.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// kbhit: 키보드 입력 확인 (비차단 방식)
int kbhit(void) {
    struct termios oldt, newt;
    int ch, oldf;
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

// Human: 키보드로 움직이는 플레이어 클래스
class Human : public Monster {
public:
    Human(string n = "미래인류", string i = "♀", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    ~Human() { cout << " [Human]"; }
    void move(int** map, int maxx, int maxy) {
        if (kbhit()) {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            int ch = getchar();
            if (ch == 27) {
                getchar();
                ch = getchar();
                if (ch == 'A') p[1]--;
                else if (ch == 'B') p[1]++;
                else if (ch == 'C') p[0]++;
                else if (ch == 'D') p[0]--;
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

// Tuman: 두 플레이어(WASD, 화살표 키) 관리
class Tuman : public Human {
    bool isRightPlayer;

public:
    Tuman(string n = "미래의인류", string i = "♀", int px = 0, int py = 0, bool rightPlayer = false)
        : Human(n, i, px, py), isRightPlayer(rightPlayer) {}
    ~Tuman() { cout << " [Tuman]"; }
    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        if (isRightPlayer) {
            if (ch == 'A') p[1]--;
            else if (ch == 'B') p[1]++;
            else if (ch == 'C') p[0]++;
            else if (ch == 'D') p[0]--;
        } else {
            if (ch == 'w' || ch == 'W') p[1]--;
            else if (ch == 's' || ch == 'S') p[1]++;
            else if (ch == 'a' || ch == 'A') p[0]--;
            else if (ch == 'd' || ch == 'D') p[0]++;
        }
        clip(maxx, maxy);
        eat(map);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    void move(int** map, int maxx, int maxy) override {}
    bool getIsRightPlayer() const { return isRightPlayer; }
    // Monster 클래스에서 상속받은 함수 명시적 선언
    int getNItem() const { return Monster::getNItem(); }
    double getTotal() const { return Monster::getTotal(); }
};