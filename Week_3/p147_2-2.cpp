#include <iostream>
using namespace std;

// 함수 프로토타입 선언
int reverse(int num);

// 함수 정의
int reverse(int num) {
    int reversedNum = 0;
    while (num != 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }
    return reversedNum;
}

// main 함수
int main() {
    int num;
    
    cout << "정수를 입력하세요: " << flush;  // 즉시 출력되도록 flush 사용
    cin >> num;

    cout << "Reversed number: " << reverse(num) << endl;
    
    return 0;
}
