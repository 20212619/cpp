#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 랜덤 맵 생성 함수
void randMap(int** map, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 랜덤 배치
        }
    }
}

// 맵 출력 함수
void printMap(int** map, int size) {
    cout << "  ";
    for (int i = 0; i < size; i++) cout << i << " ";
    cout << "\n  " << string(size * 2, '-') << endl;

    for (int i = 0; i < size; i++) {
        cout << i << "| ";
        for (int j = 0; j < size; j++) {
            cout << (map[i][j] == 0 ? "□ " : "■ ");
        }
        cout << "|" << endl;
    }
    cout << "  " << string(size * 2, '-') << endl;
}

int main() {
    int size;
    cout << "퍼즐 크기를 선택하세요 (3 또는 5): ";
    cin >> size;

    if (size != 3 && size != 5) {
        cout << "잘못된 입력! 3 또는 5만 선택 가능합니다." << endl;
        return 1;
    }

    // 동적 2D 배열 생성
    int** map = new int*[size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
    }

    // 맵 생성 및 출력
    randMap(map, size);
    printMap(map, size);

    // 동적 메모리 해제
    for (int i = 0; i < size; i++) {
        delete[] map[i];
    }
    delete[] map;

    return 0;
}
