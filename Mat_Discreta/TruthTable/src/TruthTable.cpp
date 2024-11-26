#include "TruthTable.hpp"

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
    return ((!a) || b);
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

const pair<int, int> TruthTable::evaluateFunctions(vector<bool> &values)
{
    int A = values[0], B = values[1], C = values[2], D = values[3], E = values[4], F = values[5], G = values[6],
        H = values[7], I = values[8], J = values[9], K = values[10], L = values[11], M = values[12], N = values[13],
        O = values[14], P = values[15], Q = values[16], R = values[17], S = values[18], T = values[19], U = values[20],
        V = values[21], W = values[22], X = values[23], Y = values[24], Z = values[25];

    bool f1 = IMP(AND(A, NOT(B)), OR(NOT(C), C));
    bool f2 = IMP(AND(A, NOT(B)), OR(NOT(C), C));

    return {f1, f2};
}

bool TruthTable::compareFunctions()
{
    bool different = false;

    vector<bool> resultsF1(pow(2, numPropositions));
    vector<bool> resultsF2(pow(2, numPropositions));

    for (int i = 0; i < pow(2, numPropositions); i++)
    {
        pair<int, int> results = evaluateFunctions(possibleValues[i]);

        resultsF1[i] = results.first;
        resultsF2[i] = results.second;

        cout << results.first << " " << results.second << endl;

        if (results.first != results.second)
        {
            cout << "Functions are not equivalent" << endl;

            for (bool value : possibleValues[i])
            {
                cout << value << " ";
            }

            cout << endl << resultsF1[i] << " " << resultsF2[i] << "\n\n";
            different = true;
        }
    }

    if (!different)
    {
        cout << "Functions are equivalent" << endl;
    }
}
