#include <iostream>
#include <string>

class AccountException {
    std::string message;
    int amount;

public:
    AccountException(const std::string& msg, int amt) : message(msg), amount(amt) {}

    std::string what() const { return message; }
    int getAmount() const { return amount; }
};

class CustomerAccount {
    int balance;

public:
    CustomerAccount(int b = 0) : balance(b) {}

    int getBalance() const { return balance; }

    int deposit(int amount) {
        if (amount <= 0)
            throw AccountException("입금 금액이 0 이하입니다.", amount);
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount > balance)
            throw AccountException("잔액보다 큰 금액을 출금하려고 했습니다.", amount);
        balance -= amount;
        return balance;
    }
};

int main() {
    int initial;
    std::cout << "초기 잔액을 입력하세요: ";
    std::cin >> initial;

    CustomerAccount acc(initial);

    try {
        int dep;
        std::cout << "입금할 금액을 입력하세요: ";
        std::cin >> dep;
        acc.deposit(dep);
        std::cout << "입금 후 잔액: " << acc.getBalance() << std::endl;
    }
    catch (const AccountException& e) {
        std::cerr << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << ")" << std::endl;
    }

    try {
        int wd;
        std::cout << "출금할 금액을 입력하세요: ";
        std::cin >> wd;
        acc.withdraw(wd);
        std::cout << "출금 후 잔액: " << acc.getBalance() << std::endl;
    }
    catch (const AccountException& e) {
        std::cerr << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << ")" << std::endl;
    }

    return 0;
}
