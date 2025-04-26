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

void TruthTable::printTruthTable()
{
    cout << "Truth Table:" << endl;
    for (int i = 0; i < numPropositions; i++)
    {
        cout << (char)(i + 'A') << " ";
    }
    cout << "Y " << endl;

    for (vector<bool> values : possibleValues)
    {
        for (bool value : values)
        {
            cout << value << " ";
        }
        bool a = evaluateFunction(values);
        cout << a << " ";
        cout << endl;
    }
}

void TruthTable::printSumOfProducts()
{
    cout << "Sum of Products = ";
    int first = 1;

    for (int i = 0; i < possibleValues.size(); i++)
    {
        vector<bool> values = possibleValues[i];
        bool res = evaluateFunction(values);

        if (res)
        {
            if (!first)
            {
                cout << " + ";
            }

            for (int j = 0; j < numPropositions; j++)
            {
                char character = (char)(j + 'A');

                if (!values[j]) cout << "\u0305" << character;
                else cout << character;
            }

            first = false;
        }
    }

    cout << endl;
}

void TruthTable::printProductOfSums()
{
    cout << "Product of Sums = ";
    int first = 1;

    for (int i = 0; i < possibleValues.size(); i++)
    {
        vector<bool> values = possibleValues[i];
        bool res = evaluateFunction(values);

        if (!res)
        {
            cout << "(";

            for (int j = 0; j < numPropositions; j++)
            {
                char character = (char)(j + 'A');

                if (!values[j]) cout << character;
                else cout << "\u0305" << character;

                if (j != numPropositions - 1) cout << " + ";
            }

            cout << ")";
        }
    }

    cout << endl;
}

void TruthTable::giveValues(bool &A, bool &B, bool &C, bool &D, bool &E, bool &F, bool &G, bool &H, bool &I, bool &J,
                            bool &K, bool &L, bool &M, bool &N, bool &O, bool &P, bool &Q, bool &R, bool &S, bool &T,
                            bool &U, bool &V, bool &W, bool &X, bool &Y, bool &Z, const vector<bool> &values)
{
    for (int i = 0; i < values.size(); i++)
    {
        switch (i)
        {
            case 0: A = values[i]; break;
            case 1: B = values[i]; break;
            case 2: C = values[i]; break;
            case 3: D = values[i]; break;
            case 4: E = values[i]; break;
            case 5: F = values[i]; break;
            case 6: G = values[i]; break;
            case 7: H = values[i]; break;
            case 8: I = values[i]; break;
            case 9: J = values[i]; break;
            case 10: K = values[i]; break;
            case 11: L = values[i]; break;
            case 12: M = values[i]; break;
            case 13: N = values[i]; break;
            case 14: O = values[i]; break;
            case 15: P = values[i]; break;
            case 16: Q = values[i]; break;
            case 17: R = values[i]; break;
            case 18: S = values[i]; break;
            case 19: T = values[i]; break;
            case 20: U = values[i]; break;
            case 21: V = values[i]; break;
            case 22: W = values[i]; break;
            case 23: X = values[i]; break;
            case 24: Y = values[i]; break;
            case 25: Z = values[i]; break;

            default: break;
        }
    }
}

const bool TruthTable::evaluateFunction(const vector<bool> &values)
{
    bool A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;

    giveValues(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, values);

    bool f = OR(AND(A, B), C);
    return f;
}

const pair<bool, bool> TruthTable::evaluateFunctions(const vector<bool> &values)
{
    bool A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;

    giveValues(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, values);

    bool f1 = AND(AND(A, B), C);
    bool f2 = AND(NAND(A, B), C);

    return {f1, f2};
}

bool TruthTable::compareFunctions()
{
    bool different = false;

    vector<bool> resultsF1(pow(2, numPropositions));
    vector<bool> resultsF2(pow(2, numPropositions));

    for (int i = 0; i < pow(2, numPropositions); i++)
    {
        pair<bool, bool> results = evaluateFunctions(possibleValues[i]);

        resultsF1[i] = results.first;
        resultsF2[i] = results.second;

        if (results.first != results.second)
        {
            if (different == false)
            {
                cout << "Functions are not equivalent" << endl;
            }

            int character = 0;
            for (bool value : possibleValues[i])
            {
                cout << (char)(character + 'A') << ": ";
                cout << value << " ";

                character++;
            }

            cout << endl << "Resultado F1: " << resultsF1[i] << " Resultado F2: " << resultsF2[i] << "\n\n";
            different = true;
        }
    }

    if (!different)
    {
        cout << "Functions are equivalent" << endl;
    }
}
