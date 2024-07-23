#include <stdio.h>
#include <string.h>

typedef struct
{
    char rua[50];
    unsigned int numero;
    char estado[50];

} endereco_t;

typedef struct
{
    char nome[50];
    unsigned int idade;
    float salario;
    endereco_t end;

} pessoa_t;

typedef pessoa_t grupo_t[5];

int main()
{
    grupo_t dados;
    char comando[100];
    int pessoa = 0;

    char procurado[50];
    char info[300];
    int achou = 0;

    do
    {
        fgets(comando, 100, stdin);
        comando[strlen(comando) - 1] = '\0';

        if (!strcmp(comando, "mostrar"))
        {
            fgets(procurado, 50, stdin);
            procurado[strlen(procurado) - 1] = '\0';

            achou = 0;
            for (int i = 0; i < 5; i++)
            {
                if (!strcmp(dados[i].nome, procurado))
                {
                    achou = 1;
                    printf("Registro %s %d %.2f %s %d %s\n", procurado, dados[i].idade, dados[i].salario,
                           dados[i].end.rua, dados[i].end.numero, dados[i].end.estado);
                }
            }

            if (achou == 0)
                printf("Registro ausente\n");
        }

        else if (!strcmp(comando, "inserir"))
        {
            fgets(info, 300, stdin);

            if (pessoa < 5)
            {
                sscanf(info, "%s %d %f %s %d %s", dados[pessoa].nome, &dados[pessoa].idade, &dados[pessoa].salario,
                       dados[pessoa].end.rua, &dados[pessoa].end.numero, dados[pessoa].end.estado);
                printf("Registro %s %d %.2f %s %d %s inserido\n", dados[pessoa].nome, dados[pessoa].idade,
                       dados[pessoa].salario, dados[pessoa].end.rua, dados[pessoa].end.numero,
                       dados[pessoa].end.estado);
                pessoa++;
            }
            else
                printf("Espaco insuficiente\n");
        }

        else if (!strcmp(comando, "alterar"))
        {
            fgets(info, 300, stdin);
            sscanf(info, "%s", procurado);

            achou = 0;
            for (int i = 0; i < 5; i++)
            {
                if (!strcmp(dados[i].nome, procurado))
                {
                    achou = 1; 
                    sscanf(info, "%s %d %f %s %d %s", dados[i].nome, &dados[i].idade, &dados[i].salario,
                    dados[i].end.rua, &dados[i].end.numero, dados[i].end.estado);

                    printf("Registro %s %d %.2f %s %d %s alterado\n", dados[i].nome, dados[i].idade,
                    dados[i].salario, dados[i].end.rua, dados[i].end.numero, dados[i].end.estado);
                }
            }

            if (achou == 0)
                printf("Registro ausente para alteracao\n");

        }

    } while (strlen(comando) > 0);

    return 0;
}
