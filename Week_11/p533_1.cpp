#include <iostream>

class TimeHMS {
    int hour, min, sec;

    void normalize() {
        min += sec / 60;
        sec = sec % 60;
        if (sec < 0) {
            sec += 60;
            min--;
        }
        hour += min / 60;
        min = min % 60;
        if (min < 0) {
            min += 60;
            hour--;
        }
        if (hour < 0) hour = 0;
    }

public:
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {
        normalize();
    }

    TimeHMS operator+(const TimeHMS& other) {
        TimeHMS result(hour + other.hour, min + other.min, sec + other.sec);
        return result;
    }

    TimeHMS operator-(const TimeHMS& other) {
        TimeHMS result(hour - other.hour, min - other.min, sec - other.sec);
        return result;
    }

    bool operator==(const TimeHMS& other) {
        return hour == other.hour && min == other.min && sec == other.sec;
    }

    bool operator!=(const TimeHMS& other) {
        return !(*this == other);
    }

    TimeHMS& operator++() {
        hour++;
        normalize();
        return *this;
    }

    TimeHMS& operator--() {
        hour--;
        normalize();
        return *this;
    }

    TimeHMS operator++(int) {
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }

    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        sec--;
        normalize();
        return temp;
    }

    int operator[](int index) {
        if (index == 0) return hour;
        if (index == 1) return min;
        if (index == 2) return sec;
        return 0;
    }

    operator int() {
        return hour * 3600 + min * 60 + sec;
    }

    operator double() {
        return hour + min / 60.0 + sec / 3600.0;
    }

    friend TimeHMS operator*(int n, TimeHMS t) {
        TimeHMS result(t.hour * n, t.min * n, t.sec * n);
        return result;
    }

    friend std::istream& operator>>(std::istream& is, TimeHMS& t) {
        char colon;
        is >> t.hour >> colon >> t.min >> colon >> t.sec;
        t.normalize();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, TimeHMS t) {
        if (t.hour < 10) os << "0";
        os << t.hour << ":";
        if (t.min < 10) os << "0";
        os << t.min << ":";
        if (t.sec < 10) os << "0";
        os << t.sec;
        return os;
    }
};

int main() {
    TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3;

    t3 = t1 + t2;
    std::cout << "t1 + t2 = " << t3 << std::endl;

    t3 = t2 - t1;
    std::cout << "t2 - t1 = " << t3 << std::endl;

    std::cout << "t1 == t2: " << (t1 == t2 ? "참" : "거짓") << std::endl;
    std::cout << "t1 != t2: " << (t1 != t2 ? "참" : "거짓") << std::endl;

    ++t1;
    std::cout << "++t1 = " << t1 << std::endl;
    --t1;
    std::cout << "--t1 = " << t1 << std::endl;

    t1++;
    std::cout << "t1++ = " << t1 << std::endl;
    t1--;
    std::cout << "t1-- = " << t1 << std::endl;

    std::cout << "t1[0] = " << t1[0] << ", t1[1] = " << t1[1] << ", t1[2] = " << t1[2] << std::endl;

    std::cout << "(int)t1 = " << (int)t1 << " 초" << std::endl;

    std::cout << "(double)t1 = " << (double)t1 << " 시간" << std::endl;

    t3 = 2 * t1;
    std::cout << "2 * t1 = " << t3 << std::endl;

    std::cout << "시간 입력 (hh:mm:ss): ";
    std::cin >> t3;
    std::cout << "입력 시간: " << t3 << std::endl;

    return 0;
}
