// p248_4.h - 헤더 파일
#ifndef P248_4_H
#define P248_4_H

const int MAX_WIDTH = 80;
const int MAX_HEIGHT = 40;

void initializeMineMap(int width, int height, int mineCount);
void printMap(int width, int height);
void revealCell(int x, int y, int width, int height);
void toggleFlag(int x, int y);
bool isGameWon(int width, int height);
void playGame(int width, int height);

#endif