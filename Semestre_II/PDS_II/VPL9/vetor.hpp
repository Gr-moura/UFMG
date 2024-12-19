#ifndef VETOR_H
#define VETOR_H

#include <iostream>
using namespace std;

template <typename T> class Vetor
{
  private:
    int maxSize;
    int nElementos;
    T *vetor;

  public:
    Vetor(int n) : maxSize(n), nElementos(0) { this->vetor = new T[n]; }
    Vetor(const Vetor &copia) : maxSize(copia.maxSize), nElementos(copia.nElementos)
    {
        this->vetor = new T[maxSize];

        for (int i = 0; i < nElementos; ++i)
            this->vetor[i] = copia.vetor[i];
    }

    ~Vetor() { delete[] vetor; }

    void SetElemento(int i, T x)
    {
        if (i >= nElementos)
            throw out_of_range("Index out of range");

        this->vetor[i] = x;
    }

    const T &GetElemento(int i) const
    {
        if (i >= nElementos)
            throw std::overflow_error("Max size reached");

        return this->vetor[i];
    }

    void AdicionaElemento(T x)
    {
        if (nElementos < maxSize)
            this->vetor[nElementos++] = x;

        else
            throw std::overflow_error("Max size reached");
    }

    void Imprime() const
    {
        for (int i = 0; i < nElementos; i++)
            cout << this->vetor[i] << " ";

        cout << endl;
    }
};

#endif