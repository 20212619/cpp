#include "MonsterWorld.h"
#include <time.h>
int main()
{
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Monster("몬스터", "%", rand() % w, rand() % h));
    game.add(new Monster("도깨비", "#", rand() % w, rand() % h));
    game.add(new Monster("별그대", "*", rand() % w, rand() % h));
    game.add(new Monster("고스트", "@", rand() % w, rand() % h));
    game.play(500, 30); // 보기 편하게 게임 진행 속도를 늦춤
    printf("------게임 종료-------------------\n");
}