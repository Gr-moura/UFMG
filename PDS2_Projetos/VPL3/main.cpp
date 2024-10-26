#include "Empresa.hpp"
#include "Onibus.hpp"
#include <iostream>
using namespace std;

void verificarEspacoParaTroca(const Onibus &onibus1, const Onibus &onibus2, const int qtPessoasTrocadas)
{
    if (onibus1.atualLotacao - qtPessoasTrocadas < 0)
    {
        cout << "ERRO : transferencia cancelada" << endl;
        return;
    }

    if (onibus2.atualLotacao + qtPessoasTrocadas > onibus2.maxCapacidade)
    {
        cout << "ERRO : transferencia cancelada" << endl;
        return;
    }
}

void verificarExistencia(const Onibus *onibus)
{
    if (onibus == nullptr)
    {
        cout << "ERRO : onibus inexistente" << endl;
        return;
    }
}

void cadastrarOnibus(Empresa &Empresa)
{
    string placa;
    int maxCapacidade;
    cin >> placa >> maxCapacidade;

    if (Empresa.adicionar_onibus(placa, maxCapacidade) == nullptr)
    {
        cout << "ERRO : onibus repetido" << endl;
        return;
    }

    cout << "novo onibus cadastrado" << endl;
}

void subiramNoOnibus(Empresa &Empresa)
{
    string placa;
    int qtSubiram;
    cin >> placa >> qtSubiram;

    Onibus *onibus = Empresa.busca_onibus(placa);
    verificarExistencia(onibus);

    if (onibus->atualLotacao + qtSubiram > onibus->maxCapacidade)
    {
        onibus->atualLotacao = onibus->maxCapacidade;
        cout << "ERRO : onibus lotado" << endl;
        return;
    }

    onibus->subir_passageiros(qtSubiram);
    cout << "passageiros subiram com sucesso" << endl;
}

void desceramDoOnibus(Empresa &Empresa)
{
    string placa;
    int qtDesceram;
    cin >> placa >> qtDesceram;

    Onibus *onibus = Empresa.busca_onibus(placa);
    verificarExistencia(onibus);

    if (onibus->atualLotacao - qtDesceram < 0)
    {
        onibus->atualLotacao = 0;
        cout << "ERRO : faltam passageiros" << endl;
        return;
    }

    onibus->descer_passageiros(qtDesceram);
    cout << "passageiros desceram com sucesso" << endl;
}

void transferenciaDePassageiros(Empresa &Empresa)
{
    string placa1, placa2;
    int qtPessoasTrocadas;
    cin >> placa1 >> placa2 >> qtPessoasTrocadas;

    Onibus *onibus1 = Empresa.busca_onibus(placa1);
    verificarExistencia(onibus1);

    Onibus *onibus2 = Empresa.busca_onibus(placa2);
    verificarExistencia(onibus2);

    verificarEspacoParaTroca(*onibus1, *onibus2, qtPessoasTrocadas);

    onibus1->transfere_passageiros(onibus2, qtPessoasTrocadas);
    cout << "transferencia de passageiros efetuada" << endl;
}

void ImprimirEstado(Empresa &Empresa)
{
    Empresa.imprimir_estado();
}

int main()
{
    Empresa Empresa;

    while (1)
    {
        char comando;
        cin >> comando;

        if (comando == 'F')
        {
            break;
        }

        switch (comando)
        {
        case 'C':
            cadastrarOnibus(Empresa);

            break;

        case 'S':
            subiramNoOnibus(Empresa);
            break;

        case 'D':
            desceramDoOnibus(Empresa);
            break;

        case 'T':
            transferenciaDePassageiros(Empresa);
            break;

        case 'I':
            ImprimirEstado(Empresa);
            break;
        }
    }

    return 0;
}
