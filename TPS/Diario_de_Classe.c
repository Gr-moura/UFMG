#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[110];
    unsigned int matricula;

    int notas[3];

} aluno;

typedef struct
{
    char codigo[12];
    char nome[110];

    int quantidade_alunos;
    aluno alunos[6];

} turma;

typedef struct
{
    char nome[110];
    unsigned int registro;

    int quantidade_turmas;
    turma turmas[2];

} prof;

void Ler_input(FILE *file, prof *professor)
{
    fgets(professor->nome, 110, file);
    professor->nome[strlen(professor->nome) - 1] = '\0';

    fscanf(file, "%d ", &professor->registro);

    fscanf(file, "%d ", &professor->quantidade_turmas);

    // Nome e código de cada turma
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fgets(professor->turmas[i].nome, 110, file);
        professor->turmas[i].nome[strlen(professor->turmas[i].nome) - 1] = '\0';

        fgets(professor->turmas[i].codigo, 12, file);
        professor->turmas[i].codigo[strlen(professor->turmas[i].codigo) - 1] = '\0';
    }

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fscanf(file, "%d ", &professor->turmas[i].quantidade_alunos);

        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            fgets(professor->turmas[i].alunos[j].nome, 110, file);
            professor->turmas[i].alunos[j].nome[strlen(professor->turmas[i].alunos[j].nome) - 1] = '\0';

            fscanf(file, "%d ", &professor->turmas[i].alunos[j].matricula);

            for (int k = 0; k < 3; k++)
            {
                professor->turmas[i].alunos[j].notas[k] = 0;
            }
        }
    }
}

char Conceito(int nota)
{
    if (nota < 40)
        return 'F';

    if (nota < 59)
        return 'E';

    if (nota < 69)
        return 'D';

    if (nota < 79)
        return 'C';

    if (nota < 89)
        return 'B';

    return 'A';
}

void Imprimir_menu()
{
    printf("1 - Informacoes do Professor\n");
    printf("2 - Informacoes do Aluno\n");
    printf("3 - Inserir Aluno\n");
    printf("4 - Lancar Notas\n");
    printf("5 - Informacoes da Turma\n");
    printf("6 - Situacao dos Alunos\n");
    printf("7 - Exportar Dados\n");
}

void Informacoes_do_Professor(prof *professor)
{
    printf("Professor %s\n", professor->nome);
    printf("Registro numero %d\n", professor->registro);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        printf("Turma %d: %s - %s, %d alunos\n", i + 1, professor->turmas[i].codigo, professor->turmas[i].nome,
               professor->turmas[i].quantidade_alunos);
    }

    // TODO: Deletar o seguinte antes de enviar

    ///*
    printf("%s\n", professor->nome);
    printf("%d\n", professor->registro);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        printf("%s\n", professor->turmas[i].nome);
        printf("%s\n", professor->turmas[i].codigo);

        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            printf("%s\n", professor->turmas[i].alunos[j].nome);
            printf("%d\n", professor->turmas[i].alunos[j].matricula);
        }
    } //*/
}

int Achar_turma(prof *professor, char *buscar_codigo)
{
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        if (!strcmp(professor->turmas[i].codigo, buscar_codigo))
            return i;
    }

    return -1;
}

int Achar_aluno(prof *professor, int turma, int buscar_matricula)
{
    for (int i = 0; i < professor->turmas[turma].quantidade_alunos; i++)
    {
        if (professor->turmas[turma].alunos[i].matricula == buscar_matricula)
            return i;
    }

    return -1;
}

void Informacoes_do_Aluno(prof *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[12];
    fgets(codigo, 12, stdin);
    codigo[strlen(codigo) - 1] = '\0';

    int turma = Achar_turma(professor, codigo);
    int aluno = Achar_aluno(professor, turma, matricula);

    printf("Aluno: %s\n", professor->turmas[turma].alunos[aluno].nome);
    printf("Matricula: %d\n", professor->turmas[turma].alunos[aluno].matricula);

    printf("Prova 1: %d / ", professor->turmas[turma].alunos[aluno].notas[0]);
    printf("Prova 2: %d / ", professor->turmas[turma].alunos[aluno].notas[1]);
    printf("Prova 3: %d\n", professor->turmas[turma].alunos[aluno].notas[2]);

    int Nota_final =
        (professor->turmas[turma].alunos[aluno].notas[0] + professor->turmas[turma].alunos[aluno].notas[1] +
         professor->turmas[turma].alunos[aluno].notas[2]) /
        3;

    printf("Nota Final: %d - ", Nota_final);

    char conceito = Conceito(Nota_final);
    printf("Conceito %c\n", conceito);
}

void Inserir_Aluno(prof *professor)
{
    char nome[110];
    fgets(nome, 110, stdin);
    nome[strlen(nome) - 1] = '\0';

    int matricula;
    scanf("%d ", &matricula);

    char codigo[12];
    fgets(codigo, 12, stdin);
    codigo[strlen(codigo) - 1] = '\0';

    int turma = Achar_turma(professor, codigo);

    int qt_alunos = professor->turmas[turma].quantidade_alunos;

    strcpy(professor->turmas[turma].alunos[qt_alunos].nome, nome);
    professor->turmas[turma].alunos[qt_alunos].matricula = matricula;

    for (int i = 0; i < 3; i++)
    {
        professor->turmas[turma].alunos[qt_alunos].notas[i] = 0;
    }

    professor->turmas[turma].quantidade_alunos++;
}

void Lancar_Notas(prof *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[12];
    fgets(codigo, 12, stdin);
    codigo[strlen(codigo) - 1] = '\0';

    int turma = Achar_turma(professor, codigo);
    int aluno = Achar_aluno(professor, turma, matricula);

    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &professor->turmas[turma].alunos[aluno].notas[i]);
    }
}

void Informacoes_da_Turma(prof *professor)
{
    char codigo[12];
    fgets(codigo, 12, stdin);
    codigo[strlen(codigo) - 1] = '\0';

    int turma = Achar_turma(professor, codigo);

    printf("Informacoes da turma %s - ", professor->turmas[turma].codigo);
    printf("%s:\n", professor->turmas[turma].nome);

    printf("%d alunos\n", professor->turmas[turma].quantidade_alunos);

    for (int i = 0; i < professor->turmas[turma].quantidade_alunos; i++)
    {
        printf("Aluno: %s\n", professor->turmas[turma].alunos[i].nome);
        printf("Matricula: %d\n", professor->turmas[turma].alunos[i].matricula);
    }
}

void Situacao_dos_Alunos(prof *professor)
{
    char codigo[12];
    fgets(codigo, 12, stdin);
    codigo[strlen(codigo) - 1] = '\0';

    int turma = Achar_turma(professor, codigo);

    printf("Situacao na turma %s - ", professor->turmas[turma].codigo);
    printf("%s:\n", professor->turmas[turma].nome);

    int Nota_final;

    for (int i = 0; i < professor->turmas[turma].quantidade_alunos; i++)
    {
        printf("Aluno: %s\n", professor->turmas[turma].alunos[i].nome);
        printf("Matricula: %d\n", professor->turmas[turma].alunos[i].matricula);

        Nota_final = (professor->turmas[turma].alunos[i].notas[0] + professor->turmas[turma].alunos[i].notas[1] +
                      professor->turmas[turma].alunos[i].notas[2]) /
                     3;

        printf("Nota Final: %d - ", Nota_final);

        char conceito = Conceito(Nota_final);
        printf("Conceito %c\n", conceito);

        if (conceito == 'F')
            printf("Situacao: Reprovado");

        else if (conceito == 'E')
            printf("Exame Especial");

        else
            printf("Situacao: Aprovado");
    }
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

    int comando;

    do
    {
        scanf("%d", &comando);
        getchar();

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

    } while (comando != 7);

    fclose(input);
    // fclose(output);
    return EXIT_SUCCESS;
}
