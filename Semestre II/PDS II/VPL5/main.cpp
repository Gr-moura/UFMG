#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

bool is_alphanum(char c)
{
    if (c >= 'A' && c <= 'Z')
        return true;
    
    if (c >= 'a' && c <= 'z')
        return true;
    
    if (c >= '0' && c <= '9')
        return true;
    
    return false;
}

int main()
{
    string nome_arquivo;
    cin >> nome_arquivo;

    ifstream arquivo(nome_arquivo, fstream::in);
    if (!arquivo.is_open())
    {
        cerr << "Error: File not found" << endl;
        return 1;
    }

    map <string, int> palavras;

    char aux;
    string nome;

    while(arquivo.get(aux))
    {
        if (is_alphanum(aux))
        {
            nome += tolower(aux);
            continue;   
        }

        if (!nome.empty())
            palavras[nome]++;
        
        nome = "";
    }

    for (auto p: palavras)
        cout << p.first << " " << p.second << endl;

    arquivo.close();
    return 0;
}