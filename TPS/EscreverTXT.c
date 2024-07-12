#include <stdio.h>

int main()
{
    FILE *file = fopen("input.txt", "w");
    fprintf(file, "Albert Einstein\n");
    fprintf(file, "1801\n");

    fclose(file);
    return 0;
}
