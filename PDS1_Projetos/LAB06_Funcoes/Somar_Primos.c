#include <stdio.h>
#include <string.h>

long long int Primo(long long int n)
{

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

long long int Soma_Primos(int parar)
{
    long long int soma = 0;
    for (long long int i = 2; parar != 0; i++)
    {
        if (Primo(i))
        {
            soma += i;
            parar--;
        }
    }

    return soma;
}

int main()
{
    long long int num;
    char entrada[50];
    while (fgets(entrada, 50, stdin) != NULL)
    {
        sscanf(entrada, "%lld", &num);
        printf("%lld\n", Soma_Primos(num));
    }

    return 0;
}
