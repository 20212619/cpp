#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct Move {
    int x, y;
    char direction;
};

// 현재 시간을 문자열로 반환하는 함수
string getCurrentTime() {
    time_t now = time(0);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

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

// 게임 상태 저장 함수
void saveGame(int** map, int size, vector<Move>& moves, string startTime) {
    ofstream file("saved_game.txt");
    if (!file) {
        cout << "파일 저장 실패!" << endl;
        return;
    }

    file << "게임 시작 시간: " << startTime << endl;
    file << "게임 종료 시간: " << getCurrentTime() << endl;
    file << "맵 크기: " << size << "x" << size << endl;

    file << "현재 맵 상태:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << map[i][j] << " ";
        }
        file << endl;
    }

    file << "\n움직임 기록:\n";
    for (const auto& move : moves) {
        file << "위치: (" << move.x << ", " << move.y << "), 방향: " << move.direction << endl;
    }

    file.close();
    cout << "게임 상태가 saved_game.txt에 저장되었습니다!" << endl;
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

    // 맵 생성
    randMap(map, size);
    printMap(map, size);

    vector<Move> moves; // 사용자 움직임 기록
    string startTime = getCurrentTime(); // 게임 시작 시간 저장
    char command;

    while (true) {
        cout << "움직일 방향을 입력하세요 (W: 위, S: 아래, A: 왼쪽, D: 오른쪽, Q: 종료, X: 저장 후 종료): ";
        cin >> command;
        if (command == 'Q' || command == 'q') break;
        if (command == 'X' || command == 'x') {
            saveGame(map, size, moves, startTime);
            break;
        }

        int x = rand() % size, y = rand() % size; // 랜덤 위치 이동 (예제용)
        moves.push_back({x, y, command});
    }

    // 동적 메모리 해제
    for (int i = 0; i < size; i++) {
        delete[] map[i];
    }
    delete[] map;
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
