#include <stdio.h>
#include <stdlib.h>

void multiply(long long int matA[5][5], long long int matB[5][5], long long int matC[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matC[i][j] = 0;
            for (int k = 0; k < 5; k++)
            {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int main()
{
    char nome[100];
    scanf("%s", nome);

    FILE *file = fopen(nome, "r");

    long long int matA[5][5];
    long long int matB[5][5];

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fscanf(file, "%lld", &matA[i][j]);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fscanf(file, "%lld", &matB[i][j]);
        }
    }

    long long matC[5][5];
    multiply(matA, matB, matC);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%lld ", matC[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    fclose(file);

    return EXIT_SUCCESS;
}
