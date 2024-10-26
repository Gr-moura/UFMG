#include <stdio.h>
#include <string.h>

int main()
{
    int pos;
    char s1[100], s2[100];

    fgets(s1, 100, stdin);
    fgets(s2, 100, stdin);

    for (int i = 0; s1[i] >= 'a' && s1[i] <= 'z'; i++)
        pos = i + 1;
    s1[pos] = '\0';

    for (int i = 0; s2[i] >= 'a' && s2[i] <= 'z'; i++)
        pos = i + 1;
    s2[pos] = '\0';

    strcat(s1, s2);

    printf("%s\n", s1);

    return 0;
}
