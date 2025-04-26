#include "listaAdjacencia.hpp"
#include <iostream>

TipoCelula::TipoCelula() : item(-1), proximo(nullptr) {}
TipoCelula::TipoCelula(int item) : item(item), proximo(nullptr) {}
TipoCelula::TipoCelula(int item, TipoCelula *proximo) : item(item), proximo(proximo) {}

int TipoCelula::GetItem()
{
    return item;
}

TipoCelula *TipoCelula::GetProximo()
{
    return proximo;
}

void TipoCelula::SetItem(int item)
{
    this->item = item;
}

void TipoCelula::SetProximo(TipoCelula *proximo)
{
    this->proximo = proximo;
}

ListaEncadeada::ListaEncadeada() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

ListaEncadeada::~ListaEncadeada()
{
    Limpa();
}

int ListaEncadeada::GetItem(int pos)
{
    TipoCelula *p = Posiciona(pos);
    if (p != nullptr) return p->GetItem();
    else throw "Não existe elemento na posição informada";
}

void ListaEncadeada::SetItem(int item, int pos)
{
    TipoCelula *p = Posiciona(pos);
    if (p != nullptr) p->SetItem(item);
    else throw "Não existe elemento na posição informada";
}

void ListaEncadeada::InsereInicio(int item)
{
    TipoCelula *nova = new TipoCelula(item, primeiro);
    primeiro = nova;
    if (ultimo == nullptr) ultimo = nova;
    tamanho++;
}

void ListaEncadeada::InsereFinal(int item)
{
    TipoCelula *nova = new TipoCelula(item);
    if (ultimo != nullptr) ultimo->SetProximo(nova);
    else primeiro = nova;
    ultimo = nova;
    tamanho++;
}

void ListaEncadeada::InserePosicao(int item, int pos)
{
    if (pos == 0) InsereInicio(item);
    else
    {
        TipoCelula *p = Posiciona(pos - 1);
        if (p != nullptr)
        {
            TipoCelula *nova = new TipoCelula(item, p->GetProximo());
            p->SetProximo(nova);
            if (nova->GetProximo() == nullptr) ultimo = nova;
        }
    }
    tamanho++;
}

int ListaEncadeada::RemoveInicio()
{
    if (primeiro != nullptr)
    {
        tamanho--;

        TipoCelula *p = primeiro;
        int item = p->GetItem();
        primeiro = primeiro->GetProximo();

        delete p;
        if (primeiro == nullptr) ultimo = nullptr;
        return item;
    }
    else throw "Lista vazia";
}

int ListaEncadeada::RemoveFinal()
{
    if (ultimo != nullptr)
    {
        tamanho--;

        TipoCelula *p = Posiciona(tamanho - 2);
        if (p != nullptr) p->SetProximo(nullptr);
        else primeiro = nullptr;

        int item = ultimo->GetItem();
        delete ultimo;
        ultimo = p;
        if (ultimo == nullptr) primeiro = nullptr;
        else ultimo->SetProximo(nullptr);
        return item;
    }
    else throw "Lista vazia";
}

int ListaEncadeada::RemovePosicao(int pos)
{
    if (pos == 0) return RemoveInicio();

    TipoCelula *p = Posiciona(pos - 1);

    if (p != nullptr)
    {
        TipoCelula *q = p->GetProximo();
        if (q != nullptr)
        {
            int item = q->GetItem();
            p->SetProximo(q->GetProximo());
            delete q;
            tamanho--;
            return item;
        }
        else throw "Não existe elemento na posição informada";
    }
    else throw "Não existe elemento na posição informada";
}

int ListaEncadeada::Pesquisa(int c)
{
    TipoCelula *p = primeiro;
    int pos = 0;
    while (p != nullptr)
    {
        if (p->GetItem() == c) return pos;
        p = p->GetProximo();
        pos++;
    }
    return -1;
}

void ListaEncadeada::Imprime()
{
    TipoCelula *p = primeiro;
    while (p != nullptr)
    {
        std::cout << p->GetItem() << " ";
        p = p->GetProximo();
    }
    std::cout << std::endl;
}

void ListaEncadeada::Limpa()
{
    while (primeiro != nullptr)
        RemoveInicio();
}

TipoCelula *ListaEncadeada::Posiciona(int pos)
{
    TipoCelula *p = primeiro;
    for (int i = 0; i < pos && p != nullptr; i++)
        p = p->GetProximo();
    return p;
}

ListaAdjacencia::ListaAdjacencia() : vertices(),