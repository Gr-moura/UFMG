#include "TruthTable.hpp"
#include <iostream>

using namespace std;

const string &getFunctions()
{
    string f1;
    f1 = "IMP(AND(A, NOT(B)), OR(NOT(C), C))";
}

int main()
{
    TruthTable t(3);
    t.printPossibleValues();

    t.compareFunctions("a", "v");
    return 0;
}