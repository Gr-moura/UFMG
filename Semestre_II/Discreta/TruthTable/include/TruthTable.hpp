#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#define IMP(a, b) ((a) ? (b) : (!(b)))
#define IFF(a, b) ((a) ? (b) : (!(a)))
#define XOR(a, b) ((a) ? (!(b)) : (b))
#define NAND(a, b) (!(a && b))
#define NOR(a, b) (!(a || b))
#define XNOR(a, b) (!(a) ? (b) : (!(b)))
#define AND(a, b) ((a) && (b))
#define OR(a, b) ((a) || (b))
#define NOT(a) (!(a))
class TruthTable
{
  private:
    vector<vector<bool>> possibleValues;
    int numPropositions;

    void fillPossibleValues();

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();
    void printTruthTable();

    bool compareFunctions();

    const pair<bool, bool> evaluateFunctions(const vector<bool> &values);
};

#endif
