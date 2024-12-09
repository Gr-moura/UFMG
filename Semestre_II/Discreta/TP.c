#include <stdio.h>

#define X 0
#define Y 1

const char koch[] = "F++FF--F+F";
const char correto[] = "F-F++FF--F+F";

const char hilbert[2][12] = {"-YF+XFX+FY-", "+XF-YFY-FX+"};

void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int atual)
{
    // Axioma: F
    // θ = π/3
    //
    // Regra: F → F-F+F+FF-F-F+F

    if (ordem == 0)
    {
        printf("%s", koch);
        return;
    }

    while (koch[atual] != '\0')
    {
        if (koch[atual] == 'F')
        {
            Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(ordem - 1, 0);
            atual++;
            continue;
        }

        printf("%c", koch[atual++]);
    }
}

void Preenchimento_de_Espaco_de_Hilbert(int ordem, int atual, int pai)
{
    // Axioma: X
    // θ = π/2
    //
    // Regras :
    // X → -YF+XFX+FY-
    // Y → +XF-YFY-FX+

    if (ordem == 0)
    {
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
    }
}

int main()
{
    // t(n) = R^n * T + nR(R^n - 1) / (R - 1)

    // Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(1, 0);
    Preenchimento_de_Espaco_de_Hilbert(3, 0, X);

    return 0;
}
