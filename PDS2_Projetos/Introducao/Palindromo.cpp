#include <iostream>
#include <string>
using namespace std;

bool Media(const string &entrada)
{
    for (int i = 0; i < (int)entrada.length() / 2; i++)
    {
        if (entrada[i] != entrada[entrada.length() - 1 - i])
            return 0;
    }

    return 1;
}

int main()
{
    string entrada;
    getline(cin, entrada);

    if (Media(entrada))
    {
        cout << "SIM";
        return 0;
    }

    cout << "NAO";
    return 0;
}
