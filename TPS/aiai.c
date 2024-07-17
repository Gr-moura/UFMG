#include <stdio.h>

double modulo(double x)
{
    if (x >= 0)
        return (x);

    else
        return (-x);
}

void media(double vet[], int n, int *i)
{
    double soma = 0, media = 0, dif = 0, menor_dif;
    int posicao;
    for (int j = 0; j < n; j++)
    {
        soma += vet[j];
    }
    media = soma / n;
    menor_dif = soma;

    for (int j = 0; j < n; j++)
    {
        dif = modulo(media - vet[j]);
        if (dif < menor_dif)
        {
            menor_dif = dif;
            posicao = j;
        }
    }
    *i = posicao;
}

int main()
{
    int n;
    int *i;

    printf("i: %d\n", *i);
    scanf("%d", &n);
    printf("i: %d\n", *i);

    double vet[100];
    printf("i: %p\n vet: %p", i, vet);

    for (int j = 0; j < n; j++)
    {
        scanf("%lf", &vet[j]);
    }

    media(vet, n, i);
    printf("%d", *i);

    return 0;
}
