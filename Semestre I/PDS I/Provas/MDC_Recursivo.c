/*
    Em matemática, o algoritmo de Euclides é um método simples e eficiente de encontrar o máximo divisor comum entre
    dois números inteiros diferentes de zero. É um dos algoritmos mais antigos, conhecido desde que surgiu nos Livros
    VII e X da obra Elementos de Euclides por volta de 300 a.C.. O algoritmo não exige qualquer fatoração.

    O MDC de dois números inteiros é o maior número inteiro que divide ambos sem deixar resto. O algoritmo de Euclides é
    baseado no princípio de que o MDC não muda se o menor número for subtraído ao maior. Por exemplo, 21 é o MDC de 252
    e 105 (252 = 21 × 12; 105 = 21 × 5); já que 252 − 105 = 147, o MDC de 147 e 105 é também 21. Como o maior dos dois
    números é reduzido, a repetição deste processo irá gerar sucessivamente números menores, até convergir em zero.Nesse
    momento, o MDC é o outro número inteiro, maior que zero.

    Implemente a versão recursiva do algoritmo de Euclides
    O seu programa deve ter uma função main que leia 2 números inteiros e chame a função

    int mdc(int a, int b).

    O seu programa deve imprimir apenas o valor do mdc dos dois números informados (umnúmero inteiro).

    Obs : não será aceita a versão iterativa do algoritmo de Euclides.
*/

#include <stdio.h>

int mdc(int a, int b)
{
    if (a == b)
        return a;

    if (a > b)
        return mdc(a - b, b);

    return mdc(b, a);
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);

    printf("%d", mdc(a, b));

    return 0;
}
