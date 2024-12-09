#ifndef ALUNO_H
#define ALUNO_H

#include <string>
#include <vector>

using namespace std;

class Aluno
{
  private:
    string nome;
    int matricula;
    vector<int> notas;

  public:
    Aluno();

    void setNome(const string &nome)
    {
        this->nome = nome;
    };

    void setMatricula(int matricula)
    {
        this->matricula = matricula;
    };

    void setNovaNota(int NovaNota)
    {
        this->notas.push_back(NovaNota);
    };

    const string &getNome() const
    {
        return this->nome;
    }

    int getMatricula() const
    {
        return this->matricula;
    }

    const vector<int> &getNotas() const
    {
        return this->notas;
    }

    double fazerMedia();
    pair<int, int> MaxMin();
};

#endif
