#include "TruthTable.hpp"
#include <iostream>

using namespace std;

int main()
{
    TruthTable TT(3);
    TT.printPossibleValues();
    cout << IMP(AND(A, NOT(B)), OR(NOT(C), C)) << endl;
    return 0;
}