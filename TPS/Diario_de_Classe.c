#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[100];
    unsigned int matricula;

    int notas[3];

} aluno;

typedef struct
{
    char codigo[10];
    char nome[100];

    aluno alunos[6];

} turma;

typedef struct
{
    char nome[100];
    unsigned int registro;

    turma turmas[2];

} prof;

int Exibir_prof()
{
}

int Exibir_aluno()
{
}

int Inserir_aluno()
{
}

int Lancar_notas()
{
}

int Exibir_turma()
{
}

int Exibir_situacao()
{
}

int Exportar()
{
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Está faltando coisa!");
        return 0;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);

        perror("Error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
