#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;

struct Record {
    char name[20];  // 플레이어 이름
    double time;    // 걸린 시간
};

// 4×4 퍼즐 맵
char puzzle[4][4] = {
    {'A', 'B', 'C', 'D'},
    {'E', 'F', 'G', 'H'},
    {'I', 'J', 'K', 'L'},
    {'M', 'N', 'O', ' '}
};

// 랭킹 저장 파일 이름
const char* RANKING_FILE = "ranking.dat";

// 랭킹 저장을 위한 벡터
vector<Record> ranking;

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

// 랭킹 파일에서 데이터 읽기
void loadRanking() {
    ranking.clear();
    ifstream file(RANKING_FILE, ios::binary);
    if (file.is_open()) {
        Record rec;
        while (file.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
            ranking.push_back(rec);
        }
        file.close();
    }
}

// 랭킹 파일 저장
void saveRanking() {
    ofstream file(RANKING_FILE, ios::binary | ios::trunc);
    if (file.is_open()) {
        for (size_t i = 0; i < min(ranking.size(), size_t(10)); i++) {
            file.write(reinterpret_cast<char*>(&ranking[i]), sizeof(Record));
        }
        file.close();
    }
}

// 랭킹 출력
void showRanking() {
    cout << "\n🎖️ 랭킹 보드 🎖️\n";
    loadRanking();
    if (ranking.empty()) {
        cout << "아직 기록이 없습니다.\n";
    } else {
        for (size_t i = 0; i < ranking.size(); i++) {
            cout << i + 1 << ". " << ranking[i].name << " - " << ranking[i].time << "초\n";
        }
    }
}

// 게임 실행
void playGame() {
    shufflePuzzle(); // 게임 시작 전 퍼즐 섞기
    printPuzzle();

    time_t start_time = time(nullptr); // 시작 시간 기록

    while (true) {
        cout << "WASD로 조각 이동 (Q: 종료): ";
        char move;
        cin >> move;
        if (move == 'Q' || move == 'q') break;

        moveTile(move);
        printPuzzle();

        if (isSolved()) {
            time_t end_time = time(nullptr);
            double play_time = difftime(end_time, start_time); // 걸린 시간 계산

            cout << "🎉 축하합니다! 퍼즐을 맞췄습니다! 🎉\n";
            cout << "걸린 시간: " << play_time << "초\n";

            // 이름 입력 및 랭킹 저장
            cout << "이름을 입력하세요: ";
            Record newRecord;
            cin >> newRecord.name;
            newRecord.time = play_time;

            // 랭킹에 추가하고 정렬 후 저장
            ranking.push_back(newRecord);
            sort(ranking.begin(), ranking.end(), [](const Record& a, const Record& b) {
                return a.time < b.time;
            });
            saveRanking();

            break;
        }
    }
}

int main() {
    loadRanking();

    while (true) {
        cout << "\n1. 그림 퍼즐 시작\n2. 랭킹 보기\n3. 종료\n선택 (1/2/3): ";
        int choice;
        cin >> choice;

        if (choice == 1) playGame();
        else if (choice == 2) showRanking();
        else if (choice == 3) {
            cout << "게임 종료!" << endl;
            break;
        } else {
            cout << "잘못된 입력입니다!" << endl;
        }
    }
    return 0;
}
