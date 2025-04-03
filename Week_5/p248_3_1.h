#ifndef P248_3_1_H
#define P248_3_1_H

#include <iostream>

struct MyTime {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
};

// 함수 선언
MyTime addTime(MyTime t1, MyTime t2);
MyTime inputTime();
void printTime(MyTime t);

#endif // P248_3_1_H
