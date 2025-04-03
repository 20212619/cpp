#ifndef P248_3_2_H
#define P248_3_2_H

#include <iostream>

struct MyTime {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
};

// 함수 선언
void addTime(MyTime t1, MyTime t2, MyTime& t3);
void inputTime(MyTime& t);
void printTime(const MyTime& t);

#endif // P248_3_2_H
