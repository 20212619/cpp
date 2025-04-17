#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;

    // 3. 멤버 함수 (void)
    void add(Complex& a, Complex& b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
    }

    // 4. 멤버 함수 (값 반환)
    Complex add(Complex& b) {
        Complex result;
        result.real = real + b.real;
        result.imag = imag + b.imag;
        return result;
    }

    // 5. 연산자 오버로딩
    Complex operator+(Complex& b) {
        Complex result;
        result.real = real + b.real;
        result.imag = imag + b.imag;
        return result;
    }

    void print() {
        cout << "(" << real << ", " << imag << "i)" << endl;
    }
};

// 1. 일반 함수 (void, 참조 전달)
void add(Complex& a, Complex& b, Complex& c) {
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
}

// 2. 일반 함수 (값 반환)
Complex add(Complex a, Complex b) {
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

int main() {
    Complex a = {1.0, 2.0};
    Complex b = {3.0, 4.0};

    cout << "1. 일반 함수 (void): ";
    Complex c1;
    add(a, b, c1);
    c1.print();

    cout << "2. 일반 함수 (return): ";
    Complex c2 = add(a, b);
    c2.print();

    cout << "3. 멤버 함수 (void): ";
    Complex c3;
    c3.add(a, b);
    c3.print();

    cout << "4. 멤버 함수 (return): ";
    Complex c4 = a.add(b);
    c4.print();

    cout << "5. 연산자 오버로딩: ";
    Complex c5 = a + b;
    c5.print();

    return 0;
}
