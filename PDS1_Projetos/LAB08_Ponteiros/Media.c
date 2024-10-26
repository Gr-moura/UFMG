/*

Faça uma função chamada média que recebe um vetor de double, um inteiro n que
indica o tamanho do vetor, e um inteiro i passado por referência. A função deve
primeiramente calcular a média dos n elementos no vetor. Após isso, a função deve
armazenar no inteiro i, passado por referência, a posição do elemento que tem o valor
mais próximo da média. Cabeçalho: void media(double vet[], int n, int *i);

*/

#include <math.h>
#include <stdio.h>

void media(double vet[], int n, int *i)
{
    *i = -1;
    double media = 0;

    for (int j = 0; j < n; j++)
        media += vet[j];

    media = media / n;

    for (int j = 0; j < n; j++)
    {
        if (*i == -1 || fabs(media - vet[j]) < fabs(media - vet[*i]))
            *i = j;
    }
}

int main()
{
    int ans;

    int qt_valores;
    scanf("%d", &qt_valores);

    double vet[qt_valores];

    for (int i = 0; i < qt_valores; i++)
        scanf("%lf", &vet[i]);

    media(vet, qt_valores, &ans);

    printf("%d", ans);

    return 0;
}
