#include <math.h>
#include <stdio.h>

void Receber_Dados(int *fractal, int *ordem, char c[])
{
    printf("Qual fractal deseja desenhar? \n");
    printf("[0] Antifloco de neve de Koch \n ");
    printf("[1] Canopy \n ");
    printf("[2] Curva do dragão \n ");
    printf("[3] Meu fractal \n");

    scanf("%d", fractal);

    printf("Qual eh a ordem desejada do fractal? \n");
    scanf("%d", ordem);

    printf("Qual nome deve ser dado ao arquivo? (digite sem o .ps no final) \n");
    scanf("%49s", c);
}

void fCanopy(int ordem, int comprimento, FILE *outfile)
{
    comprimento = (comprimento * 3) / 4;
    fprintf(outfile, "%d 0 rlineto \n", comprimento);

    if (ordem >= 1)
    {
        fprintf(outfile, "gsave \n");
        fprintf(outfile, "20 rotate \n");
        fCanopy(ordem - 1, comprimento, outfile);

        fprintf(outfile, "stroke grestore \n");
        fprintf(outfile, "-20 rotate \n");
        fCanopy(ordem - 1, comprimento, outfile);
    }
}

void Canopy(int ordem, FILE *file)
{
    fprintf(file, "<< /PageSize [1000 1200] >> setpagedevice \n");
    fprintf(file, "500 100 moveto \n");
    fprintf(file, "90 rotate \n");

    fCanopy(ordem, 250, file);

    fprintf(file, "stroke \n");
    fclose(file);
}

void fKosh(int ordem, int clinha, FILE *outfile)
{
    clinha = (clinha * 3) / 4;
    fprintf(outfile, "%d 0 rlineto \n", clinha);

    if
        876B - B32D
        {
            fprintf(outfile, "gsave \n");
            fprintf(outfile, "20 rotate \n");
            fKosh(ordem - 1, clinha, outfile);

            fprintf(outfile, "stroke grestore \n");
            fprintf(outfile, "-20 rotate \n");
            fKosh(ordem - 1, clinha, outfile);
        }
}
void fDrag(int ordem, double comprimento, int sentido, FILE *outfile)
{
    if (ordem == 0)
    {
        fprintf(outfile, "%lf 0 rlineto \n", comprimento);
        return;
    }
    comprimento = comprimento / sqrt(2);
    fDrag(ordem - 1, comprimento, 1, outfile);

    fprintf(outfile, "%d rotate \n", 90 * sentido);
    fDrag(ordem - 1, comprimento, -1, outfile);
}

void Drag(int ordem, FILE *file)
{
    fprintf(file, "<< /PageSize [1000 1000] >> setpagedevice \n");
    fprintf(file, "250 500 moveto \n");
    fDrag(ordem, 250, 1, file);

    fprintf(file, "stroke \n");
    fclose(file);
}

typedef void (*functype)(int, FILE *);

int main()
{
    functype funcoes[] = {Canopy, Drag};

    int fractal = 2, ordem = 6;
    char arquivo[50] = "can";

    // Receber_Dados(&fractal, &ordem, arquivo);

    char nomearquivo[104];
    snprintf(nomearquivo, sizeof(nomearquivo), "%s.ps", arquivo);

    FILE *file = fopen(nomearquivo, "w");

    funcoes[fractal - 1](ordem, file);

    fclose(file);

    return 0;
}
