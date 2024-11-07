#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 1, x;
    cin >> n >> x;

    // Em cada diagonal nao principal, existem n - x + 1 elementos

    vector<vector<int>> mat(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        if (i - x + 1 >= 0)
            cin >> mat[i][i - x + 1];

        cin >> mat[i][i];

        if (i + x - 1 < n)
            cin >> mat[i][i + x - 1];
    }

    for (int i = 0; i < n; i++)
    {
        if (mat[i][i] == 0)
            continue;

        if (i + x - 1 < n)
        {
            mat[i + x - 1][i] = 0;
            mat[i + x - 1][i + x - 1] -= mat[i + x - 1][i] / mat[i][i];
        }

        if (i + 2 * (x - 1) < n)
            mat[i + x - 1][i + 2 * (x - 1)] -= mat[i + x - 1][i] / mat[i][i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j];
        }

        cout << endl;
    }

    return 0;
}
