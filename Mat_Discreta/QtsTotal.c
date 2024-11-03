#include <stdio.h>

#define X 0
#define Y 1

const char koch[] = "F-F++FF--F+F";
const char correto[] = "F-F++FF--F+F";

char hilbert[2][12] = {"-YF+XFX+FY-", "+XF-YFY-FX+"};

int Signos = 0, Fs = 0;
int somarSignos = 0, somarFs = 0;

void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int atual)
{
    if (ordem == 0)
    {
        printf("%s", koch); // t(0) = T
        Signos += Signos;
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
    if (ordem == 0)
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

        printf("%c", hilbert[pai][atual++]);
        Signos++;
        
        if (hilbert[pai][atual] == 'F')
        {
            Fs++;
        }
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

    // Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(2, 0);
    Preenchimento_de_Espaco_de_Hilbert(2, 0, X);
    printf("\n%d %d %d", Signos, Fs, Signos - Fs);

    return 0;
}
