#ifndef P248_3_3_H
#define P248_3_3_H

#include <iostream>

struct MyTime {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
};

// 함수 선언 (포인터 전달 방식)
void addTime(const MyTime* t1, const MyTime* t2, MyTime* t3);
void inputTime(MyTime* t);
void printTime(const MyTime* t);

#endif // P248_3_3_H
