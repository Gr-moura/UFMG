#include "graph.hpp"
#include <iostream>
using namespace std;

/*
Recebe uma operação a ser realizada com o grafo pela linha
de comando. As operações são:

❑ “-d” Dados básicos: Deve imprimir na tela, um valor por
linha: a quantidade de vértices e de arestas do grafo, o
grau mínimo e o máximo.

❑ “-n” Vizinhanças: Deve imprimir os vizinhos de cada um
dos vértices. Todos os vizinhos de um vértice devem estar
na mesma linha separados por um espaço em branco e
encerrando com uma quebra de linha.

❑ “-k” : Deve imprimir 1 caso o grafo de entrada seja um
grafo completo e 0 caso contrário.

2. Recebe os dados de um grafo pela entrada padrão.
*/

int receberArgumento(const char *comando)
{
    int i = 0;
    while (comando[i] != '\0' && comando[i] != '-')
        i++;

    if (comando[i] == '\0') throw "Argumento inválido";

    switch (comando[i + 1])
    {
        case 'd': return 1;
        case 'n': return 2;
        case 'k': return 3;
        default: throw "Argumento inválido";
    }
}

Grafo lerGrafo()
{
    Grafo g;

    int nVertices;
    cin >> nVertices;

    for (int i = 0; i < nVertices; i++)
    {
        int nArestas;
        cin >> nArestas;

        g.InsereVertice();
        for (int j = 0; j < nArestas; j++)
        {
            int vizinho;
            cin >> vizinho;

            g.InsereAresta(i, vizinho);
        }
    }

    return g;
}

void dadosBasicos(Grafo &g)
{
    cout << g.QuantidadeVertices() << endl;
    cout << g.QuantidadeArestas() << endl;
    cout << g.GrauMinimo() << endl;
    cout << g.GrauMaximo() << endl;
}

void vizinhanca(Grafo &g)
{
    for (int i = 0; i < g.QuantidadeVertices(); i++)
    {
        g.ImprimeVizinhos(i);
    }
}

bool isCompleto(Grafo &g)
{
    int nVertices = g.QuantidadeVertices();
    int nArestas = g.QuantidadeArestas();

    if (nArestas == (nVertices * (nVertices - 1))) return true;
    else return false;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ./pa2.out -x" << endl;
        return 0;
    }

    int comando = receberArgumento(argv[1]);

    Grafo g = lerGrafo();

    switch (comando)
    {
        case 1: dadosBasicos(g); break;
        case 2: vizinhanca(g); break;
        case 3: cout << isCompleto(g); break;
        default: cout << "Comando inválido" << endl; break;
    }

    return 0;
}