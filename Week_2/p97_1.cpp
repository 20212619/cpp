#include <stdio.h>

int main()
{
    printf("(1) \n");
    for(int i = 1; i <= 5; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            printf("%d ", j);
        }
        printf("\n");
    }

    printf("\n");
    printf("(2) \n");
    for (int i = 1; i <= 5; i++) 
    {
        for (int j = 5; j >= i; j--) 
        {
            printf("%d ", j);
        }
        printf("\n");
    }

    printf("\n");
    printf("(3) \n");
    for (int i = 1; i <= 5; i++) 
    {
        for (int space = 5; space > i; space--) 
        {
            printf("  ");
        }
        for (int j = i; j >= 1; j--) 
        {
            printf(" %d", j);
        }
        printf("\n");

    }

    printf("\n");
    printf("(4) \n");
    for (int i = 1; i <= 5; i++) 
    {
        for (int space = 5; space > i; space--) 
        {
            printf(" ");
        }
        for (int j = i; j >= 1; j--) 
        {
            printf("%d", j);
        }
        for (int j = 2; j <= i; j++) 
        {
            printf("%d", j);
        }
        printf("\n");
    }
    return 0;
}