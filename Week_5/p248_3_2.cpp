#include "p248_3_2.h"

// 두 개의 시간을 더하는 함수 정의 (참조 전달 방식)
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    t3.milliseconds = t1.milliseconds + t2.milliseconds;
    t3.seconds = t1.seconds + t2.seconds + t3.milliseconds / 1000;
    t3.milliseconds %= 1000;

    t3.minutes = t1.minutes + t2.minutes + t3.seconds / 60;
    t3.seconds %= 60;

    t3.hours = t1.hours + t2.hours + t3.minutes / 60;
    t3.minutes %= 60;
}

// 시간을 입력받는 함수 정의
void inputTime(MyTime& t) {
    std::cout << "시간(시간 분 초 밀리초)을 입력하세요: ";
    std::cin >> t.hours >> t.minutes >> t.seconds >> t.milliseconds;
}

// 시간을 출력하는 함수 정의
void printTime(const MyTime& t) {
    std::cout << "결과: " << t.hours << "시간 "
              << t.minutes << "분 "
              << t.seconds << "초 "
              << t.milliseconds << "밀리초\n";
}

int main() {
    MyTime t1, t2, t3;

    std::cout << "첫 번째 시간을 입력하세요.\n";
    inputTime(t1);

    std::cout << "두 번째 시간을 입력하세요.\n";
    inputTime(t2);

    addTime(t1, t2, t3);

    std::cout << "두 시간을 합한 결과:\n";
    printTime(t3);

    return 0;
}
