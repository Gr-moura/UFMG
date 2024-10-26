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

    void subir_passageiros(int qtSubiram);
    void descer_passageiros(int qtDesceram);
    void transfere_passageiros(Onibus *outroOnibus, int qtPessoasTrocadas);
    void imprimir_estado();
};

#endif
