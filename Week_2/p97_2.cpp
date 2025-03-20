#include <stdio.h>

int main() {
    int num;
    printf("(1)\n");
    printf("5 digit positive number: ");
    scanf("%d", &num);

    if (num < 10000 || num > 99999) {
        printf("input error\n");
        return 1;
    }

    int ten_thousand = num / 10000;
    int thousand = (num / 1000) % 10;
    int hundred = (num / 100) % 10;
    int ten = (num / 10) % 10;
    int one = num % 10;

    if (ten_thousand > 0) {
        printf("%d만 ", ten_thousand);
    }
    if (thousand > 0) {
        printf("%d천 ", thousand);
    }
    if (hundred > 0) {
        printf("%d백 ", hundred);
    }
    if (ten > 0) {
        printf("%d십 ", ten);
    }
    if (one > 0) {
        printf("%d", one);
    }

    printf("\n\n(2)\n");
    printf("5 digit positive number: ");
    scanf("%d", &num);

    ten_thousand = num / 10000;
    thousand = (num / 1000) % 10;
    hundred = (num / 100) % 10;
    ten = (num / 10) % 10;
    one = num % 10;

    if (ten_thousand != 0) 
    {
        printf("%d만 ", ten_thousand);
    }
    if (thousand != 0) {
        printf("%d천 ", thousand);
    }
    if (hundred != 0) {
        printf("%d백 ", hundred);
    }
    if (ten != 0) {
        printf("%d십 ", ten);
    }
    if (one != 0) {
        printf("%d", one);
    }

    printf("\n\n(3)\n");
    printf("5 digit positive number: ");
    scanf("%d", &num);

    ten_thousand = num / 10000;
    thousand = (num / 1000) % 10;
    hundred = (num / 100) % 10;
    ten = (num / 10) % 10;
    one = num % 10;

    if (ten_thousand > 0) {
        printf("만 "); // 만 단위는 숫자 없이 "만"만 출력
    }
    if (thousand > 0) {
        printf("%d천 ", thousand); // 천 단위는 숫자 출력
    }
    if (hundred > 0) {
        printf("백 "); // 백 단위는 숫자 없이 "백"만 출력
    }
    if (ten > 0) {
        printf("%d십 ", ten); // 십 단위는 숫자 출력
    }
    if (one > 0) {
        printf("%d", one); // 일 단위는 숫자 출력
    }
    
    return 0;
}