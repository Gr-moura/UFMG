#include <fstream>
#include <iostream>
using namespace std;

string Encontrar_Objetivo(ifstream &arquivo)
{
    int qt_palavras;
    arquivo >> qt_palavras;

    int num_buscada;
    cin >> num_buscada;

    string chave;
    for (int i = 0; i < num_buscada; i++)
        arquivo >> chave;

    return chave;
}

bool Jogar(const string &chave)
{
    string letras;
    for (int i = 0; i < 5; i++)
    {
        string chute;
        cin >> chute;

        if (chute == chave)
        {
            cout << chute;
            cout << " (" << letras << ")" << endl;
            return 1;
        }

        for (int j = 0; j < 5; j++)
        {
            if (chave[j] == chute[j])
            {
                cout << chave[j];
                continue;
            }

            if (chave.find(chute[j]) != string::npos)
            {
                cout << (char)tolower(chute[j]);
                continue;
            }

            if (letras.find(chute[j]) == string::npos)
                letras = letras + chute[j];

            cout << "*";
        }

        cout << " (" << letras << ")" << endl;
    }

    return 0;
}

int main()
{
    ifstream arquivo("palavras.txt", fstream::in);
    if (!arquivo.is_open())
    {
        cerr << "Error: Palavras.txt" << endl;
        return 1;
    }

    string chave = Encontrar_Objetivo(arquivo);

    bool venceu = Jogar(chave);

    if (venceu)
        cout << "GANHOU!" << endl;

    else
        cout << "PERDEU! " << chave << endl;

    arquivo.close();
    return 0;
}
