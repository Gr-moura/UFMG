#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_CODIGO 10
#define MAX_ALUNOS 6
#define MAX_TURMAS 2

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
    turma_t turmas[MAX_TURMAS];

} prof_t;

// O fgets coloca o \n dentro da string, entao já o tiramos de uma vez
void Ler_String(char *variavel, int tamanho, FILE *file)
{
    fgets(variavel, tamanho, file);
    variavel[strlen(variavel) - 1] = '\0';
}

// Função para ler os dados de um professor de um arquivo
void Ler_Input(FILE *file, prof_t *professor)
{
    Ler_String(professor->nome, MAX_NOME, file);

    fscanf(file, "%u ", &professor->registro);
    fscanf(file, "%d ", &professor->quantidade_turmas);

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        Ler_String(professor->turmas[i].nome, MAX_NOME, file);
        Ler_String(professor->turmas[i].codigo, MAX_CODIGO, file);
    }

    for (int i = 0; i < professor->quantidade_turmas; i++)
    {
        fscanf(file, "%d ", &professor->turmas[i].quantidade_alunos);

        for (int j = 0; j < professor->turmas[i].quantidade_alunos; j++)
        {
            Ler_String(professor->turmas[i].alunos[j].nome, MAX_NOME, file);

            fscanf(file, "%u ", &professor->turmas[i].alunos[j].matricula);

            professor->turmas[i].alunos[j].notas[0] = 0;
            professor->turmas[i].alunos[j].notas[1] = 0;
            professor->turmas[i].alunos[j].notas[2] = 0;
        }
    }
}

// Calcular o conceito com base na nota
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

// Função para imprimir o menu de opções
void Imprimir_Menu()
{
    printf("1 - Informacoes do Professor\n");
    printf("2 - Informacoes do Aluno\n");
    printf("3 - Inserir Aluno\n");
    printf("4 - Lancar Notas\n");
    printf("5 - Informacoes da Turma\n");
    printf("6 - Situacao dos Alunos\n");
    printf("7 - Exportar Dados\n");
}

// Função para imprimir informações do professor
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

// Função para encontrar uma determinada turma pelo seu código
int Achar_Turma(prof_t *professor, char *buscar_codigo)
{
    for (int idxTurma = 0; idxTurma < professor->quantidade_turmas; idxTurma++)
    {
        if (!strcmp(buscar_codigo, professor->turmas[idxTurma].codigo))
            return idxTurma;
    }

    printf("\nErro: Turma não encontrada!\n");
    printf("Turma procurada: %s\n", buscar_codigo);
    return EXIT_FAILURE;
}

// Função para encontrar um determinado aluno pela sua matrícula
int Achar_Aluno(prof_t *professor, int idxTurma, int buscar_matricula)
{
    for (int idxAluno = 0; idxAluno < professor->turmas[idxTurma].quantidade_alunos; idxAluno++)
    {
        if (professor->turmas[idxTurma].alunos[idxAluno].matricula == buscar_matricula)
            return idxAluno;
    }

    printf("\nErro: Aluno não encontrado!\n");
    printf("Aluno procurado: %d\n", buscar_matricula);
    return EXIT_FAILURE;
}

// Função para imprimir informações de um aluno
void Informacoes_do_Aluno(prof_t *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    Ler_String(codigo, MAX_CODIGO, stdin);

    int idxTurma = Achar_Turma(professor, codigo);
    int idxAluno = Achar_Aluno(professor, idxTurma, matricula);

    printf("Aluno: %s\n", professor->turmas[idxTurma].alunos[idxAluno].nome);
    printf("Matricula: %d\n", professor->turmas[idxTurma].alunos[idxAluno].matricula);

    printf("Prova 1: %d / ", professor->turmas[idxTurma].alunos[idxAluno].notas[0]);
    printf("Prova 2: %d / ", professor->turmas[idxTurma].alunos[idxAluno].notas[1]);
    printf("Prova 3: %d\n", professor->turmas[idxTurma].alunos[idxAluno].notas[2]);

    int Nota_final =
        (professor->turmas[idxTurma].alunos[idxAluno].notas[0] + professor->turmas[idxTurma].alunos[idxAluno].notas[1] +
         professor->turmas[idxTurma].alunos[idxAluno].notas[2]) /
        3;

    printf("Nota Final: %d - ", Nota_final);

    char conceito = Conceito(Nota_final);
    printf("Conceito %c\n", conceito);
}

// Função para inserir um novo aluno
void Inserir_Aluno(prof_t *professor)
{
    char nome[MAX_NOME];
    Ler_String(nome, MAX_NOME, stdin);

    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    Ler_String(codigo, MAX_CODIGO, stdin);

    int idxTurma = Achar_Turma(professor, codigo);

    // A quantidade de alunos tem o mesmo valor que a primeira posicao não
    // utilizada do vetor alunos, então definimos a variável nova_pos com o seu valor
    int nova_pos = professor->turmas[idxTurma].quantidade_alunos;

    strcpy(professor->turmas[idxTurma].alunos[nova_pos].nome, nome);
    professor->turmas[idxTurma].alunos[nova_pos].matricula = matricula;

    professor->turmas[idxTurma].alunos[nova_pos].notas[0] = 0;
    professor->turmas[idxTurma].alunos[nova_pos].notas[1] = 0;
    professor->turmas[idxTurma].alunos[nova_pos].notas[2] = 0;

    professor->turmas[idxTurma].quantidade_alunos++;
}

// Função para lançar notas de um aluno
void Lancar_Notas(prof_t *professor)
{
    int matricula;
    scanf("%d ", &matricula);

    char codigo[MAX_CODIGO];
    Ler_String(codigo, MAX_CODIGO, stdin);

    int idxTurma = Achar_Turma(professor, codigo);
    int idxAluno = Achar_Aluno(professor, idxTurma, matricula);

    for (int i = 0; i < 3; i++)
    {
        scanf("%d ", &professor->turmas[idxTurma].alunos[idxAluno].notas[i]);
    }
}

// Função para imprimir informações de uma turma
void Informacoes_da_Turma(prof_t *professor)
{
    char codigo[MAX_CODIGO];
    Ler_String(codigo, MAX_CODIGO, stdin);

    int idxTurma = Achar_Turma(professor, codigo);

    printf("Informacoes da turma %s - ", professor->turmas[idxTurma].codigo);
    printf("%s:\n", professor->turmas[idxTurma].nome);

    printf("%d alunos\n", professor->turmas[idxTurma].quantidade_alunos);

    for (int i = 0; i < professor->turmas[idxTurma].quantidade_alunos; i++)
    {
        printf("Aluno: %s\n", professor->turmas[idxTurma].alunos[i].nome);
        printf("Matricula: %d\n", professor->turmas[idxTurma].alunos[i].matricula);
    }
}

// Função para imprimir a situação dos alunos de uma turma
void Situacao_dos_Alunos(prof_t *professor)
{
    char codigo[MAX_CODIGO];
    Ler_String(codigo, MAX_CODIGO, stdin);

    int idxTurma = Achar_Turma(professor, codigo);

    printf("Situacao na turma %s - ", professor->turmas[idxTurma].codigo);
    printf("%s:\n", professor->turmas[idxTurma].nome);

    int Nota_final;

    for (int i = 0; i < professor->turmas[idxTurma].quantidade_alunos; i++)
    {
        printf("Aluno: %s\n", professor->turmas[idxTurma].alunos[i].nome);
        printf("Matricula: %d\n", professor->turmas[idxTurma].alunos[i].matricula);

        Nota_final = (professor->turmas[idxTurma].alunos[i].notas[0] + professor->turmas[idxTurma].alunos[i].notas[1] +
                      professor->turmas[idxTurma].alunos[i].notas[2]) /
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

// Funcao para exportar dados para um arquivo
void Exportar_Dados(prof_t *professor, char *arquivo)
{
    FILE *output = fopen(arquivo, "w");

    if (output == NULL)
    {
        perror("Error");
        return;
    }

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

    Ler_Input(input, &professor);
    Imprimir_Menu();

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
