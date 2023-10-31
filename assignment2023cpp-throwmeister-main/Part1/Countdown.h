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

void createStrPermutationsRecursion(std::vector<std::vector<std::string>> &finalPermutations, const std::vector<std::string> &vals,
 std::vector<std::string> &permutation, std::vector<bool> &distinctVal, const int targetSize){
    // Checks for uniqueness in vals
    if (permutation.size() == targetSize){
        // Push finished permutation onto vector
        finalPermutations.push_back(permutation);
        return;
    }
    for (int i = 0; i < vals.size(); i++){
        // Checker for distinct value
        if (!distinctVal[i]){
            // recursion loop
            distinctVal[i] = true;
            permutation.push_back(vals[i]);
            createStrPermutationsRecursion(finalPermutations, vals, permutation, distinctVal, targetSize);
            distinctVal[i] = false;
            permutation.pop_back();
        }
    }
}

void createOperatorPermutationsRecursion(std::vector<std::vector<std::string>> &finalPermutations, const std::vector<std::string> &vals,
 std::vector<std::string> &permutation, const int targetSize){
    // Does not check for uniqueness in vals
    if (permutation.size() == targetSize){
        // Push finished permutation onto vector
        finalPermutations.push_back(permutation);
        return;
    }
    for (int i = 0; i < vals.size(); i++){
        // recursion loop
        // {x - / *}
        permutation.push_back(vals[i]);
        createOperatorPermutationsRecursion(finalPermutations, vals, permutation, targetSize);
        permutation.pop_back();
    }

}

void createPatternPermutationsRecursion(std::vector<std::vector<int>> &finalPermutations, const std::vector<int> &vals,
 std::vector<int> &permutation, std::vector<bool> &distinctVal, const int targetSize){
    // Checks for uniqueness in vals
    if (permutation.size() == targetSize){
        // Push finished permutation onto vector
        finalPermutations.push_back(permutation);
        return;
    }
    for (int i = 0; i < vals.size(); i++){
        // Checker for distinct value
        if (!distinctVal[i]){
            // recursion loop
            distinctVal[i] = true;
            permutation.push_back(vals[i]);
            createPatternPermutationsRecursion(finalPermutations, vals, permutation, distinctVal, targetSize);
            distinctVal[i] = false;
            permutation.pop_back();
        }
    }
}

void createPatternPermutations(std::vector<std::vector<int>> &finalPermutations, const std::vector<int> &vals,
 std::vector<int> &permutation, const int targetSize, int &operands, int &operators){
     if (permutation.size() == targetSize){
        // Push finished permutation onto vector
        if (operands==targetSize-5 && operators==targetSize-4){
            finalPermutations.push_back(permutation);
        }
        return;
    }
    for (int i = 0; i < vals.size(); i++){
        // Checker for distinct value
        auto var = vals[i];
        permutation.push_back(var);
        if (var==1){
            operands += 1;
        } else{
            operators += 1;
        }
        createPatternPermutations(finalPermutations, vals, permutation, targetSize, operands, operators);
        
        if (permutation.back()==1){
            operands -= 1;
        } else{
            operators -= 1;
        }
        permutation.pop_back();
    }

 }
std::vector<std::vector<std::string>> permuteString(const std::vector<std::string> &vals, const int targetSize){
    std::vector<std::vector<std::string>> permutations;
    std::vector<bool> distinctVals(vals.size(), false);
    std::vector<std::string> _p;
    createStrPermutationsRecursion(permutations, vals, _p, distinctVals, targetSize);
    return permutations;
}

std::vector<std::vector<std::string>> permuteOperators(const std::vector<std::string> &ops, const int targetSize){
    std::vector<std::vector<std::string>> permutations;
    std::vector<std::string> _p;
    std::cout << "This ran right?\n";
    createOperatorPermutationsRecursion(permutations, ops, _p, targetSize);
    return permutations;
}

std::vector<std::vector<int>> permutePattern(const std::vector<int> &vals, const int targetSize){
    std::vector<std::vector<int>> permutations;
    std::vector<bool> distinctVals(vals.size(), false);
    std::vector<int> _p;
    int x = 0;
    int y = 0;
    createPatternPermutations(permutations, vals, _p, targetSize, x, y);

    auto it = permutations.begin();

    while(it != permutations.end()){
        int operators = 0;
        int operands = 0;
        bool fail = false;
        for(auto &val: *it){
            if(val==1){
                operands += 1;
            } else{
                operators += 1;
            }
            if (operators>operands+1){
                fail = true;
                break;
            }
        }
        if (fail){
            permutations.erase(it);
            continue;
        }
        it++;
    }
    for (auto &exp: permutations){
        
    }
    return permutations;
}

std::vector<std::vector<int>> permuteAbstractOpCombos(const int numOfOps){
    // aaaa+++++ ts=9 os=4
    // aaa++++
    // aa+++
    // a++
    // +

    // redo algorithm to be much more efficient
    /*
    
    for (int i=0; i<numOfOps-1; i++){
        abstractOp.push_back(1);
    }
    for (int i=0; i<numOfOps; i++){
        abstractOp.push_back(0);
    }
    auto pattern = permutePattern(abstractOp, (numOfOps*2)-1);
    */
    std::vector<int> abstractOp = {1, 0};
    auto pattern = permutePattern(abstractOp, (numOfOps*2)-1);
    std::cout << "One permutation\n";
    return pattern;
}



CountdownSolution solveCountdownProblem(std::vector<int> numbers, const int targetNum){
    // bruteforce: build every possible rpn expression until the target number is reached or the closest#
    // Idea: when bulding the rpn string, check if + and * expressions do the same thing: prevent repeat evalutations
    int closestTarget = 0;
    const std::vector<std::string> operators = { "+", "-", "*", "/" };
    
    // temp holder
    std::vector<std::string> tmpStrNums;

    for (int num: numbers){
        tmpStrNums.push_back(intToString(num));
    }

    const std::vector<std::string> strNums = tmpStrNums;

    // 5 Layers 1-5
    
    std::vector<std::vector<std::string>> finalRPNs;

    for (int numOfOps = 5; numOfOps < 6; numOfOps++){

        auto finalNums = permuteString(strNums, numOfOps+1);
        auto finalOps = permuteOperators(operators, numOfOps);
        auto rpnTemplates = permuteAbstractOpCombos(numOfOps);
        
        //std::vector<std::vector<std::string>> staticNums = permuteString(strNums, 2); 1,2
        //std::vector<std::vector<std::string>> rpnExpressions = permuteString(strNums, numOfOps-1);
        std::cout << "Breakpoint\n";
        for(auto &expression: finalNums){
            std::vector<std::string> staticRPNStart;

            for (int i = 0; i<2; i++){
                //std::cout << expression.back() << "\n";
                staticRPNStart.push_back(expression.back());
                expression.pop_back();
            }
            // staticRPNStart == {"6", "5"}
            // expression = {"1", "2", "3", "4"}

            for(const auto &op: finalOps){
                // +++++
                // Match operators and operands to pattern
                for(auto const &pattern: rpnTemplates){
                    std::vector<std::string> opTmp(op);
                    std::vector<std::string> expTmp(expression);
                    std::vector<std::string> exp(staticRPNStart);
                    for(auto const &p: pattern){
                        // 1 = operand
                        // 0 = operator
                        if(p==1){
                            exp.push_back(expTmp.back());
                            expTmp.pop_back();
                        } else{
                            exp.push_back(opTmp.back());
                            opTmp.pop_back();
                        }
                    }
                }
            }
        }
    }
    
    /*
    for (const std::vector<std::string>& expressions : finalRPNs) {
        for (const std::string &exp: expressions){
            std::cout << exp << " ";
        }
        std::cout << "\n";
    }

    for (auto &n: permutateExpression){
                    std::cout << n;
                }
                std::cout << "\n";
    */
    

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


double evaluateCountdown(const std::string &rnp_string){
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
