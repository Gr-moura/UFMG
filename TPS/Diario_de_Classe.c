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

void Ler_input(FILE *file, prof *professor)
{
    fgets(professor->nome, 100, file);
    fscanf(file, "%d ", &professor->registro);

    int turmas;
    fscanf(file, "%d ", &turmas);

    for (int i = 0; i < turmas; i++)
    {
        fgets(professor->turmas[i].nome, 100, file);
        fgets(professor->turmas[i].codigo, 100, file);
    }

    int alunos;

    for (int i = 0; i < turmas; i++)
    {
        fscanf(file, "%d ", &alunos);
        for (int j = 0; j < alunos; j++)
        {
            fgets(professor->turmas[i].alunos[j].nome, 100, file);
            fscanf(file, "%d ", &professor->turmas[i].alunos[j].matricula);
        }
    }

    /*TODO: Deletar o seguinte antes de enviar
 *
    printf("%s", professor->nome);
    printf("%d", professor->registro);

    for (int i = 0; i < turmas; i++)
    {
        printf("%s", professor->turmas[i].nome);
        printf("%s", professor->turmas[i].codigo);
        printf("%s", professor->turmas[i].alunos[0].nome);
        printf("%d\n", professor->turmas[i].alunos[0].matricula);
        printf("%s", professor->turmas[i].alunos[1].nome);
        printf("%d\n", professor->turmas[i].alunos[1].matricula);
        printf("%s", professor->turmas[i].alunos[2].nome);
        printf("%d\n", professor->turmas[i].alunos[2].matricula);
    }*/
}

void Imprimir_menu(prof *professor)
{
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
    // TODO: retirar o que esta comentado
    //
    /*if (argc < 3)
    {
        printf("Está faltando coisa!");
        return 0;
    }*/

    // FILE *input = fopen(argv[1], "r");

    FILE *input = fopen("input.txt", "r");
    if (input == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    /*FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);

        perror("Error");
        return EXIT_FAILURE;
    }*/

    prof professor;

    Ler_input(input, &professor);

    // TODO: fazer imprimir_menu
    Imprimir_menu(&professor);

    fclose(input);
    // fclose(output);
    return EXIT_SUCCESS;
}
