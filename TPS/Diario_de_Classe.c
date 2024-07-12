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

void ler_input(FILE *file, prof *professor)
{
    char buffer[200];

    fgets(buffer, 200, file);
    sscanf(buffer, "%s", professor->nome);

    printf("%s", professor->nome);
}

void Exibir_prof()
{
}

void Exibir_aluno()
{
}

void Inserir_aluno()
{
}

void Lancar_notas()
{
}

void Exibir_turma()
{
}

void Exibir_situacao()
{
}

void Exportar()
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

    prof professor;

    ler_input(input, &professor);

    return EXIT_SUCCESS;
}
