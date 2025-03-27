#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Move {
    int x, y;
    char direction;
};

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

// 리플레이 기능
void replay(vector<Move>& moves) {
    cout << "\n📢 리플레이 시작!" << endl;
    for (size_t i = 0; i < moves.size(); i++) {
        cout << "Step " << i + 1 << ": (" << moves[i].x << ", " << moves[i].y << ") → "
             << moves[i].direction << endl;
    }
}

// 게임 실행 함수
void playGame() {
    int size;
    cout << "퍼즐 크기를 선택하세요 (3 또는 5): ";
    cin >> size;

    if (size != 3 && size != 5) {
        cout << "잘못된 입력! 3 또는 5만 선택 가능합니다." << endl;
        return;
    }

    // 동적 2D 배열 생성
    int** map = new int*[size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
    }

    // 맵 생성 및 저장
    randMap(map, size);
    int** originalMap = new int*[size];  // 최초 맵 저장용
    for (int i = 0; i < size; i++) {
        originalMap[i] = new int[size];
        for (int j = 0; j < size; j++) {
            originalMap[i][j] = map[i][j]; // 최초 상태 저장
        }
    }

    printMap(map, size);

    vector<Move> moves; // 사용자 움직임 기록
    char command;
    while (true) {
        cout << "움직일 방향을 입력하세요 (W: 위, S: 아래, A: 왼쪽, D: 오른쪽, Q: 종료): ";
        cin >> command;
        if (command == 'Q' || command == 'q') break;

        int x = rand() % size, y = rand() % size; // 랜덤 위치 이동 (예제용)
        moves.push_back({x, y, command});
    }

    // 리플레이 실행
    replay(moves);

    // 동적 메모리 해제
    for (int i = 0; i < size; i++) {
        delete[] map[i];
        delete[] originalMap[i];
    }
    delete[] map;
    delete[] originalMap;
}

int main() {
    while (true) {
        playGame();

        char choice;
        cout << "다시 하시겠습니까? (Y/N): ";
        cin >> choice;
        if (choice == 'N' || choice == 'n') {
            cout << "게임 종료!" << endl;
            break;
        }
    }
    return 0;
}
