#include "Empresa.hpp"

Empresa::Empresa()
{
    this->numOnibus = 0;
    for (int i = 0; i < 20; i++)
    {
        this->frota[i] = nullptr;
    }
}

Onibus *Empresa::adicionar_onibus(const string &placaNovoOnibus, const int maxCapacidadeNovoOnibus)
{
    if (this->numOnibus == 20)
    {
        return nullptr;
    }

    for (int onibusAtual = 0; onibusAtual < this->numOnibus; onibusAtual++)
    {
        if (this->frota[onibusAtual]->placa == placaNovoOnibus)
        {
            return nullptr;
        }
    }

    this->frota[this->numOnibus++] = new Onibus(placaNovoOnibus, maxCapacidadeNovoOnibus);
    return this->frota[this->numOnibus - 1];
}

Onibus *Empresa::busca_onibus(const string &placaProcurada)
{
    for (int onibusAtual = 0; onibusAtual < this->numOnibus; onibusAtual++)
    {
        if (this->frota[onibusAtual]->placa == placaProcurada)
        {
            return this->frota[onibusAtual];
        }
    }

    return nullptr;
}

void Empresa::imprimir_estado()
{
    for (int onibusAtual = 0; onibusAtual < this->numOnibus; onibusAtual++)
    {
        this->frota[onibusAtual]->imprimir_estado();
    }
}
