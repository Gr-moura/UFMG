#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double Media(const double *vetor, int n)
{
    double soma = 0;
    for (int i = 0; i < n; i++)
        soma += vetor[i];

    return soma / n;
}

double DP(const double *vetor, double media, int n)
{
    double soma = 0;
    for (int i = 0; i < n; i++)
        soma += (vetor[i] - media) * (vetor[i] - media);

    soma /= n;

    return sqrt(soma);
}

int main()
{
    cout << fixed << setprecision(4);

    int n;
    cin >> n;

    double *vetor = new double[n];

    for (int i = 0; i < n; i++)
        cin >> vetor[i];

    double media = Media(vetor, n);

    cout << media << endl;
    cout << DP(vetor, media, n) << endl;

    delete[] vetor;
    return 0;
}
