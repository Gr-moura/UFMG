#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int idade;
    char telefone[20];

} contato_t;

typedef contato_t agenda_t[100];

int main(int argc, char **argv)
{
    agenda_t agenda;
    contato_t blank = {"", 0, ""};

    char nome[100];
    scanf("%s", nome);

    FILE *file = fopen(nome, "rb");
    FILE *out = fopen("out.txt", "w");

    if (file == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    char c;
    int pessoa_inserida = 0;

    int pessoa_atual;
    char temp_nome[100];
    char comando[100], dados[100];
    char mensagem[200];

    int achou;

    do
    {
        if (fgets(comando, 100, file) == NULL)
            break;
        comando[strlen(comando) - 1] = '\0';

        if (!strcmp(comando, "Inserir"))
        {
            if (fgets(dados, 100, file) == NULL)
                break;

            if (pessoa_inserida >= 100)
            {
                printf("Espaco insuficiente\n");
                continue;
            }

            sscanf(dados, "%s %d %s", agenda[pessoa_inserida].nome, &agenda[pessoa_inserida].idade,
                   agenda[pessoa_inserida].telefone);
            printf("Registro %s %d %s inserido\n", agenda[pessoa_inserida].nome, agenda[pessoa_inserida].idade,
                   agenda[pessoa_inserida].telefone);

            pessoa_inserida++;
        }

        else if (!strcmp(comando, "Excluir"))
        {
            if (fgets(dados, 100, file) == NULL)
                break;
            sscanf(dados, "%s", temp_nome);

            achou = 0;
            for (int p = 0; p < pessoa_inserida; p++)
            {
                if (!strcmp(agenda[p].nome, temp_nome))
                {
                    pessoa_atual = p;
                    achou = 1;
                    break;
                }
            }

            if (achou == 0)
            {
                printf("Registro %s invalido\n", temp_nome);
                continue;
            }

            printf("Registro %s %d %s excluido\n", agenda[pessoa_atual].nome, agenda[pessoa_atual].idade,
                   agenda[pessoa_atual].telefone);

            agenda[pessoa_atual] = agenda[pessoa_inserida - 1];
            agenda[pessoa_inserida - 1] = blank;
            pessoa_inserida--;
        }

        else if (!strcmp(comando, "Alterar"))
        {
            if (fgets(dados, 100, file) == NULL)
                break;
            sscanf(dados, "%s", temp_nome);

            achou = 0;
            for (int p = 0; p < pessoa_inserida; p++)
            {
                if (!strcmp(agenda[p].nome, temp_nome))
                {
                    pessoa_atual = p;
                    achou = 1;
                    break;
                }
            }

            if (achou == 0)
            {
                printf("Registro %s invalido\n", temp_nome);
                continue;
            }

            printf("Registro %s %d %s alterado\n", agenda[pessoa_atual].nome, agenda[pessoa_atual].idade,
                   agenda[pessoa_atual].telefone);
            sscanf(dados, "%s %d %s", agenda[pessoa_atual].nome, &agenda[pessoa_atual].idade,
                   agenda[pessoa_atual].telefone);
        }

        else if (!strcmp(comando, "Exibir"))
        {
            fgets(dados, 100, file);
            sscanf(dados, "%s", temp_nome);

            achou = 0;
            for (int p = 0; p < pessoa_inserida; p++)
            {
                if (!strcmp(agenda[p].nome, temp_nome))
                {
                    pessoa_atual = p;
                    achou = 1;
                    break;
                }
            }

            if (achou == 0)
            {
                printf("Registro %s invalido\n", temp_nome);
                continue;
            }

            printf("Registro %s %d %s exibido\n", agenda[pessoa_atual].nome, agenda[pessoa_atual].idade,
                   agenda[pessoa_atual].telefone);
        }
    } while (strlen(comando) > 0);

    fclose(file);

    return EXIT_SUCCESS;
}
