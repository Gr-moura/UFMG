#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buffer[100];
    char fileName[100];

    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", fileName);

    FILE *file = fopen(fileName, "rb");

    if (file == NULL)
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    int a = 0;
    char c;
    while (1)
    {
        fread(&c, sizeof(char), 1, file);

        if (feof(file))
            break;

        if (c == 'a')
            a++;
    }

    printf("%d\n", a);

    fclose(file);

    return EXIT_SUCCESS;
}
