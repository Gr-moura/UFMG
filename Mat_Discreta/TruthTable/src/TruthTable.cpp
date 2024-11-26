#include "TruthTable.hpp"
#include <iostream>

void TruthTable::fillPossibleValues()
{
    int numValues = pow(2, numPropositions);
    possibleValues.resize(numValues);

    for (int i = 0; i < numValues; i++)
    {
        possibleValues[i].resize(numPropositions);

        for (int j = 0; j < numPropositions; j++)
        {
            possibleValues[i][numPropositions - j - 1] = (i >> j) & 1;
        }
    }
}

TruthTable::TruthTable(int numPropositions)
{
    this->numPropositions = numPropositions;
    fillPossibleValues();
}

void TruthTable::printPossibleValues()
{
    for (vector<bool> values : possibleValues)
    {
        for (bool value : values)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

bool IMP(bool a, bool b)
{
    return (!(a) || (b));
}

bool AND(bool a, bool b)
{
    return ((a) && (b));
}

bool OR(bool a, bool b)
{
    return ((a) || (b));
}

bool NOT(bool a)
{
    return (!(a));
}

bool TruthTable::evaluateFunction(const string &original, vector<bool> values)
{
    string f = "IMP(AND(A, NOT(B)), OR(NOT(C), C))";

    for (int i = 0; i + 1 < f.size(); i++)
    {
        if ((f[i] <= 'Z' && f[i] >= 'A') && (f[i + 1] == ',' or f[i + 1] == ')'))
        {
            f[i] = values[f[i] - 'A'] == 1 ? '1' : '0';
        }
    }

    cout << eval(f);
}

bool TruthTable::compareFunctions(const string &f4, const string &f5)
{
    string f1 = "IMP(AND(A, NOT(B)), OR(NOT(C), C))";
    string f2 = "IMP(AND(C, NOT(C)), OR(NOT(C), C))";

    vector<bool> resultsF1(pow(2, numPropositions));
    vector<bool> resultsF2(pow(2, numPropositions));

    for (int i = 0; i < pow(2, numPropositions); i++)
    {
        resultsF1[i] = evaluateFunction(f1, possibleValues[i]);
    }
}