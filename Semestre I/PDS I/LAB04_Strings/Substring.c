#include <stdio.h>
#include <string.h>

int main()
{
    int igual = 0, count = 0;
    char s[100], sub[100];

    fgets(s, 100, stdin);
    fgets(sub, 100, stdin);

    if (s[0] == '\n' || sub[0] == '\n')
    {
        printf("Não é substring\n");
        return 0;
    }

    for (int i = 0; i <= strlen(s) - strlen(sub); i++)
    {
        count = 0;

        for (int j = 0; j < strlen(sub) - 1; j++)
        {

            if (s[i + j] == sub[j])
            {
                count++;
            }
        }

        if (count == strlen(sub) - 1)
        {
            igual = 1;
            break;
        }
    }

    if (igual)
        printf("É substring\n");
    else
        printf("Não é substring\n");

    return 0;
}
