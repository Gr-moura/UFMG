#include <stdio.h>
#include <string.h>

int quantos(char *str, char c, int tamanho)
{
    int qt = 0;
    if (tamanho > 1)
        qt = quantos(str, c, tamanho - 1);

    if (str[tamanho - 1] == c)
        qt++;

    return qt;
}

int main()
{
    char buffer[100], str[100];
    char caractere;

    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", str);

    fgets(buffer, 100, stdin);
    sscanf(buffer, "%c", &caractere);

    char placeholder = '%';

    printf("%d\n", quantos(str, caractere, strlen(str)));

    return 0;
}
