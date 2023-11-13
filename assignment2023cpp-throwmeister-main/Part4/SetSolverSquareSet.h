#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional classes.
#include <vector>


class SetSolverSquareSet
{
public:
    std::vector<int>set;
    int readValue;
    SetSolverSquareSet(int i){
        readValue = i;
        if(i==99){
            std::vector<int> set(9);
            for(int i = 1; i<10; i++){
                set.push_back(i);
            }
        }
        //Write your constructor here
    }

    // You can add any additional functions you'd like in order to help with the task

};

#endif /* SetSolverSquareSet_h */
