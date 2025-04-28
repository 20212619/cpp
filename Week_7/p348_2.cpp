#include <iostream>
#include <iomanip>
#include <cmath>
#include "p348_2.h"

using namespace std;

// ----------------- MyTime 클래스 멤버 함수 구현 -----------------

MyTime::MyTime() {
    reset();
}

MyTime::MyTime(int h, int m, int s, int ms) 
    : hour(h), min(m), sec(s), msec(ms) {}

MyTime::MyTime(double duration) {
    convert(duration);
}

void MyTime::convert(double duration) {
    int total_msec = static_cast<int>(round(duration * 1000));
    hour = total_msec / (3600 * 1000);
    total_msec %= 3600 * 1000;
    min = total_msec / (60 * 1000);
    total_msec %= 60 * 1000;
    sec = total_msec / 1000;
    msec = total_msec % 1000;
}

void MyTime::print() {
    cout << setfill('0')
         << setw(2) << hour << ":"
         << setw(2) << min << ":"
         << setw(2) << sec << ":"
         << setw(3) << msec << endl;
}

void MyTime::reset() {
    hour = min = sec = msec = 0;
}

MyTime MyTime::add(MyTime t) {
    MyTime result;
    result.msec = msec + t.msec;
    result.sec = sec + t.sec + result.msec / 1000;
    result.msec %= 1000;
    result.min = min + t.min + result.sec / 60;
    result.sec %= 60;
    result.hour = hour + t.hour + result.min / 60;
    result.min %= 60;
    return result;
}

void MyTime::read() {
    double duration;
    cout << "초 단위 시간(double)을 입력하세요: ";
    cin >> duration;
    convert(duration);
}

// ----------------- 새로 만든 run() 함수 -----------------

void run() {
    MyTime t1, t2, result;

    cout << "[첫 번째 시간 입력]\n";
    t1.read();

    cout << "[두 번째 시간 입력]\n";
    t2.read();

    cout << "\n[입력된 시간]\n";
    cout << "t1: ";
    t1.print();

    cout << "t2: ";
    t2.print();

    result = t1.add(t2);

    cout << "\n[합산 결과]\n";
    result.print();
}

// ----------------- 메인 함수 -----------------

int main() {
    run();
    return 0;
}
