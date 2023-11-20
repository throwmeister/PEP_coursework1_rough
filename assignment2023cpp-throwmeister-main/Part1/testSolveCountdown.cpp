#include "Countdown.h"
#include <bits/stdc++.h> 
#include <iostream>
using namespace std;

#include <vector>
using std::vector;

int main(){

    // 50 10 3+* 25 1+ 7*+
    
    vector<std::string> tester{"50", "10", "3", "+", "*", "25", "1", "+", "7", "*", "+"};
    double x = evaluateCountdown(tester);
    {
        /*
        // {1, 3, 7, 10, 25, 50}  target :  831
        
        vector<int> numbers{1, 3, 7, 10, 25, 50};
        CountdownSolution answer = solveCountdownProblem(numbers, 831);

        cout<< "Unsolvable target. closest answer: " << answer.getValue() << "\n";
        */
    }
    double p = evaluateCountdown("75 2 5 + - 4 * 1 + ");
    vector<int> numbers{1,2,3,4,5,6};
    CountdownSolution answer = solveCountdownProblem(numbers, 11);
    /*
    time_t start, end;
    time(&start);

    ios_base::sync_with_stdio(false);
    

    time(&end);

    double time_taken = double(end-start);
    cout<< "Time taken: " << fixed << time_taken << setprecision(5);
    cout<< " sec " << endl;
    */
    return 0;
}
