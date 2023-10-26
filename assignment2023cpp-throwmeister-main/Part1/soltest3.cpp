#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>  // Include cmath for std::isnan

void generateRPNExpressions(const std::vector<int>& numbers, const std::string& operators, std::vector<std::string>& results, const std::string& current) {
    if (current.size() == (2 * numbers.size() - 1)) {
        results.push_back(current);
        return;
    }

    for (int i = 0; i < numbers.size(); ++i) {
        std::string newExpression = current + std::to_string(numbers[i]);
        generateRPNExpressions(numbers, operators, results, newExpression);

        if (current.size() > 0) {
            for (char op : operators) {
                std::string newExpressionWithOperator = current + op + std::to_string(numbers[i]);
                generateRPNExpressions(numbers, operators, results, newExpressionWithOperator);
            }
        }
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double evaluateRPN(const std::string& expression) {
    std::stack<double> stack;
    for (char c : expression) {
        if (isOperator(c)) {
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();

            double result;
            switch (c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        return std::numeric_limits<double>::quiet_NaN();  // Handle division by zero
                    }
                    break;
            }

            stack.push(result);
        } else {
            stack.push(c - '0');
        }
    }
    return stack.top();
}

int main() {
    std::vector<int> numbers = {1, 2, 3};
    std::string operators = "+-*/";
    std::vector<std::string> results;

    generateRPNExpressions(numbers, operators, results, "");
    
    for (const std::string& expression : results) {
        double value = evaluateRPN(expression);
        if (!std::isnan(value)) {
            std::cout << expression << " = " << value << std::endl;
        }
    }

    return 0;
}