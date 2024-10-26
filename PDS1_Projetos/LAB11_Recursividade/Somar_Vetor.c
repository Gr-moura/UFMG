#include <stdio.h>
#include <stdlib.h>

int *ler_vetor(int tam)
{
    int *vet = calloc(tam, sizeof(int));

    for (int i = 0; i < tam; i++)
        scanf("%d ", &vet[i]);

    return vet;
}
int somar(int *vet, int tam)
{
    if (tam == 1)
        return vet[0];

    return somar(vet, tam - 1) + vet[tam - 1];
}

int main()
{
    int tam;
    scanf("%d ", &tam);

    int *vet = ler_vetor(tam);

    printf("%d\n", somar(vet, tam));
    free(vet);

    return 0;
}
