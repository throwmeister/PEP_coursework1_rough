#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>


// for debugging purposes
#include <iostream>

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:

// brute force
std::string RPNBuilder(std::vector<std::string> &numbers,
    std::vector<std::string> &ops){
    
    std::vector<std::string> expressions;
    // {'+', '*', '/', '-'}
    // {'1', '2', '3', '4', '5', '6'}

    // Num of num combos = 720
    // Num of operator combos = 120
    // always need 5 operators, 4 choices = 1024
    




}

void RPNExpressionRecusionCalc(std::vector<std::string> &numbers,
    std::vector<std::string> &ops,
    std::vector<std::string> &curExpression,
    std::vector<std::string> &finalSolution){
    if (numbers.empty() && ops.empty()){
        finalSolution.push_back(curExpression[0]);
        return;
    }

    if (!numbers.empty()){
        curExpression.push_back(numbers.back());
        numbers.pop_back();
        RPNExpressionRecusionCalc(numbers, ops, curExpression, finalSolution);
        numbers.push_back(curExpression.back());
        curExpression.pop_back();
    }

    if (!ops.empty()){
        curExpression.push_back(ops.back());
        ops.pop_back();
        RPNExpressionRecusionCalc(numbers, ops, curExpression, finalSolution);
        ops.push_back(curExpression.back());
        curExpression.pop_back();
    }

}

CountdownSolution solveCountdownProblem(const std::vector<int> numbers, const int targetNum){
    // bruteforce: build every possible rpn expression until the target number is reached or the closest#
    // Idea: when bulding the rpn string, check if + and * expressions do the same thing: prevent repeat evalutations

    
    double closestTarget = 0;
    std::vector<std::string> operators = { "+", "-", "*", "/" };
    std::vector<std::string> curExpression;
    std::vector<std::string> finalSolution;

    std::vector<std::string> strNums;

    for (int num: numbers){
        strNums.push_back(intToString(num));
    }

    RPNExpressionRecusionCalc(strNums, operators, curExpression, finalSolution);

    for (const std::string& expression : finalSolution) {
        std::cout << expression << std::endl;
    }

    CountdownSolution c;
    return c;
}

// used in evaluateCountdown
void pop_2_elements(std::vector<double> &stack, double* n1, double* n2){
    // Dereference n1 and n2, assign them to the new values, 
    // Remove values from the vector
    *n2 = stack.back();
    stack.pop_back();
    *n1 = stack.back();
    stack.pop_back();
};


double evaluateCountdown(std::string rnp_string){
    // rnp_string is a reverse-polish notation expression
    std::vector<double> stack(6);

    // create string stream
    std::stringstream stream(rnp_string);
    std::string val;

    //used for calculation
    double* n1 = new double;
    double* n2 = new double;

    // tokenise string
    while(getline(stream, val, ' ')){
        if (val=="+"){
            pop_2_elements(stack, n1, n2);
            stack.push_back((*n1)+(*n2));

        } else if(val=="-"){
            pop_2_elements(stack, n1, n2);
            stack.push_back((*n1)-(*n2));

        } else if(val=="*"){
            pop_2_elements(stack, n1, n2);
            stack.push_back((*n1)*(*n2));

        } else if(val=="/"){
            pop_2_elements(stack, n1, n2);
            stack.push_back((*n1)/(*n2));

        } else{
            // convert string -> double using stringstream
            // more fun :)
            std::stringstream numstream;
            numstream << val;
            double val_num;
            numstream >> val_num;

            stack.push_back(val_num);
        }
    }

    // cleanup
    delete n1;
    delete n2;

    return stack.back();
};



// Do not edit below this line


#endif
