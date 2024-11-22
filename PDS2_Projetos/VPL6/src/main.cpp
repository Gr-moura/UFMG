#include "aluno.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

bool comparator(const Aluno *a, const Aluno *b)
{
    return a->getNome() < b->getNome();
}

int main()
{
    cout << fixed;
    cout.precision(2);

    vector<Aluno *> alunos;
    string nome;
    int matricula;
    int nota;

    while (true)
    {
        cin >> nome;

        if (nome == "END")
            break;

        alunos.push_back(new Aluno);
        alunos.back()->setNome(nome);

        cin >> matricula;
        alunos.back()->setMatricula(matricula);

        while (true)
        {
            cin >> nota;

            if (nota == -1)
                break;

            alunos.back()->setNovaNota(nota);
        }
    }

    sort(alunos.begin(), alunos.end(), comparator);

    for (Aluno *aluno : alunos)
    {
        cout << aluno->getMatricula() << " ";
        cout << aluno->getNome() << " ";

        for (int aval : aluno->getNotas())
            cout << aval << " ";

        cout << endl << aluno->fazerMedia() << " ";
        pair<int, int> maxMin = aluno->MaxMin();
        cout << maxMin.first << " " << maxMin.second << endl;

        delete aluno;
    }

    return 0;
}
