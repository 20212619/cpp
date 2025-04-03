#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_WIDTH = 80;
const int MAX_HEIGHT = 40;
static int MineMapMask[MAX_WIDTH][MAX_HEIGHT] = {0};  // 지뢰 맵 (-1: 지뢰, 0 이상: 주변 지뢰 개수)
static bool Revealed[MAX_WIDTH][MAX_HEIGHT] = {false};  // 열린 칸 여부
static bool Flagged[MAX_WIDTH][MAX_HEIGHT] = {false};  // 깃발 표시 여부

// 지뢰 맵 초기화
void initializeMineMap(int width, int height, int mineCount) {
    srand(time(0));
    int placedMines = 0;
    
    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;
        if (MineMapMask[x][y] == 0) {
            MineMapMask[x][y] = -1;
            placedMines++;
        }
    }
}

// 맵 출력
void printMap(int width, int height) {
    cout << "   ";
    for (int x = 0; x < width; x++)
        cout << x % 10 << " ";
    cout << endl;
    
    for (int y = 0; y < height; y++) {
        cout << y % 10 << "  ";
        for (int x = 0; x < width; x++) {
            if (Flagged[x][y]) {
                cout << "P ";  // 깃발 표시
            } else if (!Revealed[x][y]) {
                cout << "# ";  // 닫힌 칸
            } else if (MineMapMask[x][y] == -1) {
                cout << "* ";  // 지뢰
            } else {
                cout << MineMapMask[x][y] << " ";  // 숫자 (주변 지뢰 개수)
            }
        }
        cout << endl;
    }
}

// 셀 오픈 (깃발이 있으면 먼저 제거)
void revealCell(int x, int y, int width, int height) {
    if (x < 0 || x >= width || y < 0 || y >= height || Revealed[x][y]) return;
    
    if (Flagged[x][y]) {  
        Flagged[x][y] = false;
        cout << "🔺 깃발이 제거되었습니다!" << endl;
        return;  
    }

    Revealed[x][y] = true;

    if (MineMapMask[x][y] == -1) {
        cout << "💥 게임 오버! 지뢰를 밟았습니다." << endl;
        exit(0);
    }
}

// 깃발 토글
void toggleFlag(int x, int y) {
    if (Revealed[x][y]) {
        cout << "⚠ 이미 열린 칸에는 깃발을 놓을 수 없습니다!" << endl;
        return;
    }
    Flagged[x][y] = !Flagged[x][y];
}

// 사용자 입력 받기
void getUserInput(int &x, int &y, char &action) {
    cout << "📌 열 번호, 행 번호를 입력하세요: ";
    cin >> x >> y;
    cout << "📌 깃발을 표시하려면 'p'를 입력하세요 (아니면 'o'로 열기): ";
    cin >> action;
}

// 게임 진행
void playGame(int width, int height) {
    int x, y;
    char action;
    while (true) {
        printMap(width, height);
        getUserInput(x, y, action);
        
        if (action == 'p') {
            toggleFlag(x, y);
        } else if (action == 'o') {
            revealCell(x, y, width, height);
        }
    }
}

// 메인 함수
int main() {
    int width, height, mineCount;
    
    cout << "🛠 맵의 가로 크기를 입력하세요 (최대 80): ";
    cin >> width;
    if (width > MAX_WIDTH) width = MAX_WIDTH;
    
    cout << "🛠 맵의 세로 크기를 입력하세요 (최대 40): ";
    cin >> height;
    if (height > MAX_HEIGHT) height = MAX_HEIGHT;
    
    cout << "💣 지뢰 개수를 입력하세요: ";
    cin >> mineCount;
    
    initializeMineMap(width, height, mineCount);
    playGame(width, height);
    
    return 0;
}
