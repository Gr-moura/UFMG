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

    bool evaluateFunction(const string &f);

    // bool IMP(bool a, bool b);
    // bool AND(bool a, bool b);
    // bool OR(bool a, bool b);
    // bool NOT(bool a);

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();

    bool compareFunctions(const string &f1, const string &f2);

    bool evaluateFunction(const string &original, vector<bool> values);
};

#endif
