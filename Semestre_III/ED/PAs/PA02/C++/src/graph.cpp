#include "graph.hpp"

Grafo::Grafo() : vertices(ListaAdjacencia()) {}

// Grafo::~Grafo()
// {
//     // Destrói a lista de adjacência
//     vertices.~ListaAdjacencia();
// }

void Grafo::InsereVertice()
{
    // Insere um novo vértice na lista de adjacência
    vertices.InsereVertice();
}

void Grafo::InsereAresta(int v, int w)
{
    // Insere uma aresta entre os vértices v e w
    vertices.InsereAresta(v, w);
}

int Grafo::QuantidadeVertices()
{
    // Retorna a quantidade de vértices no grafo
    return vertices.getQuantidadeVertices();
}

int Grafo::QuantidadeArestas()
{
    // Retorna a quantidade de arestas no grafo
    return vertices.getQuantidadeArestas();
}

int Grafo::GrauMinimo()
{
    // Retorna o grau mínimo entre os vértices do grafo
    return vertices.getGrauMinimo();
}

int Grafo::GrauMaximo()
{
    // Retorna o grau máximo entre os vértices do grafo
    return vertices.getGrauMaximo();
}

void Grafo::ImprimeVizinhos(int v)
{
    // Imprime os vizinhos do vértice v
    vertices.ImprimeVizinhos(v);
}
