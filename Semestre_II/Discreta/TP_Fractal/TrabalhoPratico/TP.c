#include <stdio.h>
#include <stdlib.h>

// Definições de coordenadas
#define X 0
#define Y 1

// Definições das sequências de L-systems
const char koch[] = "F-F++FF--F+F";
const char hilbert[][12] = {"-YF+XFX+FY-", "+XF-YFY-FX+"};
const char sierpinski[][8] = {"YF+XF+Y", "XF-YF-X"};

int Signos = 0, Fs = 0;
int somarSignos = 7, somarFs = 2;

// Função recursiva para gerar o fractal Floco de Neve de Von Koch
void Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(int ordem, int indice, FILE *arquivo)
{
    // Caso base: se a ordem é 1, imprime a sequência de Koch e retorna
    if (ordem == 1)
    {
        fprintf(arquivo, "%s", koch);
        return;
    }

    // Percorre a sequência de Koch
    while (koch[indice] != '\0')
    {
        // Se o caractere atual é 'F', chama recursivamente para a próxima ordem
        if (koch[indice] == 'F')
        {
            Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(ordem - 1, 0, arquivo);
            indice++;
            continue;
        }

        // Imprime o caractere atual no arquivo
        fprintf(arquivo, "%c", koch[indice++]);
    }
}

// Função recursiva para gerar o fractal de Preenchimento de Espaço de Hilbert
void Preenchimento_de_Espaco_de_Hilbert(int ordem, int indice, int pai, FILE *arquivo)
{
    // Caso base: se a ordem é 1, imprime a sequência de Hilbert correspondente e retorna
    if (ordem == 1)
    {
        Signos += somarSignos;
        Fs += somarFs;
        // Se o pai é X, percorre a sequência de Hilbert para X
        if (pai == X)
        {
            for (int i = 0; hilbert[X][i] != '\0'; i++)
            {
                if (hilbert[X][i] == 'X')
                    continue;

                if (hilbert[X][i] == 'Y')
                    continue;

                // Imprime o caractere atual no arquivo, se ele for diferente de X e de Y
                fprintf(arquivo, "%c", hilbert[X][i]);
            }

            return;
        }

        // Se o pai é Y, percorre a sequência de Hilbert para Y
        for (int i = 0; hilbert[Y][i] != '\0'; i++)
        {
            if (hilbert[Y][i] == 'X')
                continue;

            if (hilbert[Y][i] == 'Y')
                continue;

            // Imprime o caractere atual no arquivo, se ele for diferente de X e de Y
            fprintf(arquivo, "%c", hilbert[Y][i]);
        }

        return;
    }

    // Percorre a sequência de Hilbert para o pai atual
    while (hilbert[pai][indice] != '\0')
    {
        // Se o caractere atual é 'X', chama recursivamente para a próxima ordem com pai X
        if (hilbert[pai][indice] == 'X')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, X, arquivo);
            indice++;
            continue;
        }

        // Se o caractere atual é 'Y', chama recursivamente para a próxima ordem com pai Y
        if (hilbert[pai][indice] == 'Y')
        {
            Preenchimento_de_Espaco_de_Hilbert(ordem - 1, 0, Y, arquivo);
            indice++;
            continue;
        }

        // Imprime o caractere atual no arquivo
        if (hilbert[pai][indice] == 'F')
        {
            Fs++;
        }
        fprintf(arquivo, "%c", hilbert[pai][indice++]);
        Signos++;
    }
}

// Função recursiva para gerar o fractal Ponta de Flecha de Sierpinski
void Ponta_de_Flecha_de_Sierpinski(int ordem, int indice, int pai, FILE *arquivo)
{
    // Caso base: se a ordem é 1, imprime a sequência de Sierpinski correspondente e retorna
    if (ordem == 1)
    {
        // Se o pai é X, percorre a sequência de Sierpinski para X
        if (pai == X)
        {
            for (int i = 0; sierpinski[X][i] != '\0'; i++)
            {

                if (sierpinski[X][i] == 'X')
                    continue;

                if (sierpinski[X][i] == 'Y')
                    continue;

                // Imprime o caractere atual no arquivo, se ele for diferente de X e de Y
                fprintf(arquivo, "%c", sierpinski[X][i]);
            }

            return;
        }

        // Se o pai é Y, percorre a sequência de Sierpinski para Y
        for (int i = 0; sierpinski[Y][i] != '\0'; i++)
        {
            if (sierpinski[Y][i] == 'X')
                continue;

            if (sierpinski[Y][i] == 'Y')
                continue;

            // Imprime o caractere atual no arquivo, se ele for diferente de X e de Y
            fprintf(arquivo, "%c", sierpinski[Y][i]);
        }

        return;
    }

    // Percorre a sequência de Sierpinski para o pai atual
    while (sierpinski[pai][indice] != '\0')
    {
        // Se o caractere atual é 'X', chama recursivamente para a próxima ordem com pai X
        if (sierpinski[pai][indice] == 'X')
        {
            Ponta_de_Flecha_de_Sierpinski(ordem - 1, 0, X, arquivo);
            indice++;
            continue;
        }

        // Se o caractere atual é 'Y', chama recursivamente para a próxima ordem com pai Y
        if (sierpinski[pai][indice] == 'Y')
        {
            Ponta_de_Flecha_de_Sierpinski(ordem - 1, 0, Y, arquivo);
            indice++;
            continue;
        }

        // Imprime o caractere atual no arquivo
        fprintf(arquivo, "%c", sierpinski[pai][indice++]);
    }
}

int main()
{
    int estagio;
    scanf("%d", &estagio);

    // Abertura dos arquivos para escrita
    FILE *i = fopen("i.txt", "w");
    FILE *ii = fopen("ii.txt", "w");
    FILE *iii = fopen("iii.txt", "w");

    // Geração dos fractais
    Floco_de_Neve_Onda_Senoidal_1_de_Von_Koch(estagio, 0, i);
    Preenchimento_de_Espaco_de_Hilbert(estagio, 0, X, ii);
    Ponta_de_Flecha_de_Sierpinski(estagio, 0, Y, iii);
    fprintf(iii, "F");

    // Fecha os arquivos abertos
    fclose(i);
    fclose(ii);
    fclose(iii);

    return 0;
}
