#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

class TipoCelula
{
  public:
    TipoCelula();
    TipoCelula(int item);
    TipoCelula(int item, TipoCelula *proximo);

    int GetItem();
    TipoCelula *GetProximo();

    void SetItem(int item);
    void SetProximo(TipoCelula *proximo);

  private:
    int item;
    TipoCelula *proximo;

    friend class ListaEncadeada;
};

class ListaEncadeada
{
  public:
    ListaEncadeada();
    ~ListaEncadeada();

    int GetItem(int pos);
    void SetItem(int item, int pos);
    void InsereInicio(int item);
    void InsereFinal(int item);
    void InserePosicao(int item, int pos);
    int RemoveInicio();
    int RemoveFinal();
    int RemovePosicao(int pos);
    int Pesquisa(int c);
    void Imprime();
    void Limpa();

  private:
    int tamanho;
    TipoCelula *primeiro;
    TipoCelula *ultimo;
    TipoCelula *Posiciona(int pos);
};

class ListaAdjacencia
{
  public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    void InsereVertice();
    void InsereAresta(int v, int w);
    int QuantidadeVertices();
    int QuantidadeArestas();
    int GrauMinimo();
    int GrauMaximo();
    void ImprimeVizinhos(int v);

  private:
    ListaEncadeada *vertices;
    int quantidadeVertices;
};

#endif