#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "p147_6_2.h"  // 헤더 파일 포함

using namespace std;

// 구구단 게임
void playGuguOnce() {
    int a = rand() % 9 + 1;
    int b = rand() % 9 + 1;
    int answer;
    
    cout << a << " x " << b << " = ? ";
    cin >> answer;

    if (answer == a * b) {
        cout << "정답!\n";
    } else {
        cout << "틀렸습니다. 정답: " << a * b << "\n";
    }
}

// 두 자리 수 곱셈 게임
void playMultiplication() {
    int a = rand() % 90 + 10;  
    int b = rand() % 90 + 10;  
    int answer;
    
    cout << a << " x " << b << " = ? ";
    cin >> answer;

    if (answer == a * b) {
        cout << "정답!\n";
    } else {
        cout << "틀렸습니다. 정답: " << a * b << "\n";
    }
}

// 여러 자리 수 덧셈 게임
void playAddition(int digits) {
    int num1 = rand() % (int)pow(10, digits);
    int num2 = rand() % (int)pow(10, digits);
    int answer;
    
    cout << num1 << " + " << num2 << " = ? ";
    cin >> answer;

    if (answer == num1 + num2) {
        cout << "정답!\n";
    } else {
        cout << "틀렸습니다. 정답: " << num1 + num2 << "\n";
    }
}

// 게임 시작 함수
void startGame() {
    srand(time(0));
    int choice;

    while (true) {
        cout << "\n게임을 선택하세요: \n";
        cout << "1: 구구단 게임\n";
        cout << "2: 두 자리 수 곱셈\n";
        cout << "3~9: 해당 자리 수 덧셈\n";
        cout << "0: 종료\n";
        cout << "선택: ";
        cin >> choice;

        if (cin.fail()) {  // 숫자가 아닌 값 입력 방지
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "잘못된 입력입니다. 숫자를 입력하세요.\n";
            continue;
        }

        if (choice == 0) {
            cout << "게임을 종료합니다.\n";
            break;
        } else if (choice == 1) {
            playGuguOnce();
        } else if (choice == 2) {
            playMultiplication();
        } else if (choice >= 3 && choice <= 9) {
            playAddition(choice);
        } else {
            cout << "잘못된 선택입니다. 다시 입력해주세요.\n";
        }
    }
}

// 메인 함수
int main() {
    startGame();
    return 0;
}
