#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    x--;

    vector<vector<double>> mat(n, vector<double>(n, 0));
    vector<double> b(n);

    for (int i = 0; i < n; i++)
    {
        if (i - x >= 0)
            cin >> mat[i][i - x];

        cin >> mat[i][i];

        if (i + x < n)
            cin >> mat[i][i + x];
    }

    for (int i = 0; i < n; i++)
        cin >> b[i];

    for (int i = 0; i < n; i++)
    {
        if (mat[i][i] == 0)
            continue;

        if (i + x < n)
        {
            mat[i + x][i + x] -= mat[i][i + x] * mat[i + x][i] / mat[i][i];
            b[i + x] -= b[i] * mat[i + x][i] / mat[i][i];
            mat[i + x][i] = 0;
        }

        if (i + 2 * (x - 1) < n)
            mat[i + x][i + 2 * (x - 1)] -= mat[i][i + 2 * (x - 1)] * mat[i + x][i] / mat[i][i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << " " << mat[i][j];
        }

        cout << " " << b[i] << endl;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (mat[i][i] == 0)
            continue;

        if (i - x >= 0)
        {
            mat[i - x][i - x] -= mat[i][i - x] * mat[i - x][i] / mat[i][i];
            b[i - x] -= b[i] * mat[i - x][i] / mat[i][i];
            mat[i - x][i] = 0;
        }
    }
    cout << "----------------------\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << " " << mat[i][j];
        }

        cout << " " << b[i] << endl;
    }

    cout << "----------------------\n";

    for (int i = 0; i < n; i++)
    {

        cout << " " << b[i] / mat[i][i] << endl;
    }

    return 0;
}
