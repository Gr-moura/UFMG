#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
class TruthTable
{
  private:
    vector<vector<bool>> possibleValues;
    int numPropositions;

    void fillPossibleValues();

    // bool IMP(bool a, bool b);
    // bool AND(bool a, bool b);
    // bool OR(bool a, bool b);
    // bool NOT(bool a);

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();

    bool compareFunctions();

    const pair<int, int> evaluateFunctions(vector<bool> &values);
};

#endif
