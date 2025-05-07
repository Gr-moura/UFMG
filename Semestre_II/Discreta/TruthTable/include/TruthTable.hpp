#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <iostream>
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
    void giveValues(bool &A, bool &B, bool &C, bool &D, bool &E, bool &F, bool &G, bool &H, bool &I, bool &J, bool &K,
                    bool &L, bool &M, bool &N, bool &O, bool &P, bool &Q, bool &R, bool &S, bool &T, bool &U, bool &V,
                    bool &W, bool &X, bool &Y, bool &Z, const vector<bool> &values);

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();
    void printTruthTable();
    void printProductOfSums();
    void printSumOfProducts();

    bool compareFunctions();

    const bool evaluateFunction(const vector<bool> &values);
    const pair<bool, bool> evaluateFunctions(const vector<bool> &values);
};

#endif
