#include <stdio.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char marca[50];
    double preco;

} dados_t;

typedef struct
{
    char nome[50];
    double soma;
    double quantidade;

} marca_t;

typedef dados_t produtos_t[8];
typedef marca_t marcas_t[8];

int main()
{
    produtos_t produtos;
    marcas_t marcas;
    char buffer[100];
    double total = 0;
    int qt_marcas = 0;
    int igual;

    
    for (int i = 0; i < 8; i++)
    {
        fgets(buffer, 100, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        sscanf(buffer, "%s %s %lf ", produtos[i].nome, produtos[i].marca, &produtos[i].preco);
        
        igual = 0;
        for (int j = 0; j < qt_marcas; j++)
        {
            if (!strcmp(produtos[i].marca, marcas[j].nome))
            {
                marcas[j].quantidade++;
                marcas[j].soma += produtos[i].preco;
                igual = 1;
                break;
            }
        }
        if (!igual)
        {
            strcpy(marcas[qt_marcas].nome, produtos[i].marca);
            marcas[qt_marcas].quantidade = 1;
            marcas[qt_marcas].soma += produtos[i].preco; 
            qt_marcas ++;
        }

        total += produtos[i].preco;
    }

    // numero de produtos por marca
    for (int i = 0; i < qt_marcas; i++)
    {
        printf("%s %d\n", marcas[i].nome, (int)marcas[i].quantidade);
    }

    // preco medio total dos produtos
    printf("media total %.2lf\n", total / 8);

    // preco medio por marca
    for (int i = 0; i < qt_marcas; i++)
    {
        printf("media %s %.2lf\n", marcas[i].nome, (double) marcas[i].soma/marcas[i].quantidade);
    }
    return 0;
}
