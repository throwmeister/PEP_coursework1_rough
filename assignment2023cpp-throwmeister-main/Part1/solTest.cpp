#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

bool isOperator(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

std::vector<std::string> generateRPNExpressions(const std::vector<std::string> &numbers, const std::vector<std::string> &operators) {
    std::set<std::string> uniqueExpressions;
    std::vector<std::string> currentExpression;
    std::stack<std::string> stack;

    // Generate all possible permutations of numbers and operators
    std::vector<std::string> tokens;
    tokens.insert(tokens.end(), numbers.begin(), numbers.end());
    tokens.insert(tokens.end(), operators.begin(), operators.end());
    std::sort(tokens.begin(), tokens.end());

    do {
        stack = std::stack<std::string>();
        std::cout << "New stack" << "\n";

        for (const std::string& token : tokens) {
            std::cout << "Token: " << token << "\n";
            if (!isOperator(token)) {
                stack.push(token);
            } else {
                if (stack.size() < 2) {
                    // Invalid RPN expression
                    break;
                } else {
                    std::string operand2 = stack.top();
                    stack.pop();
                    std::string operand1 = stack.top();
                    stack.pop();
                    std::string rpnExpression = operand1 + " " + operand2 + " " + token;
                    stack.push(rpnExpression);
                }
            }
        }

        if (stack.size() == 1) {
            uniqueExpressions.insert(stack.top());
        }

    } while (std::next_permutation(tokens.begin(), tokens.end()));

    std::vector<std::string> allExpressions(uniqueExpressions.begin(), uniqueExpressions.end());
    return allExpressions;
}

void testFunc(){
    std::vector<std::string> numbers = { "1", "2", "3", "4", "5", "6" };
    std::vector<std::string> operators = { "+", "-", "*", "/" };

    int encMax = 1;
    for(int i = 0; i < numbers.size()-1; i++){
        encMax *= operators.size();
    }


    
    int tmp;

    for(int i = 0; i < encMax; i++){
        tmp = i;
        std::vector<int> digits;

        for(int j = 0; j < operators.size(); j++){
            digits.push_back(tmp%operators.size());
            tmp = tmp/operators.size();
        }


        std::string result = "";
        for(int j = 0; j < numbers.size()-1; j++){
            result += numbers[j] + operators[digits[j]];
        }
        result += numbers[numbers.size()-1];

        std::cout << "Result: " << result << "\n";

    }
}

int main() {
    std::vector<std::string> numbers = {"1", "2", "3", "4", "5" };
    std::vector<std::string> operators = { "+", "-", "*", "/" };

    std::vector<std::string> rpnExpressions = generateRPNExpressions(numbers, operators);
    
    std::cout << "All possible unique RPN expressions:" << std::endl;
    for (const std::string& expression : rpnExpressions) {
        std::cout << expression << std::endl;
    }
    

    return 0;
}


