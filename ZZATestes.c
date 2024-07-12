#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Inserir 1
#define Excluir 3
#define Exibir 4

struct data
{
    char nome[50];
    int idade;
    char telefone[500];
};

char comparacao(char *buffer)
{
    if (!strcmp(buffer, "Inserir"))
        return Inserir;
    else if (!strcmp(buffer, "Excluir"))
        return Excluir;
    else if (!strcmp(buffer, "Exibir"))
        return Exibir;
    return 0;
}

void inserir(struct data data[], int *count)
{
    char temp[100];
    fgets(temp, sizeof(temp), stdin);
    if (*count >= 100)
        printf("Espaco insuficiente\n");

    sscanf(temp, "%s %d %s", data[*count].nome, &data[*count].idade, data[*count].telefone);
    printf("Registro %s %d %s inserido\n", data[*count].nome, data[*count].idade, data[*count].telefone);
    (*count)++;
}

void excluir(struct data data[], int *count)
{
    char nome[50];
    if (fgets(nome, sizeof(nome), stdin) == NULL)
        return;

    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n')
        nome[len - 1] = '\0';

    for (int i = 0; i < *count; i++)
    {
        if (!strcmp(nome, data[i].nome))
        {
            printf("Registro %s %d %s excluido\n", data[i].nome, data[i].idade, data[i].telefone);
            for (int j = i; j < *count - 1; j++)
                data[j] = data[j + 1];
            (*count)--;
            break;
        }
        else
            printf("Registro %s invalido\n", nome);
    }
}

void exibir(struct data data[], int count)
{
    char input[50];
    scanf("%s", input);
    getchar();
    int aux = 0;

    for (int i = 0; i < count; i++)
    {
        if (!strcmp(input, data[i].nome))
        {
            printf("Registro %s %d %s exibido\n", data[i].nome, data[i].idade, data[i].telefone);
            aux = 1;
            break;
        }
    }
    if (!aux)
        printf("Registro %s invalido\n", input);
}

void carrega_arquivo(const char *filename, struct data data[], int *count)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
        perror("Error: ");
    *count = fread(data, sizeof(struct data), 100, file);
    fclose(file);
}

int main()
{
    struct data data[100];
    char filename[100];
    char buffer[100];
    int count = 0;

    scanf("%s", filename);
    carrega_arquivo(filename, data, &count);

    while (1)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        int operation = comparacao(buffer);

        if (operation == Inserir)
            inserir(data, &count);
        else if (operation == Excluir)
            excluir(data, &count);
        else if (operation == Exibir)
            exibir(data, count);
    }
    return 0;
}
