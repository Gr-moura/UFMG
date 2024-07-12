#include <stdio.h>

int main()
{
    int pos;
    char s[100];
    fgets(s, 100, stdin);

    for (int i = 0; s[i] != '\0'; i++)
        pos = i + 1;

    for (int i = pos; i >= 0; i--)
        printf("%c", s[i]);
    printf("\n");

    return 0;
}
