#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

// Helper functions to trim strings
std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    return start == std::string::npos ? "" : str.substr(start, end - start + 1);
}

// Function to evaluate logical operations
bool evaluate(const std::string &op, const std::vector<bool> &args)
{
    if (op == "AND")
    {
        return args[0] && args[1];
    }
    else if (op == "OR")
    {
        return args[0] || args[1];
    }
    else if (op == "NOT")
    {
        return !args[0];
    }
    else if (op == "IMPLIES")
    {
        return !args[0] || args[1];
    }
    else if (op == "IFF")
    {
        return args[0] == args[1];
    }
    throw std::invalid_argument("Unknown operator: " + op);
}

// Function to parse and evaluate a logical expression
bool parseAndEvaluate(const std::string &expression, const std::map<std::string, bool> &variables)
{
    std::stack<std::string> ops;
    std::stack<std::vector<bool>> values;

    size_t i = 0;
    while (i < expression.length())
    {
        if (expression[i] == ' ' || expression[i] == ',')
        {
            // Ignore whitespace and commas
            ++i;
        }
        else if (expression[i] == '(')
        {
            // Start of a sub-expression
            ++i;
        }
        else if (expression[i] == ')')
        {
            // End of a sub-expression: evaluate
            std::string op = ops.top();
            ops.pop();

            std::vector<bool> args;
            while (!values.empty() && values.top().size() == 1)
            {
                args.push_back(values.top().front());
                values.pop();
            }
            std::reverse(args.begin(), args.end());

            bool result = evaluate(op, args);
            if (!values.empty())
            {
                values.top().push_back(result);
            }
            else
            {
                values.push({result});
            }
            ++i;
        }
        else
        {
            // Read an operator or variable
            size_t j = i;
            while (j < expression.length() && expression[j] != '(' && expression[j] != ',' && expression[j] != ')')
            {
                ++j;
            }
            std::string token = trim(expression.substr(i, j - i));
            i = j;

            if (variables.count(token))
            {
                // It's a variable
                if (values.empty())
                {
                    values.push({variables.at(token)});
                }
                else
                {
                    values.top().push_back(variables.at(token));
                }
            }
            else
            {
                // It's an operator
                ops.push(token);
            }
        }
    }

    // Final result
    if (!values.empty() && !values.top().empty())
    {
        return values.top().front();
    }
    throw std::invalid_argument("Malformed expression");
}

int main()
{
    // Define variables
    std::map<std::string, bool> variables = {{"a", true}, {"b", false}};

    // Logical expression
    std::string expression = "AND(a, IMPLIES(a, b))";

    try
    {
        bool result = parseAndEvaluate(expression, variables);
        std::cout << "Result: " << (result ? "true" : "false") << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
