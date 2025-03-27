#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// 4×4 퍼즐 맵
char puzzle[4][4] = {
    {'A', 'B', 'C', 'D'},
    {'E', 'F', 'G', 'H'},
    {'I', 'J', 'K', 'L'},
    {'M', 'N', 'O', ' '}
};

// 퍼즐 섞기 함수
void shufflePuzzle() {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int x = rand() % 4;
        int y = rand() % 4;
        int nx = rand() % 4;
        int ny = rand() % 4;
        swap(puzzle[x][y], puzzle[nx][ny]);
    }
}

// 퍼즐 출력 함수
void printPuzzle() {
    cout << "\n퍼즐 상태:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "[" << puzzle[i][j] << "] ";
        }
        cout << endl;
    }
}

// 빈 칸(공백)의 위치 찾기
pair<int, int> findEmptyTile() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (puzzle[i][j] == ' ') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // 오류 방지용
}

// 퍼즐 조각 이동 함수
void moveTile(char move) {
    pair<int, int> empty = findEmptyTile();
    int x = empty.first;
    int y = empty.second;

    int nx = x, ny = y;

    if (move == 'W' && x > 0) nx--; // 위로 이동
    if (move == 'S' && x < 3) nx++; // 아래로 이동
    if (move == 'A' && y > 0) ny--; // 왼쪽 이동
    if (move == 'D' && y < 3) ny++; // 오른쪽 이동

    swap(puzzle[x][y], puzzle[nx][ny]);
}

// 원래 상태인지 확인
bool isSolved() {
    char goal[4][4] = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', ' '}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (puzzle[i][j] != goal[i][j]) return false;
        }
    }
    return true;
}

// 게임 실행
void playGame() {
    shufflePuzzle(); // 게임 시작 전 퍼즐 섞기
    printPuzzle();
    
    while (true) {
        cout << "WASD로 조각 이동 (Q: 종료): ";
        char move;
        cin >> move;
        if (move == 'Q' || move == 'q') break;

        moveTile(move);
        printPuzzle();

        if (isSolved()) {
            cout << "🎉 축하합니다! 퍼즐을 맞췄습니다! 🎉" << endl;
            break;
        }
    }
}

int main() {
    while (true) {
        cout << "1. 그림 퍼즐 시작\n2. 종료\n선택 (1/2): ";
        int choice;
        cin >> choice;

        if (choice == 1) playGame();
        else if (choice == 2) {
            cout << "게임 종료!" << endl;
            break;
        } else {
            cout << "잘못된 입력입니다!" << endl;
        }
    }
    return 0;
}
