#include <iostream>
#include <cstring>

using namespace std;

class MySample {
    char* label;             // 객체 이름을 저장할 포인터
    static int totalObjects; // 생성된 전체 객체 수를 저장하는 정적 변수

public:
    // 기본 생성자
    MySample() {
        label = nullptr;     // 아무 이름이 없을 경우 nullptr로 초기화
        totalObjects++;      // 객체가 생성될 때마다 개수 증가
    }

    // 문자열을 인자로 받는 생성자
    MySample(const char* label) {
        this->label = new char[strlen(label) + 1]; // 문자열 길이만큼 메모리 할당
        strcpy(this->label, label);                // 문자열 복사
        totalObjects++;                            // 객체 개수 증가
    }

    // 복사 생성자
    MySample(const MySample& other) {
        if (other.label) {
            this->label = new char[strlen(other.label) + 1];
            strcpy(this->label, other.label);
        } else {
            this->label = nullptr;
        }
        totalObjects++;
    }

    // 소멸자
    ~MySample() {
        delete[] label;  // 동적 메모리 해제
        label = nullptr; // 안전하게 초기화
        totalObjects--;  // 객체 수 감소
    }

    // 현재 객체 수 출력
    static void showTotal() {
        cout << "현재 MySample 객체 수: " << totalObjects << endl;
    }

    // 객체 이름 출력
    void showLabel() const {
        if (label)
            cout << "객체 이름: " << label << endl;
        else
            cout << "이름 없음" << endl;
    }
};

// 정적 변수 초기화
int MySample::totalObjects = 0;

// 메인 함수: 테스트
int main() {
    MySample::showTotal();  // 0

    MySample obj1("Hello");
    obj1.showLabel();       // Hello
    MySample::showTotal();  // 1

    MySample obj2(obj1);
    obj2.showLabel();       // Hello
    MySample::showTotal();  // 2

    return 0;  // 소멸자 호출되면서 totalObjects는 다시 0으로 감소
}
