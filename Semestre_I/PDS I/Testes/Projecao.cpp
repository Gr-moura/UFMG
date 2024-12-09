#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << setprecision(2);

    int sz;
    cin >> sz;

    vector<double> V(sz);
    vector<double> W(sz);

    for (int i = 0; i < sz; i++)
        cin >> V[i];

    for (int i = 0; i < sz; i++)
        cin >> W[i];

    double Ponto = 0;

    for (int i = 0; i < sz; i++)
        Ponto += V[i] * W[i];

    double Norma = 0;

    for (int i = 0; i < sz; i++)
        Norma += W[i] * W[i];

    for (int i = 0; i < sz; i++)
        cout << W[i] * (Ponto / Norma) << endl;
}
