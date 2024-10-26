#include "Onibus.hpp"

#include <iostream>
using namespace std;

Onibus::Onibus(const string &placa, int maxCapacidade)
{
    this->placa = placa;
    this->maxCapacidade = maxCapacidade;
    this->atualLotacao = 0;
}

void Onibus::subir_passageiros(int qtSubiram)
{
    this->atualLotacao += qtSubiram;
}

void Onibus::descer_passageiros(int qtDesceram)
{
    this->atualLotacao -= qtDesceram;
}

void Onibus::transfere_passageiros(Onibus *outroOnibus, int qtPessoasTrocadas)
{
    this->atualLotacao -= qtPessoasTrocadas;
    outroOnibus->atualLotacao += qtPessoasTrocadas;
}

void Onibus::imprimir_estado()
{
    cout << this->placa << " ";
    cout << "(" << this->atualLotacao << "/" << this->maxCapacidade << ")" << endl;
}
