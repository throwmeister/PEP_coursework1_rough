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
    // aka vector of a vector of a vector
    //[[[]], [[]], [[1,2,3..]], ]
    vector<vector<SetSolverSquareSet>>board;
    
public:
    SetSolver()
    {
        //implement your code here
    }
    void PopulateBoard(vector<string>skeletonBoard)
    {
        // Initialise vector size 9x9
        vector<vector<SetSolverSquareSet>> board(boardSize, vector<SetSolverSquareSet>(boardSize));

        // for each line
        for(std::size_t i=0; i<boardSize; i++){
            string reader = skeletonBoard[i];
            bool negative = false;
            int j = 0;
            for(auto& r: reader){
                if(r=='*'){
                    std::cout << "e ";
                    board[i][j] = SetSolverSquareSet(99);

                } else if(r=='-'){
                    std::cout << "-";
                    negative = true;
                    continue;
                } else{
                    if(negative){
                        std::cout << "nn ";
                        int a = r;
                        a *= -1;
                        board[i][j] = SetSolverSquareSet(a);
                        negative = false;
                    } else{
                        int b = r;
                        board[i][j] = SetSolverSquareSet(b);
                        std::cout << "n ";
                    }
                }
                j++;

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
