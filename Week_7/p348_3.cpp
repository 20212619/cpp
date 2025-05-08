// p348_3.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include "p348_3.h"
using namespace std;

#define MAXLINES 100

class Canvas {
    string line[MAXLINES];
    int xMax, yMax;
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' ');
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            line[y].replace(x * 2, 2, val);
    }
    void clear(string val = "□") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char* title = "<Monster World>") {
        system("clear"); // 리눅스용
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                cout << line[y].substr(x * 2, 2);
                if (x < xMax - 1) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

class MonsterWorld {
    Canvas canvas;
    Monster* monsters[100];
    int nMonsters;
    int xMax, yMax;
    int xFood, yFood;
    int totalMoveCount;
    int foodCount;
public:
    MonsterWorld(int w, int h) : canvas(w, h), nMonsters(0), xMax(w), yMax(h), totalMoveCount(0), foodCount(0) {
        xFood = 3;
        yFood = 3;
    }
    void add(Monster m) {
        if (nMonsters < 100) {
            monsters[nMonsters++] = new Monster(m);
        }
    }
    void play(int maxSteps, int foodSteps) {
        int step = 0;
        int foodTimer = 0;
        char input;
        while (step++ < maxSteps) {
            canvas.clear();
            canvas.draw(xFood, yFood, "@@");

            cout << "WASD로 몬스터 이동, Q로 종료: ";
            cin >> input;
            if (input == 'q' || input == 'Q') break;

            int dx = 0, dy = 0;
            if (input == 'w' || input == 'W') dy = -1;
            else if (input == 's' || input == 'S') dy = 1;
            else if (input == 'a' || input == 'A') dx = -1;
            else if (input == 'd' || input == 'D') dx = 1;
            monsters[0]->move(dx, dy, xMax, yMax);

            for (int i = 1; i < nMonsters; i++) {
                monsters[i]->move(xMax, yMax);
            }

            for (int i = 0; i < nMonsters; i++) {
                if (monsters[i]->eat(xFood, yFood)) {
                    xFood = rand() % xMax;
                    yFood = rand() % yMax;
                    foodTimer = 0;
                    foodCount++;
                }
                monsters[i]->draw(canvas);
            }

            totalMoveCount++;
            canvas.print("Monster World (Basic)");

            cout << "전체 이동 횟수 = " << totalMoveCount << endl;
            cout << "남은 아이템 수 = " << foodCount << endl;
            for (int i = 0; i < nMonsters; i++) {
                monsters[i]->print();
            }
            cout << endl;

            if (++foodTimer >= foodSteps) {
                xFood = rand() % xMax;
                yFood = rand() % yMax;
                foodTimer = 0;
            }
        }

        cout << "\n게임 종료\n";
        cout << "전체 이동 횟수 = " << totalMoveCount << endl;
        cout << "남은 아이템 수 = " << foodCount << endl;
        for (int i = 0; i < nMonsters; i++) {
            cout << monsters[i]->getName() << " Energy = " << monsters[i]->getEnergy() << endl;
        }
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMonsters; i++) {
            delete monsters[i];
        }
    }
};

// Monster 멤버 함수들 구현

void Monster::move(int xMax, int yMax) {
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;
    x = max(0, min(xMax - 1, x + dx));
    y = max(0, min(yMax - 1, y + dy));
}

void Monster::move(int dx, int dy, int xMax, int yMax) {
    x = max(0, min(xMax - 1, x + dx));
    y = max(0, min(yMax - 1, y + dy));
}

bool Monster::eat(int xFood, int yFood) {
    if (x == xFood && y == yFood) {
        nEnergy += 8;
        return true;
    }
    nEnergy = max(0, nEnergy - 1);
    return false;
}

void Monster::print() const {
    cout << name << " E:" << nEnergy << endl;
}

void Monster::draw(Canvas& canvas) const {
    canvas.draw(x, y, icon);
}

// main 함수
int main() {
    srand((unsigned int)time(NULL));
    int w = 20, h = 10;

    MonsterWorld game(w, h);
    game.add(Monster("몬스터", "♠", 0, 1));
    game.add(Monster("도깨비", "♥", 19, 1));
    game.add(Monster("별그대", "♣", 19, 9));
    game.add(Monster("고스트", "★", 0, 9));
    
    game.play(300, 10);
    return 0;
}
