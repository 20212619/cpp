#include <iostream>
using namespace std;

int reverse(int num) {
    int reversedNum = 0;
    while (num != 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }
    return reversedNum;
}

int main() {
    int num;
    
    cout << "정수를 입력하세요: " << flush;  // 즉시 출력되도록 flush 사용
    cin >> num;

    cout << "Reversed number: " << reverse(num) << endl;
    
    return 0;
}
