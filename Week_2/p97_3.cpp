#include <iostream>

// π 근삿값을 계산하는 함수
double calculatePi(int n) {
    double pi = 0.0;  // 초기값 설정

    for (int k = 1; k <= n; k++) {
        pi += 1.0 / (2 * k - 1) - 1.0 / (2 * k + 1);
    }

    return 4 * pi;  // 최종적으로 4를 곱하여 π의 근삿값 반환
}

int main() {
    int n;

    // 사용자 입력 받기
    std::cout << "정수 n을 입력하세요: ";
    std::cin >> n;

    // n이 1 미만이면 오류 메시지 출력 후 종료
    if (n < 1) {
        std::cout << "n은 1 이상의 정수여야 합니다." << std::endl;
        return 1;
    }

    double approxPi = calculatePi(n);  // π 근삿값 계산

    std::cout << std::fixed;  // 고정 소수점 표기
    std::cout.precision(15);  // 소수점 15자리까지 출력
    std::cout << "근사값: " << approxPi << std::endl;

    return 0;
}