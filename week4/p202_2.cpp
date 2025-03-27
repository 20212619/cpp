#include <iostream>
#include <cstdlib>
#include <ctime>
#include "p202_2.h"

using namespace std;

// 5x5 배열을 0과 1로 랜덤하게 채우는 함수
void randMap(int map[5][5]) {
    srand(time(0)); // 난수 초기화
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 저장
        }
    }
}

// 5x5 배열을 출력하는 함수
void printMap(int map[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

// 가로, 세로, 대각선이 모두 0 또는 1인지 확인하는 함수
void checkMap(int map[5][5]) {
    bool rowAllSame, colAllSame, diag1AllSame = true, diag2AllSame = true;

    // 가로(행) 체크
    for (int i = 0; i < 5; i++) {
        rowAllSame = true;
        for (int j = 1; j < 5; j++) {
            if (map[i][j] != map[i][0]) {
                rowAllSame = false;
                break;
            }
        }
        if (rowAllSame) {
            cout << "Row " << i << " is all " << map[i][0] << endl;
        }
    }

    // 세로(열) 체크
    for (int j = 0; j < 5; j++) {
        colAllSame = true;
        for (int i = 1; i < 5; i++) {
            if (map[i][j] != map[0][j]) {
                colAllSame = false;
                break;
            }
        }
        if (colAllSame) {
            cout << "Column " << j << " is all " << map[0][j] << endl;
        }
    }

    // 대각선 체크 (왼쪽 상단 -> 오른쪽 하단)
    for (int i = 1; i < 5; i++) {
        if (map[i][i] != map[0][0]) {
            diag1AllSame = false;
            break;
        }
    }
    if (diag1AllSame) {
        cout << "Main diagonal is all " << map[0][0] << endl;
    }

    // 대각선 체크 (오른쪽 상단 -> 왼쪽 하단)
    for (int i = 1; i < 5; i++) {
        if (map[i][4 - i] != map[0][4]) {
            diag2AllSame = false;
            break;
        }
    }
    if (diag2AllSame) {
        cout << "Anti-diagonal is all " << map[0][4] << endl;
    }
}

// 메인 함수
int main() {
    int map[5][5];

    randMap(map);   // 랜덤 맵 생성
    printMap(map);  // 맵 출력
    checkMap(map);  // 체크 결과 출력

    return 0;
}
