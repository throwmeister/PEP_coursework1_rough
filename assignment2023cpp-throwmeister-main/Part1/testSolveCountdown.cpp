#include "Countdown.h"

#include <iostream>
using std::cout;

#include <vector>
using std::vector;

int main(){
    vector<int> numbers{1,2,3,4,5,6};
    CountdownSolution answer = solveCountdownProblem(numbers, 21);

    return 0;
}