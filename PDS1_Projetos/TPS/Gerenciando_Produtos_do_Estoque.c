#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define MAX_BUFFER 200

typedef struct
{
    unsigned int ID;
    char nome[50];
    char departamento[50];
    double preco;

} Produto_t;

typedef struct reg
{
    Produto_t produto;

    struct reg *esq;
    struct reg *dir;

} noh_t;

void Printar_noh(const noh_t *noh)
{
    printf("(%s) %s - R$ %.2lf\n", noh->produto.departamento, noh->produto.nome, noh->produto.preco);
}

noh_t *Achar_espaco(noh_t *raiz, const int ID)
{
    noh_t *Espaco_encontrado;

    if (ID < raiz->produto.ID && raiz->esq == NULL)
    {
        raiz->esq = calloc(1, sizeof(noh_t));
        return raiz->esq;
    }

    if (ID > raiz->produto.ID && raiz->dir == NULL)
    {
        raiz->dir = calloc(1, sizeof(noh_t));
        return raiz->dir;
    }

    if (ID < raiz->produto.ID && raiz->esq != NULL)
        if ((Espaco_encontrado = Achar_espaco(raiz->esq, ID)) != NULL)
            return Espaco_encontrado;

    if (ID > raiz->produto.ID && raiz->dir != NULL)
        if ((Espaco_encontrado = Achar_espaco(raiz->dir, ID)) != NULL)
            return Espaco_encontrado;

    return NULL;
}

void Inicializar_Noh(noh_t *Novo_noh, char *buffer)
{
    sscanf(buffer, "%u %s %s %lf", &Novo_noh->produto.ID, Novo_noh->produto.nome, Novo_noh->produto.departamento,
           &Novo_noh->produto.preco);
}

noh_t *Ler_input(FILE *input)
{
    char buffer[MAX_BUFFER];
    unsigned int ID;

    noh_t *raiz = calloc(1, sizeof(noh_t));

    fgets(buffer, MAX_BUFFER, input);
    Inicializar_Noh(raiz, buffer);

    noh_t *Novo;
    while (fgets(buffer, MAX_BUFFER, input) != NULL)
    {
        sscanf(buffer, "%u", &ID);

        Novo = Achar_espaco(raiz, ID);
        Inicializar_Noh(Novo, buffer);
    }

    return raiz;
}

void Liberdade(noh_t *raiz)
{
    if (raiz->esq != NULL)
        Liberdade(raiz->esq);

    if (raiz->dir != NULL)
        Liberdade(raiz->dir);

    free(raiz);
}

int Procurar_por_ID(const noh_t *raiz, const int ID)
{
    if (ID == raiz->produto.ID)
    {
        Printar_noh(raiz);
        return true;
    }

    if (ID < raiz->produto.ID)
    {
        if (raiz->esq == NULL)
            return false;

        if ((Procurar_por_ID(raiz->esq, ID)) == true)
            return true;
    }

    if (ID > raiz->produto.ID)
    {
        if (raiz->dir == NULL)
            return false;

        if (Procurar_por_ID(raiz->dir, ID) == true)
            return true;
    }

    return false;
}

void Procurar_por_Departamento()
{
}

void Inserir_Produto()
{
}

void Filtrar_Produtos_por_Preco()
{
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Está faltando o arquivo de input");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    noh_t *raiz = Ler_input(file);

    char buffer[MAX_BUFFER];
    int comando = 0;
    while (comando != 5)
    {
        fgets(buffer, MAX_BUFFER, stdin);
        sscanf(buffer, "%d", &comando);
    }

    for (int i = 0; i < 100; i++)
        Procurar_por_ID(raiz, i);

    Liberdade(raiz);

    return EXIT_SUCCESS;
}
