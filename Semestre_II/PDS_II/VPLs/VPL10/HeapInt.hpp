#ifndef HEAPINT_H
#define HEAPINT_H

#include <iostream>
using namespace std;

class HeapInt
{
  private:
    int *value;

  public:
    // Construtores e destrutores
    HeapInt();
    HeapInt(int val);
    HeapInt(const HeapInt &other);
    ~HeapInt();

    // Sobrecarga do operador de atribuição
    HeapInt &operator=(const HeapInt &other);
    HeapInt &operator=(int val);

    // Sobrecarga de operadores aritméticos
    HeapInt operator+(const HeapInt &other) const;
    HeapInt operator-(const HeapInt &other) const;

    // Sobrecarga de igualdade
    bool operator==(const HeapInt &other) const;

    // Sobrecarga de entrada e saída
    friend std::istream &operator>>(std::istream &is, HeapInt &obj);
    friend std::ostream &operator<<(std::ostream &os, const HeapInt &obj);
};

#endif