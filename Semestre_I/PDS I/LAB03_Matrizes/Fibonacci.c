#include <stdio.h>

int main()
{
    int fibonacci[801];
    int recebido;
    scanf("%d ", &recebido);

    fibonacci[0] = 0, fibonacci[1] = 1;

    for (int i = 2; i <= 800; i++)
    {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    while (recebido >= 0 && recebido <= 800)
    {
        printf("%d\n", fibonacci[recebido]);
        scanf("%d ", &recebido);
    }

    return 0;
}
