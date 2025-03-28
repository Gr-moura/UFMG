#include "vetor.hpp"
#include <iostream>
#include <string>

using namespace std;

void Teste1()
{
    int n = 10;
    int x;
    Vetor<int> a(n);

    for (int i = 0; i < n; i++)
    {
        a.AdicionaElemento(i);
    }

    x = 0;
    for (int i = 0; i < n; i++)
    {
        x += a.GetElemento(i);
    }
    cout << x << endl;
}

void Teste2()
{
    Vetor<string> a(5);
    a.AdicionaElemento("Isso");
    a.AdicionaElemento("eh");
    a.AdicionaElemento("um");
    a.AdicionaElemento("teste");

    Vetor<string> b = a;
    b.SetElemento(2, "outro");

    a.Imprime();
    b.Imprime();
}

void Teste3()
{
    Vetor<char> a(5);

    for (char i = 'a'; i <= 'e'; i++)
        a.AdicionaElemento(i);

    Vetor<char> b = a;
    b.SetElemento(1, b.GetElemento(4));
    b.SetElemento(2, 'i');
    b.SetElemento(3, 'o');
    b.SetElemento(4, 'u');

    a.Imprime();
    b.Imprime();
}

int main()
{
    int op;

    cin >> op;

    if (op == 1)
        Teste1();
    else if (op == 2)
        Teste2();
    else if (op == 3)
        Teste3();
}