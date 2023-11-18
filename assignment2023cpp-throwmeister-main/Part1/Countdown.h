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

std::string vecCharToString(const std::vector<std::string>& vec){
    std::stringstream stream;
    for (auto it = vec.begin(); it != vec.end(); it++) { 
        stream << *it << " "; 
    }
    return stream.str();
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

double evaluateCountdown(const std::vector<std::string> &rpnVector){
    // rnp_string is a reverse-polish notation expression
    std::vector<double> stack(6);

    double* n1 = new double;
    double* n2 = new double;

    for(auto& val: rpnVector){
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
            if(*n2==0){
                stack.push_back(-9999);
                break;
            }
            stack.push_back((*n1)/(*n2));
            
        } else{
            // convert str -> double
            std::stringstream numstream;
            numstream << val;
            double val_num;
            numstream >> val_num;
            stack.push_back(val_num);
        }
    }

    delete n1;
    delete n2;
    n1 = nullptr;
    n2 = nullptr;

    return stack.back();
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
            if(*n2==0){
                stack.push_back(-9999);
                break;
            }
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
    n1 = nullptr;
    n2 = nullptr;

    return stack.back();
};



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

void createPatternPermutations(std::vector<std::vector<int>> &finalPermutations, const std::vector<int> &vals,
 std::vector<int> &permutation, const int targetSize, int &operands, int &operators){
     if (permutation.size() == targetSize){
        // Push finished permutation onto vector
        // size 1: 1 operator 0 operands
        // size 3: 2 operators 1 operand
        // size 5: 3 operators 2 operands
        if (operands==(targetSize-1)/2 && operators==(targetSize+1)/2){
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
    createOperatorPermutationsRecursion(permutations, ops, _p, targetSize);
    return permutations;
}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> permutePattern(const std::vector<int> &vals, const int targetSize){
    std::vector<std::vector<int>> permutations;
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

    // indexPerms:
    // indexPerm: for pattern 00100100111
    // first 5 vals: [0,1,3,4,6,7] next 4: [2,6,8,9,10]

    std::vector<std::vector<int>> operandIndex(permutations.size());
    std::vector<std::vector<int>> operatorIndex(permutations.size());
    int p = 0;
    for (auto& exp: permutations){
        // 5 operators, 4 operands
        for(int i=0; i<(int)exp.size(); i++){
            if(exp[i] == 1){
                operandIndex[p].push_back(i);
            } else{
                operatorIndex[p].push_back(i);
            }
        }
        p++;
    }
    auto t = std::make_pair(operandIndex, operatorIndex);
    return t;

}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> permuteAbstractOpCombos(const int numOfOps){
    // aaaa+++++ ts=9 os=4
    // aaa++++
    // aa+++
    // a++
    // +

    std::vector<int> abstractOp = {1, 0};
    auto pattern = permutePattern(abstractOp, (numOfOps*2)-1);
    return pattern;
}


CountdownSolution solveCountdownProblem(std::vector<int> numbers, const int targetNum){
    // bruteforce: build every possible rpn expression until the target number is reached or the closest#
    const std::vector<std::string> operators = { "+", "-", "*", "/" };
    // temp holder
    std::vector<std::string> tmpStrNums;

    for (int num: numbers){
        tmpStrNums.push_back(intToString(num));
    }

    const std::vector<std::string> strNums = tmpStrNums;

    CountdownSolution currSol;

    for(int numOfOps=5; (int)numOfOps<numbers.size(); numOfOps++){
        auto finalNums = permuteString(strNums, numOfOps+1);
        auto finalOps = permuteOperators(operators, numOfOps);
        // first: operandIndex, second: operatorIndex
        auto rpnTemplates = permuteAbstractOpCombos(numOfOps);
        
        std::cout << numOfOps << "\n";

        
        std::vector<std::pair<std::vector<std::string>, int>> templateOpCombos;
        // combine permuteAbstractOpCombos and permuteOperators
        for(int i=0; i<(int)finalOps.size(); i++){
            auto& ops = finalOps[i];
            for(int x=0; x<(int)rpnTemplates.second.size(); x++){
                const auto& indexer = rpnTemplates.second[x];
                std::vector<std::string> templateOpCombo;
                templateOpCombo.resize((numOfOps*2)+1);
                for(int j=0; j<(int)ops.size(); j++){

                    auto op = ops[j][0];
                    templateOpCombo[indexer[j]+2] = op;
                }
                auto tmp = std::make_pair(templateOpCombo, x);
                templateOpCombos.push_back(tmp);
            }
        }

        // evaluation

        for(const auto& nums: finalNums){
            for(const auto& rpnOpTemplate: templateOpCombos){
                std::vector<std::string> expression = rpnOpTemplate.first;
                expression[0] = nums[0];
                expression[1] = nums[1];
                for(int i=2; i<numOfOps+1; i++){
                    const int index = rpnTemplates.first[rpnOpTemplate.second][i-2];
                    expression[index+2] = nums[i];
                }
                
                const double eval = evaluateCountdown(expression);
                if(eval>0&&(eval==(int)eval)){
                    // valid num
                    if(eval==targetNum){
                        // set currSol
                        std::string opSolution = vecCharToString(expression);
                        currSol = CountdownSolution(opSolution, eval);
                        return currSol;
                    } else if(abs(targetNum-eval)<abs(targetNum-currSol.getValue())){
                        // this expression is closer to the target
                        // set currSol
                        std::string opSolution = vecCharToString(expression);
                        currSol = CountdownSolution(opSolution, eval);
                    }
                }
            }
        }
    }

    

    return currSol;
}




// Do not edit below this line


#endif
