#include "MonsterWorld.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Monster("몬스터", "%", rand() % w, rand() % h));
    game.add(new Jiangshi("장시", "J", rand() % w, rand() % h));
    game.add(new Smombi("스몸비", "S", rand() % w, rand() % h));
    game.add(new Siangshi("샹시", "X", rand() % w, rand() % h));
    game.add(new Dragon("드래곤", "D", rand() % w, rand() % h));

    game.add(new Tuman("왼쪽 경기자", "L", rand() % w, rand() % h));
    game.add(new Tuman("오른쪽 경기자", "R", rand() % w, rand() % h));

    game.play(500, 30);

    std::printf("------게임 종료-------------------\n");
    return 0;
}