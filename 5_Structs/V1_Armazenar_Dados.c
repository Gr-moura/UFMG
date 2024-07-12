#include <stdio.h>
#include <string.h>

typedef struct
{
    char nome[50];
    unsigned int idade;
    float salario;
} pessoa_t;

typedef pessoa_t grupo_t[4];

int main()
{
    grupo_t dados;
    char comando[100];
    int pessoa = 0;

    char procurado[50];
    char info[100];
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
            for (int i = 0; i < 4; i++)
            {
                if (!strcmp(dados[i].nome, procurado))
                {
                    achou = 1;
                    printf("Registro %s %d %.2f\n", procurado, dados[i].idade, dados[i].salario);
                }
            }

            if (achou == 0)
                printf("Registro ausente\n");
        }

        else if (!strcmp(comando, "inserir"))
        {
            fgets(info, 100, stdin);

            if (pessoa < 4)
            {
                sscanf(info, "%s %d %f", dados[pessoa].nome, &dados[pessoa].idade, &dados[pessoa].salario);
                printf("Registro %s %d %.2f inserido\n", dados[pessoa].nome, dados[pessoa].idade,
                       dados[pessoa].salario);
                pessoa++;
            }
            else
                printf("Espaco insuficiente\n");
        }

    } while (strlen(comando) > 0);

    return 0;
}
