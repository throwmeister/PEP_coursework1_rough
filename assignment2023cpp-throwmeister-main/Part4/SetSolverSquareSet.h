#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional classes.
#include <vector>


class SetSolverSquareSet
{
public:
    std::vector<int>set;
    int readValue;
    bool whiteBox;
    
    SetSolverSquareSet(){
        readValue = 0;
        whiteBox = false;
    }

    SetSolverSquareSet(int i): readValue(i){
        if(i==99){
            whiteBox = true;
            std::vector<int> x(9, 1);
            set = x;

        } else{
            if(i<1){
                whiteBox = false;
            } else{
                whiteBox = true;
            }
        }
        //Write your constructor here
    }

    // You can add any additional functions you'd like in order to help with the task

};

#endif /* SetSolverSquareSet_h */
