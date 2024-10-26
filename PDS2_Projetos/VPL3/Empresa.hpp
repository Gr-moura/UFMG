#ifndef EMPRESA_H
#define EMPRESA_H

#include "Onibus.hpp"

struct Empresa
{
    int numOnibus;    
    Onibus* frota[20];

    Empresa();

    Onibus* adicionar_onibus(const string& placaNovoOnibus, const int maxCapacidadeNovoOnibus);
    Onibus* busca_onibus(const string& placa);
    void imprimir_estado();
};

#endif
