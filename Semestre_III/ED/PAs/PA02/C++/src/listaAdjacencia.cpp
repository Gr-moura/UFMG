#include "listaAdjacencia.hpp"
#include <iostream>
using namespace std;

Vertice::Vertice() : listaVizinhos()
{
    // Inicializa o grau do vertice
    this->grau = 0;
}

Vertice::~Vertice()
{
    // Destrutor vazio
    this->grau = 0;
    listaVizinhos.Limpa();
}

void Vertice::NovaAresta(int w)
{
    // Adiciona um vizinho
    listaVizinhos.InsereFim(w);
    grau++;
}

void Vertice::ImprimeVizinhos()
{
    // Imprime os vizinhos do vertice
    for (int i = 0; i < grau; i++)
    {
        cout << listaVizinhos[i] << " ";
    }
    cout << endl;
}

int Vertice::getGrau()
{
    // Retorna o grau do vertice
    return grau;
}

ListaAdjacencia::ListaAdjacencia() : listaVertices()
{
    // Inicializa o grafo
    quantidadeArestas = 0;
    quantidadeVertices = 0;
}

ListaAdjacencia::~ListaAdjacencia()
{
    listaVertices.Limpa();
}

void ListaAdjacencia::InsereVertice()
{
    // Adiciona um vertice
    Vertice v;
    listaVertices.InsereFim(v);
    quantidadeVertices++;
}

void ListaAdjacencia::InsereAresta(int v, int w)
{
    // Adiciona uma aresta entre os vertices v e w
    listaVertices[v].NovaAresta(w);
    quantidadeArestas++;
}

int ListaAdjacencia::getQuantidadeVertices()
{
    // Retorna a quantidade de vertices
    return quantidadeVertices;
}

int ListaAdjacencia::getQuantidadeArestas()
{
    // Retorna a quantidade de arestas
    return quantidadeArestas;
}

int ListaAdjacencia::getGrauMinimo()
{
    // Retorna o grau minimo do grafo
    if (quantidadeVertices == 0) return 0;
    int grauMinimo = listaVertices[0].getGrau();
    for (int i = 1; i < quantidadeVertices; i++)
    {
        grauMinimo = listaVertices[i].getGrau();
        if (listaVertices[i].getGrau() < grauMinimo) grauMinimo = listaVertices[i].getGrau();
    }

    return grauMinimo;
}

int ListaAdjacencia::getGrauMaximo()
{
    // Retorna o grau maximo do grafo
    int grauMaximo = 0;
    for (int i = 0; i < quantidadeVertices; i++)
    {
        if (listaVertices[i].getGrau() > grauMaximo) grauMaximo = listaVertices[i].getGrau();
    }

    return grauMaximo;
}

void ListaAdjacencia::ImprimeVizinhos(int v)
{
    // Imprime os vizinhos do vertice v
    listaVertices[v].ImprimeVizinhos();
}

void ListaAdjacencia::Imprime()
{
    // Imprime o grafo
    for (int i = 0; i < quantidadeVertices; i++)
    {
        cout << i << ": ";
        ImprimeVizinhos(i);
    }
}