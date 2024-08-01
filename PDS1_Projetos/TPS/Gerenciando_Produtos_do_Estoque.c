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

void Imprimir_Menu()
{
    printf("1 - Procurar por ID\n");
    printf("2 - Procurar por Departamento\n");
    printf("3 - Inserir Produto\n");
    printf("4 - Filtrar por Preco\n");
    printf("5 - Sair\n");
}

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

noh_t *Encontrar_ID(noh_t *raiz, const int ID)
{
    noh_t *Encontrado;

    if (ID == raiz->produto.ID)
        return raiz;

    if (ID < raiz->produto.ID)
    {
        if (raiz->esq == NULL)
            return NULL;

        if ((Encontrado = Encontrar_ID(raiz->esq, ID)) != NULL)
            return Encontrado;
    }

    if (ID > raiz->produto.ID)
    {
        if (raiz->dir == NULL)
            return NULL;

        if ((Encontrado = Encontrar_ID(raiz->dir, ID)) != NULL)
            return Encontrado;
    }

    return false;
}

void Procurar_por_ID(noh_t *raiz)
{
    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    int ID;
    sscanf(buffer, "%d", &ID);

    noh_t *Encontrado;

    if ((Encontrado = Encontrar_ID(raiz, ID)) != NULL)
        Printar_noh(Encontrado);

    else
        printf("Produto nao encontrado!\n");
}

int Produtos_Departamento(noh_t *raiz, const char *Departamento)
{
    int Produtos = 0;

    if (raiz->esq != NULL)
        Produtos += Produtos_Departamento(raiz->esq, Departamento);

    if (!strcmp(raiz->produto.departamento, Departamento))
    {
        Printar_noh(raiz);
        Produtos++;
    }

    if (raiz->dir != NULL)
        Produtos += Produtos_Departamento(raiz->dir, Departamento);

    return Produtos;
}

void Procurar_por_Departamento(noh_t *raiz)
{
    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    char Departamento[50];
    sscanf(buffer, "%s", Departamento);

    if (Produtos_Departamento(raiz, Departamento) == 0)
        printf("Departamento vazio!");
}

void Inserir_Produto(noh_t *raiz)
{
    int ID;

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    sscanf(buffer, "%u", &ID);

    noh_t *Novo = Achar_espaco(raiz, ID);
    Inicializar_Noh(Novo, buffer);
}

void Adicionar_no_Vetor(noh_t **vet, int tamanho, noh_t *add)
{
    vet = realloc(vet, (tamanho + 1) * sizeof(noh_t *));
    vet[tamanho] = add;
}

noh_t **Procurar_Preco(noh_t *raiz, double preco)
{

    if (raiz->esq != NULL)
        Procurar_Preco(raiz->esq, preco);

    if ((int)(raiz->produto.preco * 100) < (int)(preco * 100))
    {
        Printar_noh(raiz);
    }

    if (raiz->dir != NULL)
        Procurar_Preco(raiz->dir, preco);
}

void Filtrar_Produtos_por_Preco(noh_t *raiz)
{
    noh_t **vet = calloc(1, sizeof(noh_t *));

    double preco;

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    sscanf(buffer, "%lf", &preco);

    vet = Procurar_Preco(raiz, preco);

    // qsort(vet, )
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

    Imprimir_Menu();

    char buffer[MAX_BUFFER];
    int comando = 0;
    while (comando != 5)
    {
        fgets(buffer, MAX_BUFFER, stdin);
        sscanf(buffer, "%d", &comando);

        switch (comando)
        {
            /* case 1:
                 Procurar_por_ID(raiz);
                 break;

             case 2:
                 Procurar_por_Departamento(raiz);
                 break;

             case 3:
                 Inserir_Produto(raiz);
                 break;*/

        case 4:
            Filtrar_Produtos_por_Preco(raiz);
            break;
        }
    }

    Liberdade(raiz);

    return EXIT_SUCCESS;
}
