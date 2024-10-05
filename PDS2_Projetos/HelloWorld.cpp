#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    string a = "chasg ghashdkja hhchahca\n fghjjs";

    stringstream b(a);

    getline(b, a, 'f');
    cout << a;
    return 0;
} 

