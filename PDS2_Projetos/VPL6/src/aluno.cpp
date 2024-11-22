#include "aluno.hpp"

#include <algorithm>
#include <utility>

Aluno::Aluno()
{
    this->nome = "Placeholder";
    this->matricula = -1;
}

double Aluno::fazerMedia()
{
    double somaNotas = 0;

    for (double nota : this->notas)
        somaNotas += nota;

    return somaNotas / this->notas.size();
}

pair<int, int> Aluno::MaxMin()
{
    return {*max_element(this->notas.begin(), this->notas.end()), *min_element(this->notas.begin(), this->notas.end())};
}
