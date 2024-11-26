#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define IMP(a, b) (!(a) || (b))
#define AND(a, b) ((a) && (b))
#define OR(a, b) ((a) || (b))
#define NOT(a) (!(a))

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

class TruthTable
{
  private:
    vector<vector<bool>> possibleValues;
    int numPropositions;
    void fillPossibleValues();

  public:
    TruthTable(int numPropositions);

    void printPossibleValues();

    void printTable(int n, bool (*f)(bool *, int), bool *table);

    bool compareTable(int n, bool (*f)(bool *, int), bool *table1, bool *table2);
};

#endif
