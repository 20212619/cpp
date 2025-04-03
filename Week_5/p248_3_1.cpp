#include "p248_3_1.h"

// 두 개의 시간을 더하는 함수 정의
MyTime addTime(MyTime t1, MyTime t2) {
    MyTime result;
    result.milliseconds = t1.milliseconds + t2.milliseconds;
    result.seconds = t1.seconds + t2.seconds + result.milliseconds / 1000;
    result.milliseconds %= 1000;
    
    result.minutes = t1.minutes + t2.minutes + result.seconds / 60;
    result.seconds %= 60;
    
    result.hours = t1.hours + t2.hours + result.minutes / 60;
    result.minutes %= 60;

    return result;
}

// 시간을 입력받는 함수 정의
MyTime inputTime() {
    MyTime t;
    std::cout << "시간(시간 분 초 밀리초)을 입력하세요: ";
    std::cin >> t.hours >> t.minutes >> t.seconds >> t.milliseconds;
    return t;
}

// 시간을 출력하는 함수 정의
void printTime(MyTime t) {
    std::cout << "결과: " << t.hours << "시간 "
              << t.minutes << "분 "
              << t.seconds << "초 "
              << t.milliseconds << "밀리초\n";
}

int main() {
    std::cout << "첫 번째 시간을 입력하세요.\n";
    MyTime t1 = inputTime();

    std::cout << "두 번째 시간을 입력하세요.\n";
    MyTime t2 = inputTime();

    MyTime result = addTime(t1, t2);

    printTime(result);

    return 0;
}
