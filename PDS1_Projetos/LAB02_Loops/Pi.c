#include <math.h>
#include <stdio.h>

int main()
{
    double max_diferenca, resultado = 4;
    int iteracoes = 1;
    scanf("%lf", &max_diferenca);

    for (double i = 3; fabs(resultado - M_PI) > max_diferenca; i += 2)
    {
        if (iteracoes % 2 == 0)
        {
            resultado = resultado + 4 / i;
        }
        else
        {
            resultado = resultado - 4 / i;
        }
        iteracoes++;
    }

    printf("%d\n", iteracoes);

    return 0;
}
