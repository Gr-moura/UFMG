#include <iostream>
using namespace std;
int *B;

void passar(const int &A)
{
    cout << A;
}

int main()
{
    int A = 5;
    passar(A);
    cout << A;

    return 0;
}