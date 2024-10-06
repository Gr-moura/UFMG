#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

string *Encontrar_Objetivo(ifstream &arquivo)
{
    int qt_palavras;
    arquivo >> qt_palavras;

    int num_buscada;
    cin >> num_buscada;

    string *obj = new string;
    for (int i = 0; i < num_buscada; i++)
        arquivo >> *obj;

    cout << *obj;
    return obj;
}

int main()
{
    ifstream arquivo("palavras.txt", fstream::in);
    if (!arquivo.is_open())
    {
        cerr << "Error: Palavras.txt" << endl;
        return 1;
    }

    string *obj = Encontrar_Objetivo(arquivo);

    delete obj;
    arquivo.close();
    return 0;
}
