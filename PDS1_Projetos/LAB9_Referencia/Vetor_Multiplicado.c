#include <stdio.h>

void imprime(int vetor[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);

    printf("\n");
}

void multiplica(int vetor[], int n, double v)
{
    for (int i = 0; i < n; i++)
        vetor[i] *= v;
}

int main()
{
    int n;
    scanf("%d ", &n);

    int vetor[n];

    for (int i = 0; i < n; i++)
        scanf("%d ", &vetor[i]);

    double v;
    scanf("%lf", &v);

    imprime(vetor, n);

    multiplica(vetor, n, v);

    imprime(vetor, n);

    multiplica(vetor, n, 1 / v);

    imprime(vetor, n);

    return 0;
}
