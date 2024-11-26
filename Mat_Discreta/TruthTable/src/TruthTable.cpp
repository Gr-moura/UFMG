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
