#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <algorithm> // For std::sort, std::unique, std::transform
#include <iostream>  // For operator<<
#include <numeric>   // For std::accumulate (optional, alternative way to join strings)
#include <optional>  // To handle contradictions in MinTerm combination
#include <set>       // For storing unique literals/minterms
#include <stdexcept> // For potential errors
#include <string>    // Potentially needed if extending printing
#include <utility>   // For std::move
#include <vector>

// Forward declare classes to handle interdependencies (e.g., MinTerm::operator!)
class MinTerm;
class Expression;

/**
 * @brief Represents a boolean literal (e.g., 'A' or '!A').
 * Stores the variable character and its truth value (true for A, false for !A).
 */
class Literal
{
  private:
    char variable_ = '\0'; // Use underscore suffix for private members (common convention)
    bool value_ = false;

    // Make addition explicitly deleted (as before)
    Literal operator+(const Literal &other) const = delete;

  public:
    // Constructor
    Literal(char variable, bool value) : variable_(variable), value_(value)
    {
        // Basic validation: ensure it's a letter
        if (!std::isalpha(variable_))
        {
            throw std::invalid_argument("Literal variable must be an alphabet character.");
        }
        // Optional: Convert to uppercase for consistency
        variable_ = std::toupper(variable_);
    }

    // Default constructor (optional, might be useful)
    Literal() = default;

    // Getters
    char getVariable() const { return variable_; }
    bool getValue() const { return value_; }

    // Logical NOT operator: Returns the negated literal (!A becomes A, B becomes !B)
    Literal operator!() const { return Literal(variable_, !value_); }

    // Comparison operators (needed for std::set and sorting)
    bool operator<(const Literal &other) const
    {
        if (variable_ != other.variable_)
        {
            return variable_ < other.variable_;
        }
        // Treat non-negated (true) as "less than" negated (false) for consistent ordering
        return value_ > other.value_; // true (A) < false (!A)
    }

    bool operator==(const Literal &other) const { return variable_ == other.variable_ && value_ == other.value_; }

    // Inequality operator
    bool operator!=(const Literal &other) const { return !(*this == other); }

    // Friend declaration for stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Literal &lit);
};

// Stream insertion operator for Literal
inline std::ostream &operator<<(std::ostream &os, const Literal &lit)
{
    if (!lit.getValue())
    {
        os << '!'; // Print negation symbol if value is false
    }
    os << lit.getVariable();
    return os;
}

//-----------------------------------------------------------------------------

/**
 * @brief Represents a MinTerm (a product/AND of literals) in a Sum-of-Products expression.
 * Example: A * !B * C (represented as {Literal('A', true), Literal('B', false), Literal('C', true)})
 */
class MinTerm
{
  private:
    // Use std::set to automatically handle duplicate literals and keep them sorted
    std::set<Literal> literals_;

  public:
    // Constructor using an initializer list or vector
    MinTerm(std::initializer_list<Literal> literals) : literals_(literals)
    {
        if (hasContradiction())
        {
            // Option 1: Throw exception
            // throw std::logic_error("MinTerm created with contradiction.");
            // Option 2: Clear literals to represent "false" term (often preferred)
            literals_.clear(); // Represents a term that is always false
        }
    }
    MinTerm(const std::vector<Literal> &literals) : literals_(literals.begin(), literals.end())
    {
        if (hasContradiction())
        {
            literals_.clear();
        }
    }
    MinTerm(std::set<Literal> literals) : literals_(std::move(literals))
    {
        // Assume already checked or check again
        if (hasContradiction())
        {
            literals_.clear();
        }
    }

    // Default constructor: Represents an empty term (often considered "true" in some contexts, or neutral for OR)
    MinTerm() = default;

    // Check if the term contains a contradiction (e.g., A and !A)
    bool hasContradiction() const
    {
        for (const auto &lit : literals_)
        {
            // Check if the negation exists in the set
            if (literals_.count(!lit))
            {
                return true;
            }
        }
        return false;
    }

    // Check if the term is universally false (empty set after contradiction removal)
    bool isFalse() const
    {
        // An empty set *after* construction implies a contradiction was found and cleared.
        // Need a way to distinguish this from a default-constructed "true" term if that's needed.
        // For simplicity here, assume an empty term means contradiction occurred.
        return literals_.empty();
    }

    // Check if the term is universally true (empty set from default constructor - needs refinement if used)
    // bool isTrue() const { return literals_.empty() && !constructed_with_contradiction_flag; }

    // Getters (return by const reference)
    const std::set<Literal> &getLiterals() const { return literals_; }

    // Combine two minterms using AND logic.
    // Returns std::nullopt if the combination results in a contradiction (A * !A).
    // Otherwise, returns the combined MinTerm.
    std::optional<MinTerm> combineAnd(const MinTerm &other) const
    {
        // If either term is already false, the result is false
        if (this->isFalse() || other.isFalse())
        {
            return MinTerm({}); // Return an explicitly false term
        }

        std::set<Literal> combined = this->literals_;
        combined.insert(other.literals_.begin(), other.literals_.end());

        MinTerm result(std::move(combined)); // Constructor checks for contradictions

        if (result.isFalse())
        {
            return std::nullopt; // Indicate contradiction
        }
        return result;
    }

    // Logical NOT operator (De Morgan's Law for products)
    // !(A * B * !C) becomes !A + !B + C
    // This returns an Expression (Sum of Products), not a single MinTerm.
    Expression operator!() const; // Implementation requires Expression definition

    // Comparison operators (needed for std::set<MinTerm> in Expression)
    bool operator<(const MinTerm &other) const
    {
        return literals_ < other.literals_; // Lexicographical comparison of sets
    }
    bool operator==(const MinTerm &other) const { return literals_ == other.literals_; }
    bool operator!=(const MinTerm &other) const { return !(*this == other); }

    // Friend declaration for stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const MinTerm &term);
    friend class Expression; // Allow Expression to access private members if needed
};

// Stream insertion operator for MinTerm
inline std::ostream &operator<<(std::ostream &os, const MinTerm &term)
{
    if (term.isFalse())
    {
        os << "0"; // Represent a false term (contradiction)
        return os;
    }
    if (term.getLiterals().empty())
    {
        os << "1"; // Represent a true term (empty product) - convention varies
        return os;
    }

    // Print literals joined by "*" (representing AND)
    bool first = true;
    os << "("; // Group the term
    for (const auto &lit : term.getLiterals())
    {
        if (!first)
        {
            os << " * "; // Use * for AND within a term
        }
        os << lit;
        first = false;
    }
    os << ")";
    return os;
}

//-----------------------------------------------------------------------------

/**
 * @brief Represents a boolean expression in Sum-of-Products (SOP) form.
 * It's a collection (OR sum) of MinTerms.
 * Example: (A * !B) + (!A * C)
 */
class Expression
{
  private:
    // Use std::set to automatically handle duplicate minterms and keep them sorted
    std::set<MinTerm> minTerms_;

  public:
    // Default constructor: Represents an empty expression (logical false)
    Expression() = default;

    // Constructor with initializer list
    Expression(std::initializer_list<MinTerm> terms)
    {
        for (const auto &term : terms)
        {
            if (!term.isFalse())
            { // Don't add contradictory terms
                minTerms_.insert(term);
            }
        }
        // Apply basic absorption if desired (more complex simplification is possible)
        // simplify();
    }
    // Constructor from vector
    Expression(const std::vector<MinTerm> &terms)
    {
        for (const auto &term : terms)
        {
            if (!term.isFalse())
            {
                minTerms_.insert(term);
            }
        }
        // simplify();
    }
    // Constructor from set
    Expression(std::set<MinTerm> terms) : minTerms_(std::move(terms))
    {
        // Remove false terms if they exist
        std::erase_if(minTerms_, [](const MinTerm &mt) { return mt.isFalse(); });
        // simplify();
    }

    // Add a minterm to the expression (OR operation)
    void addMinTerm(const MinTerm &term)
    {
        if (!term.isFalse())
        { // Don't add contradictory terms
            minTerms_.insert(term);
            // Optionally call simplify() here
        }
    }

    // Getters
    const std::set<MinTerm> &getMinTerms() const { return minTerms_; }

    // Logical OR operator (+)
    Expression operator+(const Expression &other) const
    {
        Expression result = *this; // Copy current terms
        for (const auto &term : other.minTerms_)
        {
            result.addMinTerm(term); // Add terms from the other expression
        }
        // result.simplify(); // Optional simplification
        return result;
    }
    // Add a single minterm
    Expression operator+(const MinTerm &term) const
    {
        Expression result = *this;
        result.addMinTerm(term);
        // result.simplify();
        return result;
    }
    // Add a single literal (treat as a minterm with one literal)
    Expression operator+(const Literal &literal) const { return *this + MinTerm({literal}); }

    // Logical AND operator (*) - Distribution
    // (T1 + T2) * (T3 + T4) = (T1*T3 + T1*T4 + T2*T3 + T2*T4)
    Expression operator*(const Expression &other) const
    {
        Expression result;
        if (this->minTerms_.empty() || other.minTerms_.empty())
        {
            // If either expression is False (empty), the result is False
            return result; // Return empty expression
        }

        for (const auto &term1 : this->minTerms_)
        {
            for (const auto &term2 : other.minTerms_)
            {
                // Combine the two minterms using AND logic
                std::optional<MinTerm> combined = term1.combineAnd(term2);
                if (combined)
                { // Only add if it's not a contradiction
                    result.addMinTerm(*combined);
                }
            }
        }
        // result.simplify(); // Optional simplification
        return result;
    }
    // Multiply by a single minterm
    Expression operator*(const MinTerm &term) const { return *this * Expression({term}); }
    // Multiply by a single literal
    Expression operator*(const Literal &literal) const { return *this * MinTerm({literal}); }

    // Logical NOT operator (!) - De Morgan's Laws
    // !(T1 + T2 + ...) = !T1 * !T2 * ...
    // Requires MinTerm::operator! which returns an Expression
    Expression operator!() const
    {
        if (minTerms_.empty())
        {
            // !False is True (represented by a single MinTerm with no literals)
            return Expression({MinTerm()});
        }

        Expression result({MinTerm()}); // Start with True (identity for AND)
        for (const auto &term : minTerms_)
        {
            result = result * !term; // Requires MinTerm::operator!
        }
        // result.simplify(); // Optional simplification
        return result;
    }

    // Simplification (Basic Example: Remove subsumed terms like A + AB = A)
    // More advanced simplification (Quine-McCluskey etc.) is complex.
    void simplify()
    {
        // Basic Subsumption: Remove term T1 if there is another term T2 such that T2 is a subset of T1
        // Example: Remove ABC if AB exists.
        std::set<MinTerm> simplifiedTerms;
        for (const auto &term1 : minTerms_)
        {
            bool subsumed = false;
            for (const auto &term2 : minTerms_)
            {
                if (term1 == term2) continue;

                // Check if term2's literals are a subset of term1's literals
                bool term2_is_subset = std::includes(term1.getLiterals().begin(), term1.getLiterals().end(),
                                                     term2.getLiterals().begin(), term2.getLiterals().end());

                if (term2_is_subset)
                {
                    subsumed = true;
                    break; // term1 is subsumed by term2, no need to add term1
                }
            }
            if (!subsumed)
            {
                simplifiedTerms.insert(term1);
            }
        }
        minTerms_ = std::move(simplifiedTerms);
    }

    // Comparison operators
    bool operator==(const Expression &other) const { return minTerms_ == other.minTerms_; }
    bool operator!=(const Expression &other) const { return !(*this == other); }

    // Friend declaration for stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Expression &expr);
};

// --- Implementation of MinTerm::operator! ---
// Must be defined after Expression is fully defined.
inline Expression MinTerm::operator!() const
{
    // De Morgan's Law: !(L1 * L2 * ...) = !L1 + !L2 + ...
    // Each !Li becomes a MinTerm in the resulting Expression (Sum of Products).
    Expression result;
    if (isFalse())
    {
        // !False is True
        return Expression({MinTerm()}); // Return expression containing "1"
    }
    if (literals_.empty())
    {
        // !True is False
        return Expression(); // Return empty expression "0"
    }

    for (const auto &lit : literals_)
    {
        result.addMinTerm(MinTerm({!lit})); // Add the negation of each literal as a separate term
    }
    // Note: No simplification applied here, but could be added.
    return result;
}

// Stream insertion operator for Expression
inline std::ostream &operator<<(std::ostream &os, const Expression &expr)
{
    if (expr.getMinTerms().empty())
    {
        os << "0"; // Represent False (empty sum)
        return os;
    }

    // Print terms joined by "+" (representing OR)
    bool first = true;
    for (const auto &term : expr.getMinTerms())
    {
        if (!first)
        {
            os << " + "; // Use + for OR between terms
        }
        os << term;
        first = false;
    }
    return os;
}

// Helper functions to create Literals easily (optional)
inline Literal operator"" _lit(char c)
{
    return Literal(c, true); // e.g., 'A'_lit
}
// Cannot easily do !'A'_lit, need a function or use Literal('A', false)

#endif // PROPOSITIONS_H