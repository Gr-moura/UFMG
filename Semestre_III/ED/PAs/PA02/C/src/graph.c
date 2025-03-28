#include "graph.h"
#include <stdlib.h>

/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Nenhuma outra alteração neste arquivo é permitida
 */

/*  Você deve implementar struct s_grafo como um TAD que irá armazenar
 * os dados de um grafo. Lembrando que a estratégia utilizada deve ser uma
 * lista de adjacencia e deve ser implementada como uma lista encadeada.
 */

struct s_grafo
{
    int num_vertices;
    int num_arestas;
    int minGrau;
    int maxGrau;

    int *adjList;
};

Grafo *NovoGrafo()
{
    Grafo *graph = calloc(1, sizeof(Grafo));
    if (graph == NULL)
    {
        return NULL;
    }

    graph->num_vertices = 0;
    graph->num_arestas = 0;
    graph->minGrau = 0;
    graph->maxGrau = 0;

    graph->adjList = NULL;

    return graph;
}

void DeletaGrafo(Grafo *g)
{
    // Deletar lista de adj

    free(g);
}

void InsereVertice(Grafo *g)
{
    g->num_vertices++;
    g->adjList = realloc(g->adjList, g->num_vertices * sizeof(int));
}

void InsereAresta(Grafo *g, int v, int w)
{
    // Ver antes e depois, para botar em ordem
}

int QuantidadeVertices(Grafo *g);
int QuantidadeArestas(Grafo *g);

int GrauMinimo(Grafo *g);
int GrauMaximo(Grafo *g);

void ImprimeVizinhos(Grafo *g, int v);