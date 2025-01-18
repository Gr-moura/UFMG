#include <iostream>
#include <memory>
using namespace std;

class Teste
{
  public:
    int atributo;

    // Construtores e Destrutor
    Teste() : Teste(0) {}
    Teste(int val) : atributo(val) { cout << "Construtor " << atributo << endl; }
    ~Teste() { cout << "Destrutor " << atributo << endl; }
};

int main()
{
    int n;
    cin >> n;

    if (n % 2 == 0)
    {
        for (int c = 1; c <= n; c++)
        {
            Teste *tradicional = new Teste(c);
            unique_ptr<Teste> smart(new Teste(c));
        }

        return 0;
    }

    shared_ptr<Teste> shared(new Teste(0));
    for (int c = 1; c <= n; c++)
    {
        shared_ptr<Teste> shared2(shared);
        shared2->atributo = c;
    }

    // Returns the number of different shared_ptr instances (*this included)
    // managing the current object. If there is no managed object, ​0​ is returned.
    cout << shared.use_count() << endl;

    return 0;
}