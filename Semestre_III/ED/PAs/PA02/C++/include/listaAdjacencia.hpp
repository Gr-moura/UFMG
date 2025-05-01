#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

#include "listaEncadeada.hpp"
class Vertice
{
  public:
    Vertice();
    ~Vertice();

    void NovaAresta(int w);
    void ImprimeVizinhos();
    int getGrau();

  private:
    int grau;
    // Lista encadeada de vizinhos
    ListaEncadeada<int> listaVizinhos;

    friend class ListaAdjacencia;
};
class ListaAdjacencia
{
  public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    void InsereVertice();
    void InsereAresta(int v, int w);
    int getQuantidadeVertices();
    int getQuantidadeArestas();

    int getGrauMinimo();
    int getGrauMaximo();

    void ImprimeVizinhos(int v);
    void Imprime();

  private:
    int quantidadeVertices;
    int quantidadeArestas;

    // Lista encadeada de vertices
    ListaEncadeada<Vertice> listaVertices;
};

#endif