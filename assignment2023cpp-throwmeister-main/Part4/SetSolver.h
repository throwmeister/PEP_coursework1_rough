#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
//do not add additional libraries

class SetSolver
{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>>board;
    
public:
    SetSolver()
    {
        //implement your code here
    }
    void PopulateBoard(vector<string>skeletonBoard)
    {
        // for each line
        for(std::size_t i=0; i<skeletonBoard.size(); i++){
            string reader = skeletonBoard[i];
            bool negative = false;
            for(auto& r: reader){
                if(r=='*'){
                    std::cout << "e ";
                } else if(r=='-'){
                    std::cout << "-";
                    negative = true;
                } else{
                    if(negative){
                        std::cout << "nn ";
                        negative = false;
                    }
                    else{
                        std::cout << "n ";
                    }
                }
            }
            std::cout << "\n";
        }
    }
        
    int ReturnValue(size_t row, size_t col)
    {
        // implement your code here and
        
        //return the right value
        return 0;//This line was added temporarily 
    }
        
    void Solve()
    {
        // implement your code here
    }

//Don't edit below this line    
    
};
#endif /* SetSolver_h */
