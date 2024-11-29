/*

Faça uma função chamada primo que recebe como parâmetro um inteiro m e dois
outros inteiros p1 e p2 passados por referência. Ou seja, você deve passar o endereço
das variáveis e usar os conceitos de ponteiros ensinados na última aula. A função deve
armazenar em p1 o maior número primo que é menor do que m e deve armazenar em
p2 o menor número primo que é maior do que m. Você pode adaptar os métodos de
identificação de números primos discutidos em aulas anteriores. Cabeçalho: void
primos(int m, int *p1, int *p2);

*/

#include <stdio.h>

int eh_primo(int num)
{
    if (num < 2)
        return 0;

    if (num != 2 && num % 2 == 0)
        return 0;

    for (int i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void primos(int m, int *p1, int *p2)
{
    for (int i = m - 1; i >= 2; i--)
    {
        if (eh_primo(i))
        {
            *p1 = i;
            break;
        }
    }

    for (int i = m + 1;; i++)
    {
        if (eh_primo(i))
        {
            *p2 = i;
            break;
        }
    }
}

int main()
{
    int base;
    int p1, p2;

    scanf("%d", &base);

    primos(base, &p1, &p2);

    printf("%d\n%d", p1, p2);

    return 0;
}
