#include <stdio.h>
#include <string.h>

typedef struct
{
    double comp_sepala;
    double larg_sepala;

    double comp_petala;
    double larg_petala;

    char tipo[50];

} Iris_t;

void Registrar_Flores(Iris_t Flores[], int n)
{
    char buffer[200];

    for (int i = 0; i < n; i++)
    {
        fgets(buffer, 200, stdin);

        sscanf(buffer, "%lf %lf %lf %lf %s", &Flores[i].comp_sepala, &Flores[i].larg_sepala, &Flores[i].comp_petala,
               &Flores[i].larg_petala, Flores[i].tipo);

        // printf("%lf %lf %lf %lf\n", Flores[i].comp_sepala, Flores[i].larg_sepala, Flores[i].comp_petala,
        // Flores[i].larg_petala);
    }
}

void Classificar(Iris_t Sem_ID, Iris_t Flores[], int n)
{
    double dist_euclidiana;
    double menor = -1;

    char tipo[50];

    for (int i = 0; i < n; i++)
    {
        dist_euclidiana = 0;

        dist_euclidiana += (Sem_ID.comp_sepala - Flores[i].comp_sepala) * (Sem_ID.comp_sepala - Flores[i].comp_sepala);
        dist_euclidiana += (Sem_ID.larg_sepala - Flores[i].larg_sepala) * (Sem_ID.larg_sepala - Flores[i].larg_sepala);
        dist_euclidiana += (Sem_ID.comp_petala - Flores[i].comp_petala) * (Sem_ID.comp_petala - Flores[i].comp_petala);
        dist_euclidiana += (Sem_ID.larg_petala - Flores[i].larg_petala) * (Sem_ID.larg_petala - Flores[i].larg_petala);

        if (menor == -1 || dist_euclidiana < menor)
        {
            menor = dist_euclidiana;
            strcpy(tipo, Flores[i].tipo);
        }
    }

    printf("%s\n", tipo);
}

int main()
{
    int n;
    scanf("%d ", &n);

    Iris_t Flores[n];
    Iris_t Sem_ID;

    Registrar_Flores(Flores, n);

    char buffer[200];
    fgets(buffer, 200, stdin);

    sscanf(buffer, "%lf %lf %lf %lf", &Sem_ID.comp_sepala, &Sem_ID.larg_sepala, &Sem_ID.comp_petala,
           &Sem_ID.larg_petala);

    Classificar(Sem_ID, Flores, n);

    return 0;
}
