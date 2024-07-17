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

void str_fgets(char *variavel, int tamanho, FILE *file)
{
    fgets(variavel, tamanho, file);

    for (int i = 0; i < tamanho; i++)
    {
        if (variavel[i] == '\n' || variavel[i] == '\r')
        {
            variavel[i] = '\0';
            return;
        }
    }
}

void Ler_input(FILE *file, prof *professor)
{
    char nome[100];
    char codigo[10];

    str_fgets(professor->nome, 100, file);

    fscanf(file, "%d ", &professor->registro);
    fscanf(file, "%d ", &professor->quantidade_turmas);

    // Nome e código de cada turma
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        str_fgets(professor->turmas[i].nome, 100, file);
        str_fgets(professor->turmas[i].codigo, 10, file);
    }

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fscanf(file, "%d ", &professor->turmas[i].quantidade_alunos);

        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            str_fgets(professor->turmas[i].alunos[j].nome, 100, file);

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
}

int Achar_turma(prof *professor, char *buscar_codigo)
{
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        if (!strcmp(buscar_codigo, professor->turmas[i].codigo))
            return i;
    }

    printf("\nErro: Turma não encontrada!\n");
    printf("Turma procurada: %s\n", buscar_codigo);
    return -1;
}

int Achar_aluno(prof *professor, int turma, int buscar_matricula)
{
    for (int i = 0; i < professor->turmas[turma].quantidade_alunos; i++)
    {
        if (professor->turmas[turma].alunos[i].matricula == buscar_matricula)
            return i;
    }

    printf("\nErro: Aluno não encontrado!\n");
    printf("Aluno procurado: %d\n", buscar_matricula);
    return -1;
}

void Informacoes_do_Aluno(prof *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[10];
    str_fgets(codigo, 10, stdin);

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
    char nome[100];
    str_fgets(nome, 100, stdin);

    int matricula;
    scanf("%d ", &matricula);

    char codigo[10];
    str_fgets(codigo, 10, stdin);

    int turma = Achar_turma(professor, codigo);
    int qt_alunos = professor->turmas[turma].quantidade_alunos;

    strcpy(professor->turmas[turma].alunos[qt_alunos].nome, nome);
    professor->turmas[turma].alunos[qt_alunos].matricula = matricula;

    professor->turmas[turma].quantidade_alunos++;
}

void Lancar_Notas(prof *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[10];
    str_fgets(codigo, 10, stdin);

    int turma = Achar_turma(professor, codigo);
    int aluno = Achar_aluno(professor, turma, matricula);

    for (int i = 0; i < 3; i++)
    {
        scanf("%d ", &professor->turmas[turma].alunos[aluno].notas[i]);
    }
}

void Informacoes_da_Turma(prof *professor)
{
    char codigo[10];
    str_fgets(codigo, 10, stdin);

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
    char codigo[10];
    str_fgets(codigo, 10, stdin);

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
            printf("Situacao: Reprovado\n");

        else if (conceito == 'E')
            printf("Situacao: Exame Especial\n");

        else
            printf("Situacao: Aprovado\n");
    }
}

void Exportar_Dados(prof *professor, char *s)
{
    FILE *output = fopen(s, "w");

    fprintf(output, "DADOS EXPORTADOS\n\n");
    fprintf(output, "Professor %s", (*professor).nome);
    fprintf(output, " - Registro %d\n\n", (*professor).registro);

    for (int i = 0; i < (*professor).quantidade_turmas; i++)
    {
        turma *turma = &(*professor).turmas[i];
        fprintf(output, "Turma %s - %s\n", (*turma).codigo, (*turma).nome);

        for (int j = 0; j < (*turma).quantidade_alunos; j++)
        {

            aluno *aluno = &(*turma).alunos[j];
            fprintf(output, "Aluno: %s\n", (*aluno).nome);
            fprintf(output, "Matricula: %d\n", (*aluno).matricula);

            unsigned int nota_final =
                (professor->turmas[i].alunos[j].notas[0] + professor->turmas[i].alunos[j].notas[1] +
                 professor->turmas[i].alunos[j].notas[2]) /
                3;

            fprintf(output, "Nota Final: %d", nota_final);

            char conceito = Conceito(nota_final);

            fprintf(output, " - Conceito %c", conceito);

            if (conceito == 'F')
                fprintf(output, " - Reprovado\n");

            else if (conceito == 'E')
                fprintf(output, " - Exame Especial\n");

            else
                fprintf(output, " - Aprovado\n");
        }

        fprintf(output, "\n");
    }
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

    prof professor;

    Ler_input(input, &professor);
    Imprimir_menu();

    int comando;

    do
    {
        scanf("%d ", &comando);

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
            fclose(input);
            getchar();

            Exportar_Dados(&professor, argv[2]);
            break;
        }

    } while (comando != 7);

    return EXIT_SUCCESS;
}
