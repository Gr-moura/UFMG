#include <stdio.h>
#include <string.h>

void tirar(char *str, char c, int tamanho, char placeholder)
{
    if (tamanho > 1)
        tirar(str, c, tamanho - 1, placeholder);

    if (str[tamanho - 1] == c)
        str[tamanho - 1] = placeholder;
}

void printar(char *str, char placeholder)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != placeholder)
            printf("%c", str[i]);
    }

    printf("\n");
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

    tirar(str, caractere, strlen(str), placeholder);
    printar(str, placeholder);

    return 0;
}
