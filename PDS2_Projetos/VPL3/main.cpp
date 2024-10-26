#include "Empresa.hpp"
#include "Onibus.hpp"
#include <iostream>
using namespace std;

bool verificarEspacoParaTroca(const Onibus &onibus1, const Onibus &onibus2, const int qtPessoasTrocadas)
{
    if (onibus1.atualLotacao - qtPessoasTrocadas < 0)
    {
        cout << "ERRO : transferencia cancelada" << endl;
        return 1;
    }

    if (onibus2.atualLotacao + qtPessoasTrocadas > onibus2.maxCapacidade)
    {
        cout << "ERRO : transferencia cancelada" << endl;
        return 1;
    }

    return 0;
}

bool verificarExistencia(const Onibus *onibus)
{
    if (onibus == nullptr)
    {
        cout << "ERRO : onibus inexistente" << endl;
        return 1;
    }

    return 0;
}

void CadastrarOnibus(Empresa &Empresa)
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

void SubiramNoOnibus(Empresa &Empresa)
{
    string placa;
    int qtSubiram;
    cin >> placa >> qtSubiram;

    Onibus *onibus = Empresa.busca_onibus(placa);

    if (verificarExistencia(onibus))
        return;

    if (onibus->atualLotacao + qtSubiram > onibus->maxCapacidade)
    {
        cout << "ERRO : onibus lotado" << endl;
        return;
    }

    onibus->subir_passageiros(qtSubiram);
    cout << "passageiros subiram com sucesso" << endl;
}

void DesceramDoOnibus(Empresa &Empresa)
{
    string placa;
    int qtDesceram;
    cin >> placa >> qtDesceram;

    Onibus *onibus = Empresa.busca_onibus(placa);

    if (verificarExistencia(onibus))
        return;

    if (onibus->atualLotacao - qtDesceram < 0)
    {
        cout << "ERRO : faltam passageiros" << endl;
        return;
    }

    onibus->descer_passageiros(qtDesceram);
    cout << "passageiros desceram com sucesso" << endl;
}

void TransferenciaDePassageiros(Empresa &Empresa)
{
    string placa1, placa2;
    int qtPessoasTrocadas;
    cin >> placa1 >> placa2 >> qtPessoasTrocadas;

    Onibus *onibus1 = Empresa.busca_onibus(placa1);

    if (verificarExistencia(onibus1))
        return;

    Onibus *onibus2 = Empresa.busca_onibus(placa2);

    if (verificarExistencia(onibus2))
        return;

    if (verificarEspacoParaTroca(*onibus1, *onibus2, qtPessoasTrocadas))
        return;

    onibus1->transfere_passageiros(onibus2, qtPessoasTrocadas);
    cout << "transferencia de passageiros efetuada" << endl;
}

void Free(Empresa &Empresa)
{
    for (int i = 0; i < Empresa.numOnibus; i++)
    {
        delete Empresa.frota[i];
    }
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
            Free(Empresa);
            break;
        }

        switch (comando)
        {
        case 'C':
            CadastrarOnibus(Empresa);

            break;

        case 'S':
            SubiramNoOnibus(Empresa);
            break;

        case 'D':
            DesceramDoOnibus(Empresa);
            break;

        case 'T':
            TransferenciaDePassageiros(Empresa);
            break;

        case 'I':
            Empresa.imprimir_estado();
            break;
        }
    }

    return 0;
}
