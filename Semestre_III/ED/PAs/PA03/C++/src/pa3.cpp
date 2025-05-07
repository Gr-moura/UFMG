#include "heap.hpp"
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    Heap heap(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        heap.Inserir(x);
    }

    while (!heap.Vazio())
        cout << heap.Remover() << " ";

    cout << endl;

    return 0;
}