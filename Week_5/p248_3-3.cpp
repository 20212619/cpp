#include <iostream>

class MyTime {
public:
    int hours, minutes, seconds, milliseconds;

    MyTime(int h = 0, int m = 0, int s = 0, int ms = 0) 
        : hours(h), minutes(m), seconds(s), milliseconds(ms) {}

    void normalize() {
        seconds += milliseconds / 1000;
        milliseconds %= 1000;
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
    }

    void display() const {
        std::cout << hours << "시간 " << minutes << "분 " << seconds 
                  << "초 " << milliseconds << "밀리초\n";
    }

    void input() {
        std::cout << "시간(시 분 초 밀리초) 입력: ";
        std::cin >> hours >> minutes >> seconds >> milliseconds;
        
        // 입력 오류 방지
        while (std::cin.fail()) {
            std::cin.clear();  // 오류 플래그 해제
            std::cin.ignore(100, '\n');  // 입력 버퍼 정리
            std::cout << "잘못된 입력입니다. 다시 입력하세요 (시 분 초 밀리초): ";
            std::cin >> hours >> minutes >> seconds >> milliseconds;
        }
    }
};

// 포인터 매개변수 방식
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    if (pt) {
        pt->hours = t1.hours + t2.hours;
        pt->minutes = t1.minutes + t2.minutes;
        pt->seconds = t1.seconds + t2.seconds;
        pt->milliseconds = t1.milliseconds + t2.milliseconds;
        pt->normalize();
    }
}

int main() {
    MyTime t1, t2, result;

    std::cout << "첫 번째 시간 입력\n";
    t1.input();

    std::cin.ignore(100, '\n');  // 개행 문자 제거

    std::cout << "두 번째 시간 입력\n";
    t2.input();

    addTime(t1, t2, &result);

    std::cout << "더한 결과: ";
    result.display();

    return 0;
}
