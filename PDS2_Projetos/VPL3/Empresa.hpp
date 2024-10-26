#ifndef EMPRESA_H
#define EMPRESA_H

struct Empresa
{
    int numOnibus;
    vector<Onibus> onibus;

    Empresa(const string nome);

    void adicionar_onibus(const string placa, const int maxCapacidade);
    void remover_onibus(const string placa);
    void imprimir_frota();
};

#endif
