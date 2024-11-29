#include <stdio.h>
int main()
{
    int n, x0, x1, x2;
    scanf("%d %d %d ", &n, &x0, &x1);
    printf("X0: %d\nX1: %d\n", x0, x1);

    for (int i = 2; i <= n; i++)
    {
        x2 = 4 * x1 - 2 * x0;
        printf("X%d: %d\n", i, x2);
        x0 = x1;
        x1 = x2;
    }
}
