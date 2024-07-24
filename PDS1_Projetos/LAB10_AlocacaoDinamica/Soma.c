#include <stdio.h>
#include <stdlib.h>

int *criar_vetor(int n)
{
    int *vetor_criado = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vetor_criado[i]);
    }
    return vetor_criado;
}

int *soma(int v1[], int v2[], int n)
{
    int *v3 = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    return v3;
}

void printar(int vet[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", vet[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int *v1 = criar_vetor(n);
    int *v2 = criar_vetor(n);

    int *v3 = soma(v1, v2, n);

    printar(v3, n);

    free(v1);
    free(v2);
    free(v3);

    return EXIT_SUCCESS;
}
