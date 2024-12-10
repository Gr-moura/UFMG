#include <iostream>
#include <list>
using namespace std;

class Classe
{
  private:
    int id;
    static int numElementos;
    static int idCounter;

  public:
    Classe() : Classe(++Classe::idCounter) {}
    Classe(int id) : id(id) { ++Classe::numElementos; }

    ~Classe() { --Classe::numElementos; }

    static int getNumElementos() { return Classe::numElementos; }
    int getId() const { return this->id; }
    Classe *getAdress() { return this; }
};

int Classe::numElementos = 0;
int Classe::idCounter = 0;

void addToBack(list<Classe *> &lista);
void addToFront(list<Classe *> &lista);
void removeFirst(list<Classe *> &lista);
void printIesimo(list<Classe *> &lista);
void printAll(list<Classe *> &lista);

int main()
{
    list<Classe *> lista;
    char command;

    cin >> command;
    while (command != 'E')
    {
        switch (command)
        {
        case 'A':
            addToBack(lista);
            break;

        case 'C':
            addToFront(lista);
            break;

        case 'R':
            removeFirst(lista);
            break;

        case 'N':
            cout << Classe::getNumElementos();
            break;

        case 'P':
            printIesimo(lista);
            break;

        case 'L':
            printAll(lista);
            break;
        }

        cout << endl;
        cin >> command;
    }

    for (Classe *c : lista)
        delete c;
}

void addToFront(list<Classe *> &lista)
{
    int id;
    cin >> id;

    if (id >= 0)
    {
        cout << "ERRO";
        return;
    }

    lista.push_front(new Classe(id));
    cout << lista.front()->getId() << " " << lista.front()->getAdress();
}

void addToBack(list<Classe *> &lista)
{
    lista.push_back(new Classe());
    cout << lista.back()->getId() << " " << lista.back()->getAdress();
}

void removeFirst(list<Classe *> &lista)
{
    if (lista.empty())
    {
        cout << "ERRO";
        return;
    }

    cout << lista.front()->getId() << " " << lista.front()->getAdress();

    delete lista.front();
    lista.pop_front();
}

void printIesimo(list<Classe *> &lista)
{
    int index;
    cin >> index;

    if (index < 1 or index > Classe::getNumElementos())
    {
        cout << "ERRO";
        return;
    }

    list<Classe *>::iterator it = lista.begin();
    advance(it, index - 1);

    cout << (*it)->getId() << " " << *it;
}

void printAll(list<Classe *> &lista)
{
    for (Classe *c : lista)
    {
        cout << c->getId() << " " << c;

        if (c != lista.back())
            cout << endl;
    }
}