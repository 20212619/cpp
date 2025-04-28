#ifndef P348_2_H
#define P348_2_H

class MyTime {
private:
    int hour; // 시간
    int min;  // 분
    int sec;  // 초
    int msec; // 밀리초

public:
    MyTime();                      // 기본 생성자
    MyTime(int h, int m, int s, int ms); // 시, 분, 초, 밀리초 생성자
    MyTime(double duration);            // 초 단위 실수형 생성자

    void convert(double duration); // 초를 시:분:초:밀리초로 변환
    void print();                  // 시간 출력
    MyTime add(MyTime t);           // 두 시간 더하기
    void reset();                  // 시간 초기화
    void read();                   // 사용자 입력 받기
};

// 추가: 메인 루틴 run() 함수 선언
void run();

#endif
