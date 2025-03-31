#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

// 게임 기록을 저장할 구조체
struct GameRecord {
    string playerName;
    int moveCount;
    double timeTaken;
};

// 게임 기록을 비교하는 함수 (이동 횟수 기준으로 비교)
bool compareRecords(const GameRecord& a, const GameRecord& b) {
    return a.moveCount < b.moveCount;  // 이동 횟수가 적을수록 더 좋은 성적
}

class PuzzleGame {
private:
    vector<vector<int>> puzzle;
    vector<vector<char>> charPuzzle;
    int emptyRow, emptyCol;
    int puzzleSize;
    bool isNumberPuzzle;
    int moveCount;
    time_t startTime, endTime;

    vector<GameRecord> ranking;  // 랭킹을 저장하는 벡터
    vector<pair<int, int>> moveHistory;  // 이동 기록 (빈칸의 위치 변화)

    string playerName;  // 플레이어 이름 저장

public:
    PuzzleGame(int size, bool numberPuzzle, const string& name) {
        puzzleSize = size;
        isNumberPuzzle = numberPuzzle;
        playerName = name;
        moveCount = 0;
        time(&startTime);

        if (isNumberPuzzle) {
            puzzle.resize(puzzleSize, vector<int>(puzzleSize));
            generateRandomPuzzle();
        } else {
            charPuzzle.resize(puzzleSize, vector<char>(puzzleSize));
            generateRandomCharPuzzle();
        }

        loadRanking();  // 게임 시작 시 기존 랭킹 불러오기
    }

    void generateRandomPuzzle() {
        vector<int> numbers;
        for (int i = 0; i < puzzleSize * puzzleSize; ++i) {
            numbers.push_back(i);
        }

        random_device rd;
        mt19937 g(rd());
        shuffle(numbers.begin(), numbers.end(), g);

        int index = 0;
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                puzzle[i][j] = numbers[index++];
                if (puzzle[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                }
            }
        }
    }

    void generateRandomCharPuzzle() {
        vector<char> characters;
        for (char c = 'A'; c < 'A' + puzzleSize * puzzleSize; ++c) {
            characters.push_back(c);
        }
        characters.push_back('_');

        random_device rd;
        mt19937 g(rd());
        shuffle(characters.begin(), characters.end(), g);

        int index = 0;
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                charPuzzle[i][j] = characters[index++];
                if (charPuzzle[i][j] == '_') {
                    emptyRow = i;
                    emptyCol = j;
                }
            }
        }
    }

    void printPuzzle() {
        if (isNumberPuzzle) {
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    if (puzzle[i][j] == 0) cout << "_ ";
                    else cout << puzzle[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            for (int i = 0; i < puzzleSize; ++i) {
                for (int j = 0; j < puzzleSize; ++j) {
                    cout << charPuzzle[i][j] << " ";
                }
                cout << endl;
            }
        }
    }

    void move(char direction) {
        int newRow = emptyRow, newCol = emptyCol;
        switch (direction) {
            case 'w': newRow--; break;
            case 's': newRow++; break;
            case 'a': newCol--; break;
            case 'd': newCol++; break;
            default:
                cout << "잘못된 입력입니다!" << endl;
                return;
        }

        if (newRow >= 0 && newRow < puzzleSize && newCol >= 0 && newCol < puzzleSize) {
            if (isNumberPuzzle) {
                swap(puzzle[emptyRow][emptyCol], puzzle[newRow][newCol]);
            } else {
                swap(charPuzzle[emptyRow][emptyCol], charPuzzle[newRow][newCol]);
            }
            emptyRow = newRow;
            emptyCol = newCol;
            moveCount++;
            moveHistory.push_back({emptyRow, emptyCol});  // 이동 기록 추가
        }
    }

    bool isNumberPuzzleComplete() {
        int value = 1;
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                if (i == puzzleSize - 1 && j == puzzleSize - 1) {
                    if (puzzle[i][j] != 0) return false;
                } else {
                    if (puzzle[i][j] != value++) return false;
                }
            }
        }
        return true;
    }

    bool isCharPuzzleComplete() {
        char value = 'A';
        for (int i = 0; i < puzzleSize; ++i) {
            for (int j = 0; j < puzzleSize; ++j) {
                if (i == puzzleSize - 1 && j == puzzleSize - 1) {
                    if (charPuzzle[i][j] != '_') return false;
                } else {
                    if (charPuzzle[i][j] != value++) return false;
                }
            }
        }
        return true;
    }

    void saveRanking() {
        // 기존 랭킹에 이어서 기록을 저장하도록 ios::app 모드 사용
        ofstream file("ranking.txt", ios::app);
        if (file.is_open()) {
            for (const auto& record : ranking) {
                file << "이름: " << record.playerName << ", 이동 횟수: " << record.moveCount << ", 시간: " << record.timeTaken << "초\n";
            }
            file.close();
            cout << "랭킹이 저장되었습니다!" << endl;
        }
    }

    void loadRanking() {
        ifstream file("ranking.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                GameRecord record;
                stringstream ss(line);
                string temp;
                ss >> temp >> record.playerName >> temp >> record.moveCount >> temp >> record.timeTaken >> temp >> temp;
                ranking.push_back(record);
            }
            file.close();
        }
    }

    void saveGameStateAndRanking() {
        // 기존 게임 상태에 이어서 기록을 저장하도록 ios::app 모드 사용
        ofstream file("game_and_ranking.txt", ios::app);
        if (file.is_open()) {
            // 게임 상태 저장
            file << "===== 게임 상태 =====" << endl;
            file << "플레이어 이름: " << playerName << endl;
            file << "퍼즐 크기: " << puzzleSize << endl;
            file << "퍼즐 유형: " << (isNumberPuzzle ? "숫자 퍼즐" : "문자 퍼즐") << endl;
            file << "이동 횟수: " << moveCount << endl;
            file << "빈칸 위치: " << emptyRow << ", " << emptyCol << endl;
            
            file << "===== 퍼즐 상태 =====" << endl;
            if (isNumberPuzzle) {
                for (int i = 0; i < puzzleSize; ++i) {
                    for (int j = 0; j < puzzleSize; ++j) {
                        if (puzzle[i][j] == 0) file << "_ ";
                        else file << puzzle[i][j] << " ";
                    }
                    file << endl;
                }
            } else {
                for (int i = 0; i < puzzleSize; ++i) {
                    for (int j = 0; j < puzzleSize; ++j) {
                        file << charPuzzle[i][j] << " ";
                    }
                    file << endl;
                }
            }

            // 랭킹 순위 저장
            file << "===== 랭킹 =====" << endl;
            sort(ranking.begin(), ranking.end(), compareRecords);
            for (int i = 0; i < ranking.size() && i < 10; ++i) {
                file << "순위 " << i + 1 << ": " << ranking[i].playerName << " - 이동 횟수 " << ranking[i].moveCount << ", 시간 " << ranking[i].timeTaken << "초" << endl;
            }
            file.close();
            cout << "게임 상태와 랭킹이 저장되었습니다!" << endl;
        }
    }

    void endGame() {
        time(&endTime);
        double timeTaken = difftime(endTime, startTime);
        GameRecord record = {playerName, moveCount, timeTaken};
        ranking.push_back(record);
        saveRanking();  // 게임 종료 시 랭킹 저장

        cout << "퍼즐이 완성되었습니다!" << endl;
        cout << "이동 횟수: " << moveCount << endl;
        cout << "게임 시간: " << timeTaken << "초" << endl;

        cout << "리플레이 하시겠습니까? (r: 예, 다른 키: 아니오): ";
        char choice;
        cin >> choice;
        if (choice == 'r') {
            replay();
        }
    }

    void replay() {
        // 초기 상태로 돌아가기 위해 이동 기록을 역순으로 따라감
        cout << "리플레이 시작!" << endl;
        for (auto it = moveHistory.rbegin(); it != moveHistory.rend(); ++it) {
            int r = it->first;
            int c = it->second;
            if (isNumberPuzzle) {
                swap(puzzle[emptyRow][emptyCol], puzzle[r][c]);
            } else {
                swap(charPuzzle[emptyRow][emptyCol], charPuzzle[r][c]);
            }
            emptyRow = r;
            emptyCol = c;
            printPuzzle();
            cout << "========" << endl;
        }
    }
};

int main() {
    string playerName;
    int size;
    char puzzleType;

    cout << "게임 시작 전에 이름을 입력하세요: ";
    cin >> playerName;

    cout << "퍼즐 크기를 선택하세요 (3, 4, 5 중 하나): ";
    cin >> size;

    cout << "숫자 퍼즐(n) 또는 문자 퍼즐(m) 중 하나를 선택하세요: ";
    cin >> puzzleType;

    bool isNumberPuzzle = (puzzleType == 'n');

    PuzzleGame game(size, isNumberPuzzle, playerName);

    while (true) {
        game.printPuzzle();

        if ((isNumberPuzzle && game.isNumberPuzzleComplete()) || 
            (!isNumberPuzzle && game.isCharPuzzleComplete())) {
            game.endGame();
            break;
        }

        cout << "이동(a: 왼, d: 오른, w: 위, s: 아래, r: 리플레이, q: 저장, e: 게임 종료): ";
        char direction;
        cin >> direction;

        if (direction == 'e') {
            cout << "게임을 종료합니다." << endl;
            break;
        } else if (direction == 'q') {
            game.saveGameStateAndRanking();
            cout << "게임이 저장되었습니다." << endl;
            break;
        } else if (direction == 'r') {
            game.replay();
        } else {
            game.move(direction);
        }
    }

    return 0;
}
