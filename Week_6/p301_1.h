#ifndef P301_1_H
#define P301_1_H

#include <iostream>
#include <iomanip>

class MyTime {
private:
    int hours, minutes, seconds, milliseconds;

public:
    MyTime(int h = 0, int m = 0, int s = 0, int ms = 0)
        : hours(h), minutes(m), seconds(s), milliseconds(ms) {}

    inline void convert(double duration) {
        hours = static_cast<int>(duration / 3600);
        duration -= hours * 3600;
        minutes = static_cast<int>(duration / 60);
        duration -= minutes * 60;
        seconds = static_cast<int>(duration);
        milliseconds = static_cast<int>((duration - seconds) * 1000);
    }

    inline void print() {
        std::cout << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds << ":"
                  << std::setw(3) << std::setfill('0') << milliseconds << "\n";
    }

    inline MyTime add(MyTime t) {
        MyTime result;
        result.milliseconds = milliseconds + t.milliseconds;
        result.seconds = seconds + t.seconds + result.milliseconds / 1000;
        result.milliseconds %= 1000;

        result.minutes = minutes + t.minutes + result.seconds / 60;
        result.seconds %= 60;

        result.hours = hours + t.hours + result.minutes / 60;
        result.minutes %= 60;

        return result;
    }

    inline void reset() {
        hours = minutes = seconds = milliseconds = 0;
    }

    inline void input() {
        std::cout << "시간(시 분 초 밀리초)을 입력하세요: ";
        std::cin >> hours >> minutes >> seconds >> milliseconds;
    }
};

#endif // P301_1_H

