#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_CODIGO 10
#define MAX_ALUNOS 6

typedef struct
{
    char nome[MAX_NOME];
    unsigned int matricula;

    int notas[3];

} aluno_t;

typedef struct
{
    char codigo[MAX_CODIGO];
    char nome[MAX_NOME];

    int quantidade_alunos;
    aluno_t alunos[MAX_ALUNOS];

} turma_t;

typedef struct
{
    char nome[MAX_NOME];
    unsigned int registro;

    int quantidade_turmas;
    turma_t turmas[2];

} prof_t;

// O fgets coloca o \n dentro da string, entao já o tiramos de uma vez
void str_fgets(char *variavel, int tamanho, FILE *file)
{
    fgets(variavel, tamanho, file);
    variavel[strlen(variavel) - 1] = '\0';
}

void Ler_input(FILE *file, prof_t *professor)
{
    str_fgets(professor->nome, MAX_NOME, file);

    fscanf(file, "%u ", &professor->registro);
    fscanf(file, "%d ", &professor->quantidade_turmas);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        str_fgets(professor->turmas[i].nome, MAX_NOME, file);
        str_fgets(professor->turmas[i].codigo, MAX_CODIGO, file);
    }

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fscanf(file, "%d ", &professor->turmas[i].quantidade_alunos);

        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            str_fgets(professor->turmas[i].alunos[j].nome, MAX_NOME, file);

            fscanf(file, "%u ", &professor->turmas[i].alunos[j].matricula);

            professor->turmas[i].alunos[j].notas[0] = 0;
            professor->turmas[i].alunos[j].notas[1] = 0;
            professor->turmas[i].alunos[j].notas[2] = 0;
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

void Informacoes_do_Professor(prof_t *professor)
{
    printf("Professor %s\n", professor->nome);
    printf("Registro numero %u\n", professor->registro);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        printf("Turma %d: %s - %s, %d alunos\n", i + 1, professor->turmas[i].codigo, professor->turmas[i].nome,
               professor->turmas[i].quantidade_alunos);
    }
}

int Achar_turma(prof_t *professor, char *buscar_codigo)
{
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        if (!strcmp(buscar_codigo, professor->turmas[i].codigo))
            return i;
    }

    printf("\nErro: Turma não encontrada!\n");
    printf("Turma procurada: %s\n", buscar_codigo);
    return EXIT_FAILURE;
}

int Achar_aluno(prof_t *professor, int turma, int buscar_matricula)
{
    for (int i = 0; i < professor->turmas[turma].quantidade_alunos; i++)
    {
        if (professor->turmas[turma].alunos[i].matricula == buscar_matricula)
            return i;
    }

    printf("\nErro: Aluno não encontrado!\n");
    printf("Aluno procurado: %d\n", buscar_matricula);
    return EXIT_FAILURE;
}

void Informacoes_do_Aluno(prof_t *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    str_fgets(codigo, MAX_CODIGO, stdin);

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

void Inserir_Aluno(prof_t *professor)
{
    char nome[MAX_NOME];
    str_fgets(nome, MAX_NOME, stdin);

    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    str_fgets(codigo, MAX_CODIGO, stdin);

    int turma = Achar_turma(professor, codigo);

    // A quantidade de alunos tem o mesmo valor que a primeira
    // posicao nao utilizada do vetor alunos
    int nova_pos = professor->turmas[turma].quantidade_alunos;

    strcpy(professor->turmas[turma].alunos[nova_pos].nome, nome);
    professor->turmas[turma].alunos[nova_pos].matricula = matricula;

    professor->turmas[turma].quantidade_alunos++;
}

void Lancar_Notas(prof_t *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    str_fgets(codigo, MAX_CODIGO, stdin);

    int turma = Achar_turma(professor, codigo);
    int aluno = Achar_aluno(professor, turma, matricula);

    for (int i = 0; i < 3; i++)
    {
        scanf("%d ", &professor->turmas[turma].alunos[aluno].notas[i]);
    }
}

void Informacoes_da_Turma(prof_t *professor)
{
    char codigo[MAX_CODIGO];
    str_fgets(codigo, MAX_CODIGO, stdin);

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

void Situacao_dos_Alunos(prof_t *professor)
{
    char codigo[MAX_CODIGO];
    str_fgets(codigo, MAX_CODIGO, stdin);

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

void Exportar_Dados(prof_t *professor, char *s)
{
    FILE *output = fopen(s, "w");

    fprintf(output, "DADOS EXPORTADOS\n\n");
    fprintf(output, "Professor %s - Registro %u\n\n", professor->nome, professor->registro);

    int Nota_final;
    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fprintf(output, "Turma %s - ", professor->turmas[i].codigo);
        fprintf(output, "%s\n", professor->turmas[i].nome);
        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            fprintf(output, "Aluno: %s\n", professor->turmas[i].alunos[j].nome);
            fprintf(output, "Matricula: %d\n", professor->turmas[i].alunos[j].matricula);

            Nota_final = (professor->turmas[i].alunos[j].notas[0] + professor->turmas[i].alunos[j].notas[1] +
                          professor->turmas[i].alunos[j].notas[2]) /
                         3;

            fprintf(output, "Nota Final: %d - ", Nota_final);

            char conceito = Conceito(Nota_final);
            fprintf(output, "Conceito %c - ", conceito);

            if (conceito == 'F')
                fprintf(output, "Reprovado\n");

            else if (conceito == 'E')
                fprintf(output, "Exame Especial\n");

            else
                fprintf(output, "Aprovado\n");
        }

        if (professor->quantidade_turmas == 2 && i == 0)
            fputc('\n', output);
    }

    fclose(output);
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

    prof_t professor;

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
            getchar();
            fclose(input);
            Exportar_Dados(&professor, argv[2]);
            break;
        }

    } while (comando != 7);

    return EXIT_SUCCESS;
}
