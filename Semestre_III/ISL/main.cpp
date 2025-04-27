#include "Expressions.hpp" // Include the header file with your class definitions
#include <iostream>
#include <stdexcept> // Include for exception handling
#include <vector>

int main()
{
    try
    {
        // --- 1. Create Literals ---
        std::cout << "--- Creating Literals ---" << std::endl;
        Literal A('A', true);     // Represents 'A'
        Literal notA = !A;        // Represents '!A'
        Literal B('B', true);     // Represents 'B'
        Literal notB('B', false); // Represents '!B'
        Literal C('C', true);     // Represents 'C'
        Literal D('D', true);     // Represents 'D'

        std::cout << "A: " << A << std::endl;
        std::cout << "!A: " << notA << std::endl;
        std::cout << "B: " << B << std::endl;
        std::cout << "!B: " << notB << std::endl;
        std::cout << "C: " << C << std::endl;
        std::cout << std::endl;

        // --- 2. Create MinTerms ---
        // A minterm is a product (AND) of literals.
        std::cout << "--- Creating MinTerms ---" << std::endl;
        MinTerm t1({A, notB});      // Represents (A * !B)
        MinTerm t2({notA, B, C});   // Represents (!A * B * C)
        MinTerm t3({A, B});         // Represents (A * B)
        MinTerm t_true({});         // Represents True ("1")
        MinTerm t_false({A, notA}); // Represents False ("0") due to contradiction

        std::cout << "Term 1 (A * !B): " << t1 << std::endl;
        std::cout << "Term 2 (!A * B * C): " << t2 << std::endl;
        std::cout << "Term 3 (A * B): " << t3 << std::endl;
        std::cout << "Term True (empty product): " << t_true << std::endl;
        std::cout << "Term False (A * !A): " << t_false << std::endl; // Should print 0
        std::cout << "Is Term False actually false? " << std::boolalpha << t_false.isFalse() << std::endl;
        std::cout << std::endl;

        // --- 3. Create Expressions ---
        // An expression is a sum (OR) of minterms.
        std::cout << "--- Creating Expressions ---" << std::endl;
        Expression expr1({t1, t2}); // Represents (A * !B) + (!A * B * C)
        Expression expr2({t3});     // Represents (A * B)
        Expression expr_empty;      // Represents False ("0")

        std::cout << "Expression 1: " << expr1 << std::endl;
        std::cout << "Expression 2: " << expr2 << std::endl;
        std::cout << "Empty Expression: " << expr_empty << std::endl;
        std::cout << std::endl;

        // --- 4. Perform Operations ---
        std::cout << "--- Performing Operations ---" << std::endl;

        // OR (+) Operations
        Expression expr_sum = expr1 + expr2; // (A*!B) + (!A*B*C) + (A*B)
        std::cout << "expr1 + expr2: " << expr_sum << std::endl;
        Expression expr_sum_term = expr1 + MinTerm({C, D}); // Add term (C*D)
        std::cout << "expr1 + (C*D): " << expr_sum_term << std::endl;
        Expression expr_sum_lit = expr1 + A; // Add literal A (becomes term (A))
        std::cout << "expr1 + A: " << expr_sum_lit << std::endl;
        std::cout << std::endl;

        // AND (*) Operations (Distribution)
        // expr1 * expr2 = ((A*!B) + (!A*B*C)) * (A*B)
        //             = (A*!B)*(A*B) + (!A*B*C)*(A*B)
        //             = (A*!B*B) + (!A*A*B*C) --> Both terms have contradictions
        Expression expr_prod = expr1 * expr2;
        std::cout << "expr1 * expr2: " << expr_prod << std::endl; // Should be 0 (False)

        // Example that doesn't result in False
        Expression expr_ab({MinTerm({A}), MinTerm({B})}); // (A) + (B)
        Expression expr_cd({MinTerm({C}), MinTerm({D})}); // (C) + (D)
        Expression expr_prod_2 = expr_ab * expr_cd;       // (A+B)*(C+D) = AC + AD + BC + BD
        std::cout << "(A+B)*(C+D): " << expr_prod_2 << std::endl;
        std::cout << std::endl;

        // NOT (!) Operations
        std::cout << "!(Literal A): " << !A << std::endl;
        // !(Term (A * !B)) = !A + B
        Expression not_t1 = !t1;
        std::cout << "!(Term (A * !B)): " << not_t1 << std::endl;
        // !(Expression (A*!B) + (!A*B*C)) = !(A*!B) * !(!A*B*C)
        //                            = (!A+B) * (A+!B+!C)
        Expression not_expr1 = !expr1;
        std::cout << "!(Expression 1): " << not_expr1 << std::endl;
        std::cout << std::endl;

        // --- 5. Simplification ---
        std::cout << "--- Simplification ---" << std::endl;
        // Example: A + AB = A
        Expression expr_to_simplify({MinTerm({A}), MinTerm({A, B})});
        std::cout << "Before Simplify (A + AB): " << expr_to_simplify << std::endl;
        expr_to_simplify.simplify();                                                // Apply basic subsumption
        std::cout << "After Simplify (A + AB):  " << expr_to_simplify << std::endl; // Should just be (A)
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Indicate error
    }

    return 0; // Indicate success
}