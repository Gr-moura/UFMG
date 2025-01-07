#include <iostream>
using namespace std;
class Base1
{
  public:
    Base1() { cout << "Base1()" << " "; }
    virtual void Imprimir() = 0;
};
class Base2
{
  public:
    Base2() { cout << "Base2()" << " "; }
};
class Derived : public Base1, public Base2
{
  public:
    Derived() { cout << "Derived()" << " "; }
    void Imprimir() { cout << 3; }
};
int main()
{
    Derived d;
    return 0;
}