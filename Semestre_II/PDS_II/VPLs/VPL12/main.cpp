#include <exception>
#include <iostream>
#include <vector>

class NegativeResultException : public std::exception
{
  private:
    int _valor;

  public:
    NegativeResultException(int valor) : _valor(valor) {}
    virtual const char *what() const throw() override { return "Erro: Resultado Negativo."; }
    int getValor() const noexcept { return _valor; }
};

int main()
{
    std::vector<int> vetor = {-20, -10, 0, 10, 20};
    try
    {
        int in;
        std::cin >> in;

        if (in < 0 || in >= (int)vetor.size())
            throw std::out_of_range("Erro: Parametro invalido");

        int a = vetor.at(in);

        if (a < 0)
            throw NegativeResultException(a);

        else if (a == 0)
            throw std::logic_error("Erro: O resultado nao deve ser zero");

        std::cout << a;
    }
    catch (const NegativeResultException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << e.getValor() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}