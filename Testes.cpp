#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a;
    scanf("%d", &a);
    int v[a];

    if (a > 2000)
    {
        return 0;
    }

    for (int i = 0; i < a; i++)
    {
        scanf("%d", &v[i]);
    }

    int max = 0;
    for (int fi = 1; fi <= a; fi++)
    {
        int numero = 0;

        for (int i = 0; i < a; i++)
        {
            if (v[i] >= fi)
            {
                numero++;
            }
            if (numero == fi)
            {
                max = numero;
                break;
            }
        }
    }
    printf("%d\n", max);

    return 0;
}