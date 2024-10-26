#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("cadê o nome trouxão\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    int a = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
        if (c == 'a')
            a++;

    printf("%d\n", a);

    fclose(file);

    return EXIT_SUCCESS;
}
