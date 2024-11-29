#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

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
class TruthTable
{
  private:
    vector<vector<bool>> possibleValues;
    int numPropositions;

    void fillPossibleValues();

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();

    bool compareFunctions();

    const pair<bool, bool> evaluateFunctions(const vector<bool> &values);
};

#endif
