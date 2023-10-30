#include "Countdown.h"
#include <bits/stdc++.h> 
#include <iostream>
using namespace std;

#include <vector>
using std::vector;

int main(){
    vector<int> numbers{1,2,3,4,5,6};
    CountdownSolution answer = solveCountdownProblem(numbers, 21);
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
