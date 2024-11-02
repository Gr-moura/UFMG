#include <iostream>
using namespace std;

#define X 0
#define Y 1

const string koch = "F++FF--F+F";
const string correto = "F-F++FF--F+F";

const string hilbert[2] = {"-YF+XFX+FY-", "+XF-YFY-FX+"};

void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int atual)
{
    // Axioma: F
    // θ = π/3
    //
    // Regra: F → F-F+F+FF-F-F+F

    if (ordem == 0)
    {
        cout << koch;
        return;
    }

    while (atual < koch.length())
    {
        if (koch[atual] == 'F')
        {
            Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(ordem - 1, 0);
            atual++;
            continue;
        }

        cout << koch[atual++];
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
            cout << hilbert[X];
            return;
        }

        cout << hilbert[Y];
        return;
    }

    while (atual < hilbert[pai].length())
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

        cout << hilbert[pai][atual++];
    }
}

int main()
{
    Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(1, 0);
    Preenchimento_de_Espaco_de_Hilbert(1, 0, X);

    return 0;
}
