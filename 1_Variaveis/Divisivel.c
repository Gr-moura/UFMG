#include <stdio.h>

int main()
{
    int x, y, z;
    scanf("%d %d %d ", &x, &y, &z);

    if (!(x % y) && !(x % z))
    {
        printf("O número é divisível");
    }
    else
    {
        printf("O número não é divisível");
    }

    return 0;
}
