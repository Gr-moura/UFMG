#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    string nome_arquivo;
    cin >> nome_arquivo;
    cout << nome_arquivo;

    ifstream arquivo(nome_arquivo, fstream::in);
    if (!arquivo.is_open())
    {
        cerr << "Error: File not found" << endl;
        return 1;
    }

    map <string, int> palavras;
    string a;
    while(arquivo >> a)
    cout << a;


    arquivo.close();
    return 0;
}