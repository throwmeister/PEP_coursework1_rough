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
    
    // row1: possible: 
    vector<vector<int>>rowNumNotPossible;
    vector<vector<int>>columnNumNotPossible;

    // [row][column].first - start of compartment, .second - end of compartment#
    // This vector is static - compartments always stay the same.
    vector<vector<std::pair<int, int>>>compartmentRow;
    vector<vector<std::pair<int, int>>>compartmentColumn;

    bool solved;
    
public:
    SetSolver()
    {
        vector<vector<SetSolverSquareSet>> b(boardSize, vector<SetSolverSquareSet>(boardSize));
        board = b;
        solved = false;

        vector<vector<int>> tmp2DVec(boardSize);
        /*
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                tmp2DVec[i][j] = 0;
            }
        }
        */
        rowNumNotPossible = tmp2DVec;
        columnNumNotPossible = tmp2DVec;

        vector<vector<std::pair<int, int>>> tmp2DPairVec(boardSize, vector<std::pair<int, int>>(boardSize));
        compartmentRow = tmp2DPairVec;
        compartmentColumn = tmp2DPairVec;
        // CompertmentColumn will still be indexed by [row][column]
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
                    board[i][j] = SetSolverSquareSet(99);
                } else if(r=='-'){
                    negative = true;
                    continue;
                } else{
                    if(negative){
                        int a = r - '0';
                        a *= -1;
                        board[i][j] = SetSolverSquareSet(a);
                        negative = false;
                    } else{
                        int b = r - '0';
                        board[i][j] = SetSolverSquareSet(b);
                    }
                }
                j++;
            }
        }
    }
        
    int ReturnValue(size_t row, size_t col)
    {
        return board[row][col].readValue;
    }
        
    void Solve(){
        // shows which compartment a cell is in.
        compartmantCreator();
        filterInitialPossible(board);
        filter();
    }

    void branchSolver(vector<vector<SetSolverSquareSet>> recBoard){

    }
    
    void filter(){

    }

    void filterInitialPossible(vector<vector<SetSolverSquareSet>>& cBoard){

        
        // rethink my filter strategy
        // first: get all column and row nums not allowed
        for(int row=0; row<boardSize; row++){
            for(int column=0; column<boardSize; column++){
                const SetSolverSquareSet& cell = cBoard[row][column];
                if(cell.readValue < 10 && cell.readValue != 0){
                    int a = abs(cell.readValue);
                    rowNumNotPossible[row].push_back(a);
                    columnNumNotPossible[column].push_back(a);
                }
            }
        }

        // next: get compartment limitations
        

    }

    void compartmantCreator(){
        // Row compartment
        for(int i = 0; i<boardSize; i++){
            int compartmentLenCount = 0;
            for(int j = 0; j<boardSize; j++){
                const SetSolverSquareSet& cell = board[i][j];
                if(cell.whiteBox){
                    // White square
                    if(j==boardSize-1){
                        int end = j;
                        int start = j-compartmentLenCount;
                        std::pair<int,int> compartmentIndexes = std::make_pair(start,end);
                        for(int x=start; x<j+1; x++){
                            compartmentRow[i][x] = compartmentIndexes;
                        }
                    }

                    compartmentLenCount += 1;
                } else{
                    // Black square
                    if(compartmentLenCount>0){
                        int end = j-1;
                        int start = j-compartmentLenCount;
                        std::pair<int,int> compartmentIndexes = std::make_pair(start,end);
                        for(int x=start; x<j; x++){
                            compartmentRow[i][x] = compartmentIndexes;
                        }

                    }
                    compartmentLenCount = 0;
                }
            }
        }

        //Column Compartment
        // currently broken
        for(int j = 0; j<boardSize; j++){
            int compartmentLenCount = 0;
            for(int i = 0; i<boardSize; i++){
                SetSolverSquareSet cell = board[i][j];
                if(cell.whiteBox){
                    // White square
                    if(i==boardSize-1){
                        int end = i;
                        int start = i-compartmentLenCount;
                        std::pair<int,int> compartmentIndexes = std::make_pair(start,end);
                        for(int x=start; x<i+1; x++){
                            compartmentColumn[x][j] = compartmentIndexes;
                        }
                    }

                    compartmentLenCount += 1;
                } else{
                    // Black square
                    if(compartmentLenCount>0){
                        int end = i-1;
                        int start = i-compartmentLenCount;
                        std::pair<int,int> compartmentIndexes = std::make_pair(start,end);
                        for(int x=start; x<i; x++){
                            compartmentColumn[x][j] = compartmentIndexes;
                        }

                    }
                    compartmentLenCount = 0;
                }
            }
        }

    }
    

//Don't edit below this line    
    
};
#endif /* SetSolver_h */
