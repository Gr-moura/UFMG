#include <stdio.h>
int main()
{
    int quantia;
    scanf("%d ", &quantia);
    printf("100: %d\n", quantia / 100);
    quantia = quantia % 100;
    printf("50: %d\n", quantia / 50);
    quantia = quantia % 50;
    printf("20: %d\n", quantia / 20);
    quantia = quantia % 20;
    printf("10: %d\n", quantia / 10);
    quantia = quantia % 10;
    printf("5: %d\n", quantia / 5);
    quantia = quantia % 5;
    printf("2: %d\n", quantia / 2);
    quantia = quantia % 2;
    printf("1: %d\n", quantia);

    return 0;
}
