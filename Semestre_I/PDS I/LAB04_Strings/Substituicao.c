#include <stdio.h>

int main()
{
    int pos, i;
    char s[100], a, b;
    fgets(s, 100, stdin);

    scanf("%c ", &a);
    scanf("%c", &b);

    for (i = 0; s[i] != a && s[i] != '\0'; i++)
        pos = i + 1;

    if (s[i] != '\0')
        s[pos] = b;

    fputs(s, stdout);

    return 0;
}
