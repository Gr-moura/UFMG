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

void Inicializar_Noh(noh_t *Novo_noh, const char *buffer)
{
    sscanf(buffer, "%u %49s %49s %lf", &Novo_noh->produto.ID, Novo_noh->produto.nome, Novo_noh->produto.departamento,
           &Novo_noh->produto.preco);
}

noh_t *Ler_input(FILE *input)
{
    char buffer[MAX_BUFFER];
    unsigned int ID;

    noh_t *raiz = calloc(1, sizeof(noh_t));

    fgets(buffer, MAX_BUFFER, input);
    Inicializar_Noh(raiz, buffer);

    while (fgets(buffer, MAX_BUFFER, input) != NULL)
    {
        sscanf(buffer, "%u", &ID);

        noh_t *Novo = Achar_espaco(raiz, ID);
        Inicializar_Noh(Novo, buffer);
    }

    fclose(input);

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

int Encontrar_ID(noh_t *raiz, const int ID)
{
    Printar_noh(raiz);

    if (ID == raiz->produto.ID)
        return true;

    if (ID < raiz->produto.ID)
    {
        if (raiz->esq == NULL)
            return false;

        if (Encontrar_ID(raiz->esq, ID) == true)
            return true;
    }

    if (ID > raiz->produto.ID)
    {
        if (raiz->dir == NULL)
            return false;

        if (Encontrar_ID(raiz->dir, ID) == true)
            return true;
    }

    return false;
}

void Procurar_por_ID(noh_t *raiz)
{
    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    int ID;
    sscanf(buffer, "%d", &ID);

    if (Encontrar_ID(raiz, ID) == false)
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
    sscanf(buffer, "%49s", Departamento);

    if (Produtos_Departamento(raiz, Departamento) == 0)
        printf("Departamento vazio!\n");
}

void Inserir_Produto(noh_t *raiz)
{
    unsigned int ID;

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    sscanf(buffer, "%u", &ID);

    noh_t *Novo = Achar_espaco(raiz, ID);
    Inicializar_Noh(Novo, buffer);
}

int compare(const void *a, const void *b)
{
    // Converte os ponteiros genericos para ponteiros para ponteiros do tipo noh_t
    const noh_t *no_a = *(const noh_t **)a;
    const noh_t *no_b = *(const noh_t **)b;

    // Compara os precos dos produtos
    if (no_a->produto.preco < no_b->produto.preco)
        return -1;

    if (no_a->produto.preco > no_b->produto.preco)
        return 1;

    return 0;
}

void Adicionar_no_Vetor(noh_t ***vet, int *tamanho, noh_t *add)
{
    *vet = realloc(*vet, (*tamanho + 1) * sizeof(noh_t *));
    (*vet)[*tamanho] = add;
    (*tamanho)++;
}

void Procurar_Preco(noh_t *raiz, double preco, noh_t ***vet, int *tamanho)
{
    if (raiz->esq != NULL)
        Procurar_Preco(raiz->esq, preco, vet, tamanho);

    if ((int)(raiz->produto.preco * 100) <= (int)(preco * 100))
    {
        Adicionar_no_Vetor(vet, tamanho, raiz);
    }

    if (raiz->dir != NULL)
        Procurar_Preco(raiz->dir, preco, vet, tamanho);
}

void Filtrar_Produtos_por_Preco(noh_t *raiz)
{
    noh_t **vet = NULL;
    int tamanho = 0;

    double preco;

    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin);

    sscanf(buffer, "%lf", &preco);

    Procurar_Preco(raiz, preco, &vet, &tamanho);

    qsort(vet, tamanho, sizeof(noh_t *), compare);

    for (int i = 0; i < tamanho; i++)
        Printar_noh(vet[i]);

    if (tamanho == 0)
        printf("Sem resultados para o filtro!");

    free(vet);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Esta faltando o arquivo de input");
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
        case 1:
            Procurar_por_ID(raiz);
            break;

        case 2:
            Procurar_por_Departamento(raiz);
            break;

        case 3:
            Inserir_Produto(raiz);
            break;

        case 4:
            Filtrar_Produtos_por_Preco(raiz);
            break;
        }
    }

    Liberdade(raiz);

    return EXIT_SUCCESS;
}
