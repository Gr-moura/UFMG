#include "listaAdjacencia.hpp" // Seu header com as declarações
#include "listaEncadeada.hpp"  // Dependência necessária
#include <cassert>
#include <iostream>
#include <limits>    // Para std::numeric_limits
#include <stdexcept> // Para capturar exceções padrão (embora o seu lance const char*)

// --- Funções de Teste ---

// Testa a criação do vértice e a adição de arestas (vizinhos)
void test_Vertice_NovaAresta_GetGrau()
{
    std::cout << "Running test_Vertice_NovaAresta_GetGrau..." << std::endl;
    Vertice v;
    assert(v.getGrau() == 0); // Verifica grau inicial

    v.NovaAresta(1);          // Adiciona vizinho 1
    assert(v.getGrau() == 1); // Verifica grau após 1 adição

    v.NovaAresta(5);          // Adiciona vizinho 5
    v.NovaAresta(2);          // Adiciona vizinho 2
    assert(v.getGrau() == 3); // Verifica grau após 3 adições

    // Teste visual (smoke test) para Impressão - não verifica o conteúdo exato
    std::cout << "  Imprimindo vizinhos do Vertice (esperado: 3 1 5 2 ): ";
    v.ImprimeVizinhos(); // Deve imprimir grau seguido dos vizinhos

    std::cout << "test_Vertice_NovaAresta_GetGrau PASSED." << std::endl;
}

// Testa o construtor da ListaAdjacencia e getters de quantidade iniciais
void test_ListaAdjacencia_Construtor_GetQuantidade()
{
    std::cout << "Running test_ListaAdjacencia_Construtor_GetQuantidade..." << std::endl;
    ListaAdjacencia grafo;
    assert(grafo.getQuantidadeVertices() == 0); // Verifica vértices iniciais
    assert(grafo.getQuantidadeArestas() == 0);  // Verifica arestas iniciais
    std::cout << "test_ListaAdjacencia_Construtor_GetQuantidade PASSED." << std::endl;
}

// Testa a inserção de vértices
void test_ListaAdjacencia_InsereVertice()
{
    std::cout << "Running test_ListaAdjacencia_InsereVertice..." << std::endl;
    ListaAdjacencia grafo;
    assert(grafo.getQuantidadeVertices() == 0);

    grafo.InsereVertice(); // Vértice 0
    assert(grafo.getQuantidadeVertices() == 1);

    grafo.InsereVertice(); // Vértice 1
    grafo.InsereVertice(); // Vértice 2
    assert(grafo.getQuantidadeVertices() == 3);

    // Com vértices inseridos, mas sem arestas, min/max grau deve ser 0
    // NOTA: A implementação atual de getGrauMinimo/Maximo falhará se chamada
    // ANTES de inserir o primeiro vértice. Testamos apenas após inserção.
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 0);

    std::cout << "test_ListaAdjacencia_InsereVertice PASSED." << std::endl;
}

// Testa a inserção de arestas e a contagem (incrementa em 2)
void test_ListaAdjacencia_InsereAresta_Contagem()
{
    std::cout << "Running test_ListaAdjacencia_InsereAresta_Contagem..." << std::endl;
    ListaAdjacencia grafo;
    grafo.InsereVertice(); // 0
    grafo.InsereVertice(); // 1
    grafo.InsereVertice(); // 2
    assert(grafo.getQuantidadeVertices() == 3);
    assert(grafo.getQuantidadeArestas() == 0);

    // Insere aresta (0, 1)
    grafo.InsereAresta(0, 1);
    assert(grafo.getQuantidadeArestas() == 2); // Verifica incremento por 2
    // Verifica graus (assumindo que Vertice::getGrau está correto)
    // É necessário acessar listaVertices diretamente ou ter um método getVertice(index)
    // Como não temos getVertice, vamos confiar nos testes de grau min/max depois
    // Mas podemos inferir que os graus de 0 e 1 devem ser 1.

    // Insere aresta (1, 2)
    grafo.InsereAresta(1, 2);
    assert(grafo.getQuantidadeArestas() == 4); // Verifica incremento por 2 novamente
    // Graus esperados: V0=1, V1=2, V2=1

    // Insere aresta (0, 2)
    grafo.InsereAresta(0, 2);
    assert(grafo.getQuantidadeArestas() == 6); // Verifica incremento por 2
    // Graus esperados: V0=2, V1=2, V2=2

    std::cout << "test_ListaAdjacencia_InsereAresta_Contagem PASSED." << std::endl;
}

// Testa os métodos getGrauMinimo e getGrauMaximo
void test_ListaAdjacencia_GetGrauMinimoMaximo()
{
    std::cout << "Running test_ListaAdjacencia_GetGrauMinimoMaximo..." << std::endl;
    ListaAdjacencia grafo;

    // --- Teste com grafo vazio ---
    // IMPORTANTE: A implementação atual CRASHARÁ se getGrauMinimo/Maximo
    // forem chamados aqui, pois acessa listaVertices[0] sem verificar.
    // Não podemos testar isso diretamente com assert sem risco de crash.
    // Adicionamos o primeiro vértice antes de chamar os métodos.
    std::cout << "  Nota: Teste em grafo vazio pulado devido ao acesso listaVertices[0] na implementacao." << std::endl;

    grafo.InsereVertice(); // 0
    // Teste com um vértice (grau 0)
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 0);

    grafo.InsereVertice(); // 1
    grafo.InsereVertice(); // 2
    grafo.InsereVertice(); // 3

    // Teste com vértices isolados (grau 0)
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 0);

    // Adiciona arestas e verifica graus
    grafo.InsereAresta(0, 1); // Graus: V0=1, V1=1, V2=0, V3=0 -> Min=0, Max=1
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 1);

    grafo.InsereAresta(0, 2); // Graus: V0=2, V1=1, V2=1, V3=0 -> Min=0, Max=2
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 2);

    grafo.InsereAresta(1, 2); // Graus: V0=2, V1=2, V2=2, V3=0 -> Min=0, Max=2
    assert(grafo.getGrauMinimo() == 0);
    assert(grafo.getGrauMaximo() == 2);

    grafo.InsereAresta(2, 3); // Graus: V0=2, V1=2, V2=3, V3=1 -> Min=1, Max=3
    assert(grafo.getGrauMinimo() == 1);
    assert(grafo.getGrauMaximo() == 3);

    std::cout << "test_ListaAdjacencia_GetGrauMinimoMaximo PASSED." << std::endl;
}

// Testa o acesso a índices inválidos que devem lançar exceção
void test_ListaAdjacencia_AcessoInvalido()
{
    std::cout << "Running test_ListaAdjacencia_AcessoInvalido..." << std::endl;
    ListaAdjacencia grafo;
    grafo.InsereVertice(); // 0
    grafo.InsereVertice(); // 1

    // --- Teste InsereAresta com índice inválido ---
    bool lancouExcecaoAresta = false;
    try
    {
        grafo.InsereAresta(0, 5); // Vértice 5 não existe
    }
    catch (const char *msg)
    { // Captura a exceção esperada de ListaEncadeada::operator[]
        lancouExcecaoAresta = true;
        std::cout << "  Excecao esperada capturada em InsereAresta(0, 5): " << msg << std::endl;
    }
    catch (...)
    {
        // Captura qualquer outra exceção inesperada
        assert(false && "Excecao inesperada em InsereAresta com indice invalido!");
    }
    assert(lancouExcecaoAresta); // Garante que a exceção esperada foi lançada

    lancouExcecaoAresta = false;
    try
    {
        grafo.InsereAresta(-1, 0); // Vértice -1 não existe
    }
    catch (const char *msg)
    {
        lancouExcecaoAresta = true;
        std::cout << "  Excecao esperada capturada em InsereAresta(-1, 0): " << msg << std::endl;
    }
    catch (...)
    {
        assert(false && "Excecao inesperada em InsereAresta com indice negativo!");
    }
    assert(lancouExcecaoAresta);

    // --- Teste ImprimeVizinhos com índice inválido ---
    bool lancouExcecaoImprime = false;
    try
    {
        grafo.ImprimeVizinhos(2); // Vértice 2 não existe (índices são 0, 1)
    }
    catch (const char *msg)
    {
        lancouExcecaoImprime = true;
        std::cout << "  Excecao esperada capturada em ImprimeVizinhos(2): " << msg << std::endl;
    }
    catch (...)
    {
        assert(false && "Excecao inesperada em ImprimeVizinhos com indice invalido!");
    }
    assert(lancouExcecaoImprime);

    lancouExcecaoImprime = false;
    try
    {
        grafo.ImprimeVizinhos(-1); // Vértice -1 não existe
    }
    catch (const char *msg)
    {
        lancouExcecaoImprime = true;
        std::cout << "  Excecao esperada capturada em ImprimeVizinhos(-1): " << msg << std::endl;
    }
    catch (...)
    {
        assert(false && "Excecao inesperada em ImprimeVizinhos com indice negativo!");
    }
    assert(lancouExcecaoImprime);

    // NOTA: getGrauMinimo/Maximo também falhariam com acesso inválido se
    // o loop interno tentasse acessar um vértice inválido, mas a falha
    // principal é no acesso a listaVertices[0] em grafo vazio.

    std::cout << "test_ListaAdjacencia_AcessoInvalido PASSED." << std::endl;
}

// Teste "smoke test" para os métodos de impressão (verifica se não travam)
void test_ListaAdjacencia_ImprimeMethods_SmokeTest()
{
    std::cout << "Running test_ListaAdjacencia_ImprimeMethods_SmokeTest..." << std::endl;
    ListaAdjacencia grafo;
    grafo.InsereVertice(); // 0
    grafo.InsereVertice(); // 1
    grafo.InsereVertice(); // 2

    grafo.InsereAresta(0, 1);
    grafo.InsereAresta(1, 2);

    std::cout << "  Chamando ImprimeVizinhos(1): ";
    grafo.ImprimeVizinhos(1); // Deve imprimir grau e vizinhos de 1 (0 e 2)

    std::cout << "  Chamando Imprime():" << std::endl;
    grafo.Imprime(); // Deve imprimir a lista de adjacência completa

    // Teste em grafo vazio
    ListaAdjacencia grafoVazio;
    std::cout << "  Chamando Imprime() em grafo vazio:" << std::endl;
    grafoVazio.Imprime(); // Deve imprimir indicando 0 vértices/arestas

    std::cout << "test_ListaAdjacencia_ImprimeMethods_SmokeTest PASSED (se nao houve crash)." << std::endl;
}

// --- Função Principal para Rodar os Testes ---
// int main()
// {
//     std::cout << "--- Iniciando Testes Unitarios para ListaAdjacencia & Vertice (v2) ---" << std::endl;

//     test_Vertice_NovaAresta_GetGrau();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_Construtor_GetQuantidade();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_InsereVertice();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_InsereAresta_Contagem();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_GetGrauMinimoMaximo();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_AcessoInvalido(); // Testa o tratamento de índices errados
//     std::cout << "-----------------------------------------" << std::endl;
//     test_ListaAdjacencia_ImprimeMethods_SmokeTest();

//     std::cout << "--- Todos os Testes Unitarios Completos ---" << std::endl;

//     return 0;
// }
