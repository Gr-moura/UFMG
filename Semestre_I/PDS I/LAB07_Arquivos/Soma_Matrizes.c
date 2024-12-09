#include <stdio.h>
#include <stdlib.h>
int ehnum(char c)
{
    if (c - '0' >= 0 && c - '0' <= 9)
        return 1;

    return 0;
}

int main(int argc, char **argv)
{
    /*
     if (argc < 2)
    {
        printf("cadê o nome trouxão\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    */

    char nome[100];
    scanf("%s", nome);

    FILE *file = fopen(nome, "rb");

    if (file == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    long long soma[25] = {0};
    long long a = 0;
    long long temp;

    char c;

    while (fread(&c, sizeof(char), 1, file))
    {
        if (ehnum(c))
        {
            fseek(file, -1, SEEK_CUR);
            temp = 0;

            while (1)
            {
                fread(&c, sizeof(char), 1, file);

                if (ehnum(c))
                {
                    temp = 10 * temp + c - '0';
                }

                else
                    break;
            }

            soma[a] += temp;
            a++;
            a %= 25;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        if (i % 5 == 0 && i != 0)
            printf("\n");

        printf("%lld ", soma[i]);
    }
    printf("\n");

    fclose(file);

    return EXIT_SUCCESS;
}
