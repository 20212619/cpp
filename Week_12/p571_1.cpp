#include <iostream>
#include <string>

class CustomerAccount {
    int balance;

public:
    CustomerAccount(int b = 0) : balance(b) {}

    int getBalance() const { return balance; }

    int deposit(int amount) {
        if (amount <= 0)
            return -1;   // 에러 코드 -1 반환
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount > balance)
            return -1;   // 에러 코드 -1 반환
        balance -= amount;
        return balance;
    }
};

int main() {
    int initial;
    std::cout << "초기 잔액을 입력하세요: ";
    std::cin >> initial;

    CustomerAccount acc(initial);

    int dep;
    std::cout << "입금할 금액을 입력하세요: ";
    std::cin >> dep;
    int depResult = acc.deposit(dep);
    if (depResult == -1)
        std::cerr << "입금 오류: 입금 금액이 0 이하입니다." << std::endl;
    else
        std::cout << "입금 후 잔액: " << depResult << std::endl;

    int wd;
    std::cout << "출금할 금액을 입력하세요: ";
    std::cin >> wd;
    int wdResult = acc.withdraw(wd);
    if (wdResult == -1)
        std::cerr << "출금 오류: 잔액보다 큰 금액을 출금하려고 했습니다." << std::endl;
    else
        std::cout << "출금 후 잔액: " << wdResult << std::endl;

    return 0;
}
