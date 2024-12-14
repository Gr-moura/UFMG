#include <stdio.h>

#define X 0
#define Y 1

const char koch[] = "F-F+F+FF-F-F+F";
const char correto[] = "F-F++FF--F+F";

char hilbert[2][12] = {"YF+XF+Y", "XF-YF-X"};

int Signos = 0, Fs = 0;
int somarSignos = 0, somarFs = 0;

void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int atual)
{
    if (ordem == 1)
    {
        printf("%s", koch); // t(0) = T
        Signos += somarSignos;
        Fs += somarFs;
        return;
    }

    while (koch[atual] != '\0') // t(n) = R * t(n - 1) + nR
    {
        if (koch[atual] == 'F')
        {
            Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(ordem - 1, 0);
            atual++;
            continue;
        }

        printf("%c", koch[atual++]); // t(n) = R^n * T + nR(R^n - 1) / (R - 1)

        Signos++;
    }
}

void Preenchimento_de_Espaco_de_Hilbert(int ordem, int atual, int pai)
{
    if (ordem == 1)
    {
        Signos += somarSignos;
        Fs += somarFs;

        if (pai == X)
        {
            printf("%s", hilbert[X]);
            return;
        }

        printf("%s", hilbert[Y]);
        return;
    }

    while (hilbert[pai][atual] != '\0')
    {
        if (hilbert[pai][atual] == 'X')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, X);
            atual++;
            continue;
        }

        if (hilbert[pai][atual] == 'Y')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, Y);
            atual++;
            continue;
        }
        if (hilbert[pai][atual] == 'F')
        {
            Fs++;
        }

        printf("%c", hilbert[pai][atual++]);
        Signos++;
    }
}

int main()
{
    char *regra = hilbert[X];

    for (int i = 0; regra[i] != '\0'; i++)
    {
        somarSignos++;

        if (regra[i] == 'F')
        {
            somarFs++;
        }
    }

    // t(n) = R^n * T + nR(R^n - 1) / (R - 1)

    // Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(3, 0);
    Preenchimento_de_Espaco_de_Hilbert(1, 0, Y);
    Fs++;
    Signos++;
    printf("\nSignos: %d\nSegmentos: %d\nResto: %d\n", Signos, Fs, Signos - Fs);

    return 0;
}
