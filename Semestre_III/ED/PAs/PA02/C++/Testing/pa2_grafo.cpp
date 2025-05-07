#include <algorithm> // Para std::min_element, std::max_element (usado no stub)
#include <iostream>
#include <limits> // Para std::numeric_limits (usado no stub)
#include <list>
#include <numeric> // Para std::accumulate (usado no stub)
#include <string>
#include <vector>
// --- Funções de Teste Unitário ---
#include "graph.hpp"

// Função auxiliar para verificar uma condição e imprimir resultado
bool check(const std::string &testName, const std::string &conditionDesc, bool condition)
{
    std::cout << "  [TEST] " << testName << " - " << conditionDesc << ": ";
    if (condition)
    {
        std::cout << "PASSOU" << std::endl;
        return true;
    }
    else
    {
        std::cout << "FALHOU" << std::endl;
        return false;
    }
}

// Testa o estado inicial de um grafo recém-criado
bool testInitialState()
{
    std::cout << "\n--- Testando Estado Inicial ---" << std::endl;
    Grafo g;
    bool passed = true;
    passed &= check("Estado Inicial", "QuantidadeVertices == 0", g.QuantidadeVertices() == 0);
    passed &= check("Estado Inicial", "QuantidadeArestas == 0", g.QuantidadeArestas() == 0);
    // Assumindo que graus para grafo vazio são 0
    passed &= check("Estado Inicial", "GrauMinimo == 0", g.GrauMinimo() == 0);
    passed &= check("Estado Inicial", "GrauMaximo == 0", g.GrauMaximo() == 0);
    return passed;
}

// Testa a inserção de vértices
bool testVertexInsertion()
{
    std::cout << "\n--- Testando Inserção de Vértices ---" << std::endl;
    Grafo g;
    bool passed = true;

    g.InsereVertice(); // Vértice 0
    passed &= check("Inserção Vértice Único", "QuantidadeVertices == 1", g.QuantidadeVertices() == 1);
    passed &= check("Inserção Vértice Único", "QuantidadeArestas == 0", g.QuantidadeArestas() == 0);
    passed &= check("Inserção Vértice Único", "GrauMinimo == 0", g.GrauMinimo() == 0);
    passed &= check("Inserção Vértice Único", "GrauMaximo == 0", g.GrauMaximo() == 0);

    g.InsereVertice(); // Vértice 1
    g.InsereVertice(); // Vértice 2
    passed &= check("Inserção Múltiplos Vértices", "QuantidadeVertices == 3", g.QuantidadeVertices() == 3);
    passed &= check("Inserção Múltiplos Vértices", "QuantidadeArestas == 0", g.QuantidadeArestas() == 0);

    return passed;
}

// Testa a inserção de arestas e atualização de graus
bool testEdgeInsertionAndDegrees()
{
    std::cout << "\n--- Testando Inserção de Arestas e Graus ---" << std::endl;
    Grafo g;
    bool passed = true;

    g.InsereVertice(); // Vértice 0
    g.InsereVertice(); // Vértice 1
    g.InsereVertice(); // Vértice 2
    g.InsereVertice(); // Vértice 3

    // Aresta 0 -- 1
    g.InsereAresta(0, 1);
    passed &= check("Aresta 0-1", "QuantidadeArestas == 1", g.QuantidadeArestas() == 2);
    passed &= check("Aresta 0-1", "GrauMinimo == 0", g.GrauMinimo() == 0); // Vértices 2 e 3 têm grau 0
    passed &= check("Aresta 0-1", "GrauMaximo == 1", g.GrauMaximo() == 1); // Vértices 0 e 1 têm grau 1

    // Aresta 1 -- 2
    g.InsereAresta(1, 2);
    passed &= check("Aresta 1-2", "QuantidadeArestas == 2", g.QuantidadeArestas() == 4);
    // Graus: V0=1, V1=2, V2=1, V3=0
    passed &= check("Aresta 1-2", "GrauMinimo == 0", g.GrauMinimo() == 0); // Vértice 3
    passed &= check("Aresta 1-2", "GrauMaximo == 2", g.GrauMaximo() == 2); // Vértice 1

    // Aresta 0 -- 2 (forma triângulo 0-1-2)
    g.InsereAresta(0, 2);
    passed &= check("Aresta 0-2", "QuantidadeArestas == 3", g.QuantidadeArestas() == 6);
    // Graus: V0=2, V1=2, V2=2, V3=0
    passed &= check("Aresta 0-2", "GrauMinimo == 0", g.GrauMinimo() == 0); // Vértice 3
    passed &= check("Aresta 0-2", "GrauMaximo == 2", g.GrauMaximo() == 2); // Vértices 0, 1, 2

    // Aresta 1 -- 3
    g.InsereAresta(1, 3);
    passed &= check("Aresta 1-3", "QuantidadeArestas == 4", g.QuantidadeArestas() == 8);
    // Graus: V0=2, V1=3, V2=2, V3=1
    passed &= check("Aresta 1-3", "GrauMinimo == 1", g.GrauMinimo() == 1); // Vértice 3
    passed &= check("Aresta 1-3", "GrauMaximo == 3", g.GrauMaximo() == 3); // Vértice 1

    return passed;
}

// Testa um grafo completo K3
bool testCompleteGraphK3()
{
    std::cout << "\n--- Testando Grafo Completo K3 ---" << std::endl;
    Grafo g;
    bool passed = true;

    g.InsereVertice(); // Vértice 0
    g.InsereVertice(); // Vértice 1
    g.InsereVertice(); // Vértice 2

    g.InsereAresta(0, 1);
    g.InsereAresta(0, 2);
    g.InsereAresta(1, 2);

    passed &= check("K3", "QuantidadeVertices == 3", g.QuantidadeVertices() == 3);
    passed &= check("K3", "QuantidadeArestas == 3", g.QuantidadeArestas() == 6);
    passed &= check("K3", "GrauMinimo == 2", g.GrauMinimo() == 2);
    passed &= check("K3", "GrauMaximo == 2", g.GrauMaximo() == 2);

    return passed;
}

// --- Função Principal para Rodar os Testes ---
// int main()
// {
//     std::cout << "===========================" << std::endl;
//     std::cout << "   INICIANDO TESTES GRAFO  " << std::endl;
//     std::cout << "===========================" << std::endl;

//     int testsPassed = 0;
//     int testsTotal = 0;

//     testsTotal++;
//     if (testInitialState())
//     {
//         testsPassed++;
//     }

//     testsTotal++;
//     if (testVertexInsertion())
//     {
//         testsPassed++;
//     }

//     testsTotal++;
//     if (testEdgeInsertionAndDegrees())
//     {
//         testsPassed++;
//     }

//     testsTotal++;
//     if (testCompleteGraphK3())
//     {
//         testsPassed++;
//     }

//     // Adicione chamadas para outras funções de teste aqui...

//     std::cout << "\n===========================" << std::endl;
//     std::cout << "    RESULTADO DOS TESTES   " << std::endl;
//     std::cout << "===========================" << std::endl;
//     std::cout << " Testes executados: " << testsTotal << std::endl;
//     std::cout << " Testes passaram:   " << testsPassed << std::endl;
//     std::cout << " Testes falharam:   " << (testsTotal - testsPassed) << std::endl;
//     std::cout << "===========================" << std::endl;

//     // Retorna 0 se todos passaram, 1 se algum falhou (útil para scripts)
//     return (testsPassed == testsTotal) ? 0 : 1;
// }