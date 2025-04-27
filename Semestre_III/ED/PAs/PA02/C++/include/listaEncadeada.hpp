#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <iostream>
using namespace std;

template <typename T> class Celula
{
  public:
    Celula(T valor) : valor(valor), proximaCelula(nullptr) {}
    // ~Celula() {}

    T valor;
    Celula *proximaCelula;
};

template <typename T> class ListaEncadeada
{
  public:
    ListaEncadeada() : primeiraCelula(nullptr), ultimaCelula(nullptr), quantidadeCelulas(0) {}
    // ~ListaEncadeada() { Limpa(); }

    void InsereFim(T valor);
    void Imprime();
    // void Limpa();

    // --- Acesso por Índice (Operator[]) ---
    // Retorna referência para modificar/ler. Lança std::out_of_range se índice inválido.
    // CUIDADO: Operação O(n) - ineficiente para listas grandes/acesso frequente.
    T &operator[](int index);

    // Versão const: Retorna referência constante para leitura em listas const.
    // CUIDADO: Operação O(n) - ineficiente para listas grandes/acesso frequente.
    const T &operator[](int index) const;

    int getQuantidade();

  private:
    Celula<T> *primeiraCelula;
    Celula<T> *ultimaCelula;

    int quantidadeCelulas;
};

template <typename T> void ListaEncadeada<T>::InsereFim(T valor)
{
    Celula<T> *novaCelula = new Celula<T>(valor);
    if (quantidadeCelulas == 0)
    {
        primeiraCelula = novaCelula;
        ultimaCelula = novaCelula;
    }
    else
    {
        ultimaCelula->proximaCelula = novaCelula;
        ultimaCelula = novaCelula;
    }
    quantidadeCelulas++;
}

template <typename T> void ListaEncadeada<T>::Imprime()
{
    Celula<T> *atual = primeiraCelula;
    while (atual != nullptr)
    {
        cout << atual->valor << " ";
        atual = atual->proximaCelula;
    }
    cout << endl;
}

// template <typename T> void ListaEncadeada<T>::Limpa()
// {
//     Celula<T> *atual = primeiraCelula;
//     while (atual != nullptr)
//     {
//         Celula<T> *proxima = atual->proximaCelula;
//         delete atual;
//         atual = proxima;
//     }
//     primeiraCelula = nullptr;
//     ultimaCelula = nullptr;
//     quantidadeCelulas = 0;
// }

template <typename T> int ListaEncadeada<T>::getQuantidade()
{
    return quantidadeCelulas;
}

// --- Implementação do Operator[] ---
// Versão não-const: retorna T&
template <typename T> T &ListaEncadeada<T>::operator[](int index)
{
    if (index < 0 or index >= quantidadeCelulas) throw "Índice fora dos limites da lista encadeada.";

    Celula<T> *atual = primeiraCelula;
    for (int i = 0; i < index; ++i)
        atual = atual->proximaCelula;

    return atual->valor;
}

// Versão const: retorna const T&
template <typename T> const T &ListaEncadeada<T>::operator[](int index) const
{
    if (index < 0 or index >= quantidadeCelulas) throw "Índice fora dos limites da lista encadeada (const access).";

    Celula<T> *atual = primeiraCelula;
    for (std::size_t i = 0; i < index; ++i)
        atual = atual->proximaCelula;

    // Retorna a referência constante ao valor do nó encontrado
    return atual->valor;
}

#endif