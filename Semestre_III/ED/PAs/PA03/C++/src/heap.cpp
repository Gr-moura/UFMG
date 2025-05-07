#include "heap.hpp"

Heap::Heap(int maxsize) : tamanho(0), data(new int[maxsize]) {}

Heap::~Heap()
{
    delete[] data;
}

bool Heap::Vazio()
{
    return tamanho == 0;
}

int Heap::GetAncestral(int pos)
{
    if (Vazio()) return -1;
    return (pos - 1) / 2;
}

int Heap::GetSucessorDir(int pos)
{
    if (Vazio()) return -1;

    int sucessor = 2 * pos + 2;
    if (sucessor >= tamanho) return -1;

    return sucessor;
}

int Heap::GetSucessorEsq(int pos)
{
    if (Vazio()) return -1;

    int sucessor = 2 * pos + 1;
    if (sucessor >= tamanho) return -1;

    return sucessor;
}

void Heap::Inserir(int x)
{
    data[tamanho] = x;

    HeapifyPorBaixo(tamanho);
    tamanho++;
}

void Heap::HeapifyPorBaixo(int pos)
{
    if (GetAncestral(pos) == -1) return;
    if (data[pos] >= data[GetAncestral(pos)]) return;

    int temp = data[pos];
    data[pos] = data[GetAncestral(pos)];
    data[GetAncestral(pos)] = temp;

    HeapifyPorBaixo(GetAncestral(pos));
}

void Heap::HeapifyPorCima(int pos)
{
    if (GetSucessorEsq(pos) == -1) return;

    int posMenorSucessor = GetSucessorEsq(pos);
    if (GetSucessorDir(pos) != -1)
        posMenorSucessor = data[posMenorSucessor] <= data[GetSucessorDir(pos)] ? posMenorSucessor : GetSucessorDir(pos);

    if (data[pos] <= data[posMenorSucessor]) return;

    int temp = data[pos];
    data[pos] = data[posMenorSucessor];
    data[posMenorSucessor] = temp;

    HeapifyPorCima(posMenorSucessor);
}

int Heap::Remover()
{
    if (Vazio()) return -1;

    int retorno = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;

    HeapifyPorCima(0);

    return retorno;
}