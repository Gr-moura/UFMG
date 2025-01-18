#include <iostream>
using namespace std;

void a(int b = 10, int c = 2)
{
    cout << b;
}

int main()
{
    a(1);
    a(15, 1);
    return 0;
}