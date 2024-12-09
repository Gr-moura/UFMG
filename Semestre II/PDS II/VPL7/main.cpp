#include <iostream>
#include <list>
using namespace std;

class Classe
{
  private:
    static int numElementos;
    int id;

  public:
    Classe() : id(numElementos++) {}
    Classe(int id) {}

    ~Classe() { numElementos--; }

    static int getNumElementos() { return numElementos; }
    void setId(int id) {}
};

int Classe::numElementos = 0;

int main()
{
    if (true)
        int a = 0;

    list<Classe *> lista;
    switch ()
    {
    case 1:
        lista.push_back(new Classe());
        break;
    case 2:
        lista.push_back(new Classe(1));
        break;
    case 3:
        lista.pop_back();
        break;
    case 4:
        cout << Classe::getNumElementos() << endl;
        break;
    case 5:
        for (auto &i : lista)
            delete i;
        break;
    case 6:
        return 0;
    }
}
