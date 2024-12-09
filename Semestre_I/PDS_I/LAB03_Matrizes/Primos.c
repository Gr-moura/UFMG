#include <math.h>
#include <stdio.h>

int main()
{
    int inicio, fim, ehprimo = 0;
    scanf("%d %d", &inicio, &fim);
    if (inicio % 2 == 0)
        inicio = inicio - 1;
    if (inicio + 1 == 2)
        printf("2\n");

    for (int i = inicio + 2; i < fim; i += 2)
    {
        ehprimo = 1;
        if (i % 2 == 0)
            continue;

        for (int n = 3; n < (int)sqrt(i) + 1; n += 2)
        {
            if (i % n == 0)
            {
                ehprimo = 0;
                break;
            }
        }
        if (ehprimo)
            printf("%d\n", i);
    }

    return 0;
}
