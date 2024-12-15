#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Ponto
{
  private:
    int x;
    int y;

  public:
    Ponto() : Ponto(0, 0) {}
    Ponto(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

class FiguraGeometrica
{
  private:
    const Ponto centro;

  public:
    FiguraGeometrica(int x, int y) : centro(x, y) {}
    virtual ~FiguraGeometrica() {}

    virtual double calculaArea() const = 0;
    virtual void desenha() const
    {
        cout << centro.getX() << " ";
        cout << centro.getY() << " ";
    }
};

class Retangulo : public FiguraGeometrica
{
  private:
    int L1;
    int L2;

  public:
    Retangulo(int x, int y, int L1, int L2) : FiguraGeometrica(x, y), L1(L1), L2(L2) {}

    int getL1() const { return L1; }
    int getL2() const { return L2; }

    void setL1(int L1) { this->L1 = L1; }
    void setL2(int L2) { this->L2 = L2; }

    double calculaArea() const override { return (double)L1 * (double)L2; }
    void desenha() const override
    {
        FiguraGeometrica::desenha();
        cout << "RETANGULO" << endl;
    }

    ~Retangulo() {}
};

class Triangulo : public FiguraGeometrica
{
  private:
    int base;
    int altura;

  public:
    Triangulo(int x, int y, int b, int a) : FiguraGeometrica(x, y), base(b), altura(a) {}

    double calculaArea() const override { return (double)base * (double)altura / 2.0; }
    void desenha() const override
    {
        FiguraGeometrica::desenha();
        cout << "TRIANGULO" << endl;
    }

    ~Triangulo() {}
};

class Circulo : public FiguraGeometrica
{
  private:
    int raio;

  public:
    Circulo(int x, int y, int r) : FiguraGeometrica(x, y), raio(r) {}

    double calculaArea() const override { return M_PI * (double)raio * (double)raio; }
    void desenha() const override
    {
        FiguraGeometrica::desenha();
        cout << "CIRCULO" << endl;
    }

    ~Circulo() {}
};

Retangulo *createRectangle();
Circulo *createCircle();
Triangulo *createTriangle();

void calculateAreas(const vector<FiguraGeometrica *> &figuras);
void desenhaTodas(const vector<FiguraGeometrica *> &figuras);

int main()
{
    cout << fixed;
    cout.precision(2);
    cout.fill('0');

    vector<FiguraGeometrica *> figuras;

    char command;
    cin >> command;

    while (command != 'E')
    {
        switch (command)
        {
        case 'R':
            figuras.push_back(createRectangle());
            break;

        case 'C':
            figuras.push_back(createCircle());
            break;

        case 'T':
            figuras.push_back(createTriangle());
            break;

        case 'A':
            calculateAreas(figuras);
            break;

        case 'D':
            desenhaTodas(figuras);
            break;
        }

        cin >> command;
    }

    for (FiguraGeometrica *c : figuras)
        delete c;

    return 0;
}

Retangulo *createRectangle()
{
    int x, y, L1, L2;
    cin >> x >> y >> L1 >> L2;

    return new Retangulo(x, y, L1, L2);
}

Circulo *createCircle()
{
    int x, y, r;
    cin >> x >> y >> r;

    return new Circulo(x, y, r);
}

Triangulo *createTriangle()
{
    int x, y, b, a;
    cin >> x >> y >> b >> a;

    return new Triangulo(x, y, b, a);
}

void calculateAreas(const vector<FiguraGeometrica *> &figuras)
{
    double soma = 0;
    for (FiguraGeometrica *f : figuras)
    {
        soma += f->calculaArea();
    }

    cout << soma << endl;
}

void desenhaTodas(const vector<FiguraGeometrica *> &figuras)
{
    for (FiguraGeometrica *f : figuras)
    {
        f->desenha();
    }
}