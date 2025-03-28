#include "HeapInt.hpp"
#include <iostream>
#include <ostream>

using namespace std;

int main()
{

    int x;
    cin >> x;
    if (x == 1)
    {
        HeapInt a(20);
        HeapInt b = a;
        HeapInt c;
        HeapInt d = 1;

        cout << a << " " << b << " " << c << " " << d << endl;

        b = 10;
        cin >> c;
        d = b + c;

        cout << a << " " << b << " " << c << " " << d << endl;

        cin >> b;
        cin >> c;
        cin >> d;
        a = b + c - d;

        cout << a << " " << b << " " << c << " " << d << endl;

        cin >> a;
        cin >> b;
        if (a == b)
        {
            HeapInt *p = new HeapInt(20);
            c = 10;
            d = *p - c;
            cout << a << " " << b << " " << c << " " << d << endl;
            a = *p;
            delete (p);
        }
        else
        {
            c = a;
            d = b;
        }
        cout << a << " " << b << " " << c << " " << d << endl;
    }
    else
    {
        HeapInt a(10);
        HeapInt b;

        cin >> b;

        if (a == b)
            cout << "Bingo!" << endl;

        HeapInt c = a;
        HeapInt d;
        HeapInt e;

        d = 5;
        e = a + b + c + d;
        cout << a << " " << b << " " << c << " " << d << " " << e << endl;
    }

    return 0;
}