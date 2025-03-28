#include "HeapInt.hpp"
#include <iostream>

HeapInt::HeapInt() : value(new int(0)) {}

HeapInt::HeapInt(int val) : value(new int(val)) {}

HeapInt::HeapInt(const HeapInt &other)
{
    value = new int(*other.value);
}

HeapInt::~HeapInt()
{
    delete value;
}

HeapInt &HeapInt::operator=(const HeapInt &other)
{
    if (this != &other)
    {
        delete value;
        value = new int(*other.value);
    }
    return *this;
}

HeapInt HeapInt::operator+(const HeapInt &other) const
{
    return HeapInt(*this->value + *other.value);
}
HeapInt &HeapInt::operator=(int att)
{
    delete value;         // Libera memória existente
    value = new int(att); // Aloca nova memória com o valor atribuído
    return *this;         // Permite encadeamento
}

std::ostream &operator<<(std::ostream &os, const HeapInt &obj)
{
    if (obj.value)
        os << *obj.value;
    else
        os << "(null)";
    return os;
}
std::istream &operator>>(std::istream &is, HeapInt &t)
{
    if (!t.value)
    {                      // Se o ponteiro `value` for nulo
        t.value = new int; // Aloca memória
    }
    is >> *t.value; // Lê o valor para o ponteiro
    return is;
}
HeapInt HeapInt::operator-(const HeapInt &dois) const
{
    return HeapInt(*this->value - *dois.value); // Retorna um novo HeapInt
}
bool HeapInt::operator==(const HeapInt &dois) const
{
    return *this->value == *dois.value;
}
