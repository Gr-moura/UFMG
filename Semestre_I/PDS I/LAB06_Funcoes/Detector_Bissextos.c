#include <stdio.h>
#include <string.h>

int eh_bi(int teste)
{
    if (teste % 4 == 0 && (teste % 100 != 0 || teste % 400 == 0))
        return 1;

    return 0;
}

int main()
{
    int ano;
    char entrada[50];

    while (fgets(entrada, 50, stdin) != NULL)
    {
        sscanf(entrada, "%d", &ano);
        printf("%d\n", eh_bi(ano));
    }

    return 0;
}
