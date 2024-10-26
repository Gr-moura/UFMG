#include <stdio.h>

int main()
{
    float celsius;
    scanf("%f ", &celsius);
    printf("%.0f", (celsius * 1.8 + 32));

    return 0;
}
