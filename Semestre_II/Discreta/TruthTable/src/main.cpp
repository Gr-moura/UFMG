#include "TruthTable.hpp"
#include <locale>

int main()
{
    // Enable UTF-8 locale (may help on some systems)
    std::setlocale(LC_ALL, "");

    // Initialize the truth table with 3 propositions
    // The number of propositions can be changed as needed
    TruthTable t(3);

    t.printTruthTable();
    t.printProductOfSums();
    t.printSumOfProducts();

    return 0;
}