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
         vector<vector<SetSolverSquareSet>> b(boardSize, vector<SetSolverSquareSet>(boardSize));
         board = b;
    }
    void PopulateBoard(vector<string>skeletonBoard)
    {
        // Initialise vector size 9x9

        // for each line
        for(std::size_t i=0; i<boardSize; i++){
            string reader = skeletonBoard[i];
            bool negative = false;
            int j = 0;
            for(auto& r: reader){
                if(r=='*'){
                    std::cout << "*";
                    board[i][j] = SetSolverSquareSet(99);
                } else if(r=='-'){
                    negative = true;
                    continue;
                } else{
                    if(negative){
                        int a = r - '0';
                        a *= -1;
                        std::cout << a;
                        board[i][j] = SetSolverSquareSet(a);
                        negative = false;
                    } else{
                        int b = r - '0';
                        std::cout << b;
                        board[i][j] = SetSolverSquareSet(b);
                    }
                }
                j++;

            }
            std::cout << "\n";
        }
    }
        
    int ReturnValue(size_t row, size_t col)
    {
        return board[row][col].readValue;
    }
        
    void Solve()
    {
        // implement your code here
    }

    

//Don't edit below this line    
    
};
#endif /* SetSolver_h */
