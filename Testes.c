#include <stdio.h>

int main()
{
    char *strings[5];

    printf("%p\n", strings[0]);
    strings[0] = "Hello World!";
    printf("%p\n", strings[0]);
    printf("%p\n\n", &strings[0][1]);

    printf("%p\n", strings[1]);
    strings[1] = "Hello World!";
    printf("%p", &strings[1]);
    return 0;
}
