#include <stdio.h>
#include <stdlib.h>

#define X 0
#define Y 1

const char koch[] = "F-F++FF--F+F";
const char hilbert[][12] = {"-YF+XFX+FY-", "+XF-YFY-FX+"};
const char sierpinski[][8] = {"YF+XF+Y", "XF-YF-X"};

void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int atual, FILE *arquivo)
{
    if (ordem == 1)
    {
        fprintf(arquivo, "%s", koch);
        return;
    }

    while (koch[atual] != '\0')
    {
        if (koch[atual] == 'F')
        {
            Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(ordem - 1, 0, arquivo);
            atual++;
            continue;
        }

        fprintf(arquivo, "%c", koch[atual++]);
    }
}

void Preenchimento_de_Espaco_de_Hilbert(int ordem, int atual, int pai, FILE *arquivo)
{
    if (ordem == 1)
    {
        if (pai == X)
        {
            for (int i = 0; hilbert[X][i] != '\0'; i++)
            {
                if (hilbert[X][i] == 'X')
                    continue;

                if (hilbert[X][i] == 'Y')
                    continue;

                fprintf(arquivo, "%c", hilbert[X][i]);
            }

            return;
        }

        for (int i = 0; hilbert[Y][i] != '\0'; i++)
        {
            if (hilbert[Y][i] == 'X')
                continue;

            if (hilbert[Y][i] == 'Y')
                continue;

            fprintf(arquivo, "%c", hilbert[Y][i]);
        }

        return;
    }

    while (hilbert[pai][atual] != '\0')
    {
        if (hilbert[pai][atual] == 'X')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, X, arquivo);
            atual++;
            continue;
        }

        if (hilbert[pai][atual] == 'Y')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, Y, arquivo);
            atual++;
            continue;
        }

        fprintf(arquivo, "%c", hilbert[pai][atual++]);
    }
}

void Ponta_de_Flecha_de_Sierpinski(int ordem, int atual, int pai, FILE *arquivo)
{
    if (ordem == 1)
    {
        if (pai == X)
        {
            for (int i = 0; sierpinski[X][i] != '\0'; i++)
            {
                if (sierpinski[X][i] == 'X')
                    continue;

                if (sierpinski[X][i] == 'Y')
                    continue;

                fprintf(arquivo, "%c", sierpinski[X][i]);
            }

            return;
        }

        for (int i = 0; sierpinski[Y][i] != '\0'; i++)
        {
            if (sierpinski[Y][i] == 'X')
                continue;

            if (sierpinski[Y][i] == 'Y')
                continue;

            fprintf(arquivo, "%c", sierpinski[Y][i]);
        }

        return;
    }

    while (sierpinski[pai][atual] != '\0')
    {
        if (sierpinski[pai][atual] == 'X')
        {
            Ponta_de_Flecha_de_Sierpinski(ordem - 1, 0, X, arquivo);
            atual++;
            continue;
        }

        if (sierpinski[pai][atual] == 'Y')
        {
            Ponta_de_Flecha_de_Sierpinski(ordem - 1, 0, Y, arquivo);
            atual++;
            continue;
        }

        fprintf(arquivo, "%c", sierpinski[pai][atual++]);
    }
}

int main()
{
    int estagio;
    scanf("%d", &estagio);

    FILE *i = fopen("i.txt", "w");
    FILE *ii = fopen("ii.txt", "w");
    FILE *iii = fopen("iii.txt", "w");

    Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(estagio, 0, i);
    Preenchimento_de_Espaco_de_Hilbert(estagio, 0, X, ii);
    Ponta_de_Flecha_de_Sierpinski(estagio, 0, Y, iii);
    fprintf(iii, "F");

    return 0;
}
