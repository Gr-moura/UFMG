#include <iostream>
#include <list>
using namespace std;

class Classe
{
  private:
    static int numElementos;
    int id;

  public:
    Classe() : id(++numElementos) {}
    Classe(int id) : id(id) {}

    ~Classe()
    {
        --Classe::numElementos;
        delete this;
    }

    static int getNumElementos() { return Classe::numElementos; }
    int getId() const { return this->id; }
};

int Classe::numElementos = 0;

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
    cout << lista.front()->getId() << " " << lista.front();
}

void addToBack(list<Classe *> &lista)
{
    lista.push_back(new Classe());
    cout << lista.back()->getId() << " " << lista.back();
}

void removeFirst(list<Classe *> &lista)
{
    if (lista.empty())
    {
        cout << "ERRO";
        return;
    }

    cout << lista.front()->getId() << " " << lista.front();
    lista.pop_front();
}

void printIesimo(list<Classe *> &lista)
{
    int index;
    cin >> index;

    if (index < 1 or index >= Classe::getNumElementos())
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