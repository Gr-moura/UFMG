#include <stdio.h>
#include <stdlib.h>

void ler_elementos(int vet[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vet[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int *vet = (int *)malloc(n * sizeof(int));

    ler_elementos(vet, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d \n", vet[i]);
    }

    free(vet);
    return 0;
}
