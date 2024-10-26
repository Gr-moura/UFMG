#ifndef ONIBUS_H
#define ONIBUS_H

#include <string>
using namespace std;

struct Onibus
{
    string placa;
    int maxCapacidade;
    int atualLotacao;

    Onibus(const string &placa, const int maxCapacidade);

    void subir_passageiros(const int qtSubiram);
    void descer_passageiros(const int qtDesceram);
    void transfere_passageiros(Onibus *outroOnibus, const int qtPessoasTrocadas);
    void imprimir_estado();
};

#endif
