#include <stdio.h>
#include <string.h>

int ehprimo(long long int n)
{
    if (n < 2)
        return -1;

    if (n != 2 && n % 2 == 0)
        return 0;

    for (long long int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char buffer[100];
    long long int num;

    fgets(buffer, 100, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    do
    {
        sscanf(buffer, "%lld", &num);
        printf("%d\n", ehprimo(num));

        fgets(buffer, 100, stdin);
        buffer[strlen(buffer) - 1] = '\0';

    } while (strlen(buffer) > 0);

    return 0;
}
