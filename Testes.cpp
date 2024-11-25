#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quantos(char *str, char c, int tamanho, char placeholder)
{
    if (tamanho > 1)
        quantos(str, c, tamanho - 1, placeholder);

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
    int *a = (int *)malloc(sizeof(int));
    char str[] = "jcbhjsahbehfhajhfhadaskjdbashjdhasdahsj";
    char caractere = 'a';

    char placeholder = '%';

    quantos(str, caractere, strlen(str), placeholder);
    printar(str, placeholder);

    return 0;
}
