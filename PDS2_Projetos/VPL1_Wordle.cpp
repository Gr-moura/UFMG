#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    ifstream palavras("palavras.txt", fstream::in);
    if (!palavras.is_open())
    {
        cout << "Error: Palavras.txt";
        return 1;
    }

    int n;
    palavras >> n;

    string *dados = new string[n];
    cout << n;

    string a;
    palavras >> a;
    cout << a;

    delete[] dados;
}
