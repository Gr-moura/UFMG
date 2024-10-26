#include <stdio.h>
#include <string.h>

int eh_bi(int teste)
{
    if (teste % 4 == 0 && (teste % 100 != 0 || teste % 400 == 0))
        return 1;

    return 0;
}

int desde_inicio(int dia, int mes, int bi)
{
    int ans = 0;
    for (int i = 1; i < mes; i++)
    {
        if (i == 1)
            ans += 31;
        else if (i == 2 && bi == 1)
            ans += 29;
        else if (i == 2 && bi == 0)
            ans += 28;
        else if (i == 3)
            ans += 31;
        else if (i == 4)
            ans += 30;
        else if (i == 5)
            ans += 31;
        else if (i == 6)
            ans += 30;
        else if (i == 7)
            ans += 31;
        else if (i == 8)
            ans += 31;
        else if (i == 9)
            ans += 30;
        else if (i == 10)
            ans += 31;
        else if (i == 11)
            ans += 30;
    }

    ans += dia;

    return ans;
}

int bissextos(int inicio)
{
    int somar = 0;
    for (int i = inicio; i < 2020; i++)
    {
        if (eh_bi(i))
            somar++;
    }

    return somar;
}

int dias(int dia, int mes, int ano)
{
    int ans = 0;

    if (ano != 2020)
    {
        ans += (2019 - ano) * 365;

        ans += 261;

        // ver bissextos;
        ans += bissextos(ano + 1);

        // Ver quanto que falta até o fim do ano;
        if (eh_bi(ano))
            ans += (367 - desde_inicio(dia, mes, 1));
        else
            ans += (366 - desde_inicio(dia, mes, 0));
    }

    else
    {
        ans += (262 - desde_inicio(dia, mes, 1));
    }

    return ans;
}

int main()
{
    char buffer[100];
    int dia, mes, ano;

    do
    {
        fgets(buffer, 100, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        sscanf(buffer, "%d%d%d", &dia, &mes, &ano);
        printf("%d\n", dias(dia, mes, ano));

    } while (strlen(buffer) > 0);

    return 0;
}
