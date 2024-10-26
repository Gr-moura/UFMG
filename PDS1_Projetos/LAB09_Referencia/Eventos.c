#include <stdio.h>

typedef enum
{
    jan = 1,
    fev,
    mar,
    abr,
    mai,
    jun,
    jul,
    ago,
    set,
    out,
    nov,
    dez

} mes_t;

typedef struct
{
    int dia;
    mes_t mes;
    int ano;

} Data;

typedef struct
{
    char nome[100];
    char local[100];
    Data data;

} Evento;

void cadastrar_eventos(Evento agenda[], int n)
{
    char buffer[300];

    for (int i = 0; i < n; i++)
    {
        fgets(buffer, 300, stdin);

        sscanf(buffer, "%s %s %d %d %d", agenda[i].nome, agenda[i].local, &agenda[i].data.dia,
               (int *)&agenda[i].data.mes, &agenda[i].data.ano);
    }
}

void imprimir_eventos(Evento agenda[], Data d, int n)
{
    int achados = 0;
    for (int i = 0; i < n; i++)
    {
        if (agenda[i].data.dia == d.dia && agenda[i].data.mes == d.mes && agenda[i].data.ano == d.ano)
        {
            printf("%s %s\n", agenda[i].nome, agenda[i].local);
            achados++;
        }
    }

    if (!achados)
        printf(" Nenhum evento encontrado!");
}

int main()
{
    int n;
    scanf("%d ", &n);

    Evento agenda[n];

    Data buscar_data;

    cadastrar_eventos(agenda, n);

    char buffer[300];
    fgets(buffer, 300, stdin);

    sscanf(buffer, "%d %d %d", &buscar_data.dia, (int *)&buscar_data.mes, &buscar_data.ano);

    imprimir_eventos(agenda, buscar_data, n);

    return 0;
}
