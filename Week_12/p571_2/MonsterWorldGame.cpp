#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "RankingBoard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

// getch: 즉시 키 입력 받기
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// main: 게임 초기화, 몬스터 추가, 게임 실행, 랭킹 관리
int main() {
    RankingBoard rank;
    try {
        rank.load("MonsterWorld.rnk");
    } catch (FileException e) {
        char str[80];
        string passwd, correct = "123456";
        cout << "관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) {
            str[i] = getch();
            if (str[i] == '\n') {
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
            putchar('*');
        }
        if (passwd != correct) {
            cout << "비밀번호가 맞지 않습니다. 게임 종료.\n\n";
            exit(0);
        }
    }
    rank.print("[게임 랭킹: 시작]");

    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("허접한좀비", "§", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
    game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
    game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
    game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
    game.add(new Smombi("나는스몸비", "↘", rand() % w, rand() % h));
    game.add(new Siangshi("난수퍼강시", "⇄", rand() % w, rand() % h, true));
    game.add(new KGhostold("노처녀귀신", "♡", rand() % w, rand() % h));
    game.add(new Tuman("미래의좌파", "☜", rand() % w, rand() % h, false));
    game.add(new Tuman("미래의우파", "☞", rand() % w, rand() % h, true));

    game.play(500, 50);
    cout << "------게임 종료-------------------" << endl;

    Tuman* leftPlayer = (Tuman*)game.getMonster(game.getNMon() - 2);
    Tuman* rightPlayer = (Tuman*)game.getMonster(game.getNMon() - 1);
    double leftIpm = (leftPlayer->getTotal() > 0) ? leftPlayer->getNItem() / leftPlayer->getTotal() : 0.0;
    double rightIpm = (rightPlayer->getTotal() > 0) ? rightPlayer->getNItem() / rightPlayer->getTotal() : 0.0;

    if (leftPlayer->getNItem() >= rightPlayer->getNItem()) {
        rank.add(leftPlayer->getNItem(), leftIpm, leftPlayer->getIsRightPlayer());
        rank.add(rightPlayer->getNItem(), rightIpm, rightPlayer->getIsRightPlayer());
    } else {
        rank.add(rightPlayer->getNItem(), rightIpm, rightPlayer->getIsRightPlayer());
        rank.add(leftPlayer->getNItem(), leftIpm, leftPlayer->getIsRightPlayer());
    }
    rank.print("[게임 랭킹: 종료]");

    try {
        rank.store("MonsterWorld.rnk");
    } catch (FileException e) {
        char str[80];
        string passwd, correct = "123456";
        cout << "랭킹 저장 실패. 관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) {
            str[i] = getch();
            if (str[i] == '\n') {
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
            putchar('*');
        }
        if (passwd != correct) {
            cout << "비밀번호가 맞지 않습니다. 랭킹 저장 없이 게임 종료.\n\n";
            exit(0);
        }
        string newFilename;
        cout << "새로운 랭킹 파일 이름을 입력하세요: ";
        getline(cin, newFilename);
        rank.store(newFilename);
    }

    return 0;
}