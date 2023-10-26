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

void createPermutationsRecursion(std::vector<std::vector<std::string>> &finalPermutations, std::vector<std::string> &vals,
 std::vector<std::string> &permutation, std::vector<bool> &distinctVal){

    if (permutation.size() == vals.size()){
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
            createPermutationsRecursion(finalPermutations, vals, permutation, distinctVal);
            distinctVal[i] = false;
            permutation.pop_back();
        }
        
    }
}

std::vector<std::vector<std::string>> permuteString(std::vector<std::string> &vals){
    std::vector<std::vector<std::string>> permutations;
    std::vector<bool> distinctVals(vals.size(), false);
    std::vector<std::string> _p;
    createPermutationsRecursion(permutations, vals, _p, distinctVals);
    return permutations;
}


CountdownSolution solveCountdownProblem(std::vector<int> numbers, const int targetNum){
    // bruteforce: build every possible rpn expression until the target number is reached or the closest#
    // Idea: when bulding the rpn string, check if + and * expressions do the same thing: prevent repeat evalutations

    
    double closestTarget = 0;
    std::vector<std::string> operators = { "+", "-", "*", "/" };
    
    std::vector<std::string> strNums;

    for (int num: numbers){
        strNums.push_back(intToString(num));
    }

    std::vector<std::vector<std::string>> finalSolution = permuteString(strNums);
    
    for (const std::vector<std::string>& expression : finalSolution) {
        // std::cout << expression << std::endl;
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
