
#include "p348_1.h"

int main() {
    MyTime t1, t2;

    std::cout << "첫 번째 시간을 입력하세요.\n";
    t1.input();

    std::cout << "두 번째 시간을 입력하세요.\n";
    t2.input();

    MyTime result = t1.add(t2);

    std::cout << "합산된 시간: ";
    result.print();

    return 0;
}
