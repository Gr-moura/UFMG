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

    int quantidade_alunos;
    aluno alunos[6];

} turma;

typedef struct
{
    char nome[100];
    unsigned int registro;

    int quantidade_turmas;
    turma turmas[2];

} prof;

void Ler_input(FILE *file, prof *professor)
{
    fgets(professor->nome, 100, file);
    fscanf(file, "%d ", &professor->registro);

    fscanf(file, "%d ", &professor->quantidade_turmas);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fgets(professor->turmas[i].nome, 100, file);
        fgets(professor->turmas[i].codigo, 100, file);
    }

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fscanf(file, "%d ", &professor->turmas[i].quantidade_alunos);
        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            fgets(professor->turmas[i].alunos[j].nome, 100, file);
            fscanf(file, "%d ", &professor->turmas[i].alunos[j].matricula);
        }
    }

    // TODO: Deletar o seguinte antes de enviar
    ///*
    printf("%s", professor->nome);
    printf("%d\n", professor->registro);
    printf("%d\n", professor->quantidade_turmas);
    printf("%d\n", professor->turmas[0].quantidade_alunos);
    printf("%d\n", professor->turmas[1].quantidade_alunos);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        printf("%s", professor->turmas[i].nome);
        printf("%s", professor->turmas[i].codigo);
        printf("%s", professor->turmas[i].alunos[0].nome);
        printf("%d\n", professor->turmas[i].alunos[0].matricula);
        printf("%s", professor->turmas[i].alunos[1].nome);
        printf("%d\n", professor->turmas[i].alunos[1].matricula);
        printf("%s", professor->turmas[i].alunos[2].nome);
        printf("%d\n", professor->turmas[i].alunos[2].matricula);
    } //*/
}

void Imprimir_menu()
{
    printf("1 - Informacoes do Professor\n");
    printf("2 - Informacoes do Aluno\n");
    printf("3 - Inserir Aluno\n");
    printf("4 - Lancar Notas\n");
    printf("5 - Informacoes da Turma\n");
    printf("6 - Situacao dos Alunos\n");
    printf("7 - Exportar Dados");
}

void Informacoes_do_Professor(prof *professor)
{
    printf("Professor %s", professor->nome);
    printf("Registro numero %d\n", professor->registro);
}

void Informacoes_do_Aluno(prof *professor)
{
}

void Inserir_Aluno(prof *professor)
{
}

void Lancar_Notas(prof *professor)
{
}

void Informacoes_da_Turma(prof *professor)
{
}

void Situacao_dos_Alunos(prof *professor)
{
}

void Exportar_Dados(prof *professor)
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
    Imprimir_menu();
    /*
        int comando;

        do
        {
            scanf("%d", &comando);

            switch (comando)
            {
            case 1:
                Informacoes_do_Professor(&professor);
                break;

            case 2:
                Informacoes_do_Aluno(&professor);
                break;

            case 3:
                Inserir_Aluno(&professor);
                break;

            case 4:
                Lancar_Notas(&professor);
                break;

            case 5:
                Informacoes_da_Turma(&professor);
                break;

            case 6:
                Situacao_dos_Alunos(&professor);
                break;

            case 7:
                Exportar_Dados(&professor);
                break;
            }

        } while (comando != 7);*/

    fclose(input);
    // fclose(output);
    return EXIT_SUCCESS;
}
