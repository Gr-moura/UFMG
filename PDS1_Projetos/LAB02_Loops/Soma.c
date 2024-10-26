#include <stdio.h>
int main()
{
    int x, soma = 0;
    scanf("%d ", &x);

    for (int i = 1; i <= x; i++)
    {
        soma = soma + i;
    }
    printf("%d", soma);

    return 0;
}
