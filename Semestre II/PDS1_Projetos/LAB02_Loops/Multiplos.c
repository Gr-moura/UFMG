#include <stdio.h>
int main()
{
    int x, maior2 = 0, maior3 = 0, maior5 = 0, maiort = 0;
    scanf("%d ", &x);
    x = x + 1;
    while (x % 2 || x % 3 || x % 5 && x > 1)
    {
        x = x - 1;
        if (x % 2 == 0 && x > maior2)
        {
            maior2 = x;
        }
        if (x % 3 == 0 && x > maior3)
        {
            maior3 = x;
        }
        if (x % 5 == 0 && x > maior5)
        {
            maior5 = x;
        }
        if (x % 2 == 0 && x % 3 == 0 && x % 5 == 0)
        {
            maiort = x;
        }
    }
    printf("Múltiplos de 2: %d\nMúltiplos de 3: %d\nMúltiplos de 5: %d\nMúltiplos de todos: %d\n", maior2 / 2,
           maior3 / 3, maior5 / 5, maiort / 30);

    return 0;
}
