#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
//do not add additional libraries

struct result{
    bool backtrack;
    bool filtered;
    bool solved;
};

struct bestBranch{
    int row;
    int column;
    // number of branches needed
    int options;
};

class SetSolver
{
private:
    int boardSize = 9;
    // aka vector of a vector of a vector
    //[[[]], [[]], [[1,2,3..]], ]
    vector<vector<SetSolverSquareSet>>board;
    
    // column+row numbers
    vector<vector<int>>rowNPossible;
    vector<vector<int>>columnNPossible;

    // vectors are static - compartments always stay the same.
    // [row][column].first - start of compartment, .second - end of compartment#
    vector<vector<std::pair<int, int>>>compartmentRow;
    vector<vector<std::pair<int, int>>>compartmentColumn;
    
    vector<vector<std::pair<int, int>>> iterateComponentRow;
    vector<vector<std::pair<int, int>>> iterateComponentColumn;
  
public:
    SetSolver()
    {
        vector<vector<SetSolverSquareSet>> b(boardSize, vector<SetSolverSquareSet>(boardSize));
        board = b;

        vector<vector<int>> tmp2DVec(boardSize, vector<int>(boardSize, 0));

        rowNPossible = tmp2DVec;
        columnNPossible = tmp2DVec;

        // each cell matching to a compartment: used in calc, always constant after initalisation in compartmentCreator()
        vector<vector<std::pair<int, int>>> tmp2DPairVec(boardSize, vector<std::pair<int, int>>(boardSize, std::pair<int,int>(-1, -1)));
        compartmentRow = tmp2DPairVec;
        compartmentColumn = tmp2DPairVec;
        // CompertmentColumn will still be indexed by [row][column]

        // list of compartments: used in calc, always constant after initalisation in compartmentCreator()
        vector<vector<std::pair<int, int>>> revisedTmp2dVec(boardSize);
        iterateComponentRow = revisedTmp2dVec;
        iterateComponentColumn = revisedTmp2dVec;

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

    int ReturnValue(size_t row, size_t col){
        return board[row][col].readValue;
    }

    void Solve(){
        setUp();

        bool x = loopSolve(board, rowNPossible, columnNPossible);
        if(!x){
            std::cout << "\n" << "ERROR: NO SOLUTION FOUND" << "\n";
        }
    }

    void setUp(){
        compartmantCreator();
        // filterInitialPossible(board);
    }

    // recusive loop for solving
    bool loopSolve(vector<vector<SetSolverSquareSet>>& cBoard, std::vector<std::vector<int>>& rowNotPossible, std::vector<std::vector<int>>& colNotPossible){
        result x;
        do{
            filterInitialPossible(cBoard, rowNotPossible, colNotPossible);
            x = reduce(cBoard);
        } while((!x.backtrack)&&(x.filtered)&&(!x.solved));

        if(x.solved){
            board = cBoard;
            return true;
        } else if(x.backtrack){
            // must backtrack
            return false;
        } else{
            // must branch
            bestBranch branch = getBestBranch(cBoard);
            const SetSolverSquareSet& cell = cBoard[branch.row][branch.column];
            vector<int> vOptions;
            for(int i=0; i<boardSize; i++){
                if(cell.set[i]==1){
                    vOptions.push_back(i+1);
                }
            }

            for(auto num: vOptions){
                vector<vector<SetSolverSquareSet>> newboard = cBoard;
                auto& newCell = newboard[branch.row][branch.column];
                newCell.readValue = num;
                newCell.set.clear();
                auto tmpR = rowNotPossible;
                auto tmpC = colNotPossible;
                bool succ = loopSolve(newboard, tmpR, tmpC);
                if(succ){
                    return true;
                }
            }
        }
        return false;
    }

    // Gets smallest branching pattern
    bestBranch getBestBranch(vector<vector<SetSolverSquareSet>>& cboard){
        bestBranch branch;
        branch.options = 10;
        branch.row = 0;
        branch.column = 0;
        for(int row=0; row<boardSize; row++){
            for(int column=0; column<boardSize; column++){
                SetSolverSquareSet& cell = cboard[row][column];
                if(cell.readValue == 99){
                    int sum = 0;
                    for(const auto& n: cell.set){
                        sum += n;
                    }
                    if(sum<branch.options){
                        branch.row = row;
                        branch.column = column;
                        branch.options = sum;
                    }
                }
            }
        }

        return branch;
    }

    result reduce(vector<vector<SetSolverSquareSet>>& cboard){
        result res;
        res.backtrack = false;
        res.filtered = false;
        res.solved = false;
        int emptyCellCount = 0;

        // pair(row, column)
        std::pair<int,int> c;
        for(int row=0; row<boardSize; row++){
            for(int column=0; column<boardSize; column++){
                if(res.filtered){
                    break;
                }
                SetSolverSquareSet& cell = cboard[row][column];
                if(cell.readValue == 99){
                    emptyCellCount++;
                    int sum = 0;
                    for(const auto& n: cell.set){
                        sum += n;
                    }
                    switch(sum){
                        case 0:
                            // invalid: must backtrack
                            res.backtrack = true;
                            return res;
                            break;
                        case 1:
                            // single value found, filter down
                            c = std::make_pair(row,column);
                            res.filtered = true;
                            break;
                    }
                }
            }
        }

        if(emptyCellCount==0){
            res.solved = true;
        }
        if(res.filtered){
            SetSolverSquareSet& cell = cboard[c.first][c.second];
            int cellNum = -99;
            for(int i=0; i<boardSize; i++){
                if(cell.set[i]==1){
                    cellNum = i+1;
                    break;
                }
            }
            cell.readValue = cellNum;
            cell.set.clear();
        }
        

        return res;

    }

    void filterInitialPossible(vector<vector<SetSolverSquareSet>>& cboard, std::vector<std::vector<int>>& rowNumNotPossible, std::vector<std::vector<int>>columnNumNotPossible){
        // first: get all column and row nums not allowed
        for(int row=0; row<boardSize; row++){
            for(int column=0; column<boardSize; column++){
                const SetSolverSquareSet& cell = cboard[row][column];
                int a = abs(cell.readValue);
                if(cell.readValue < 10 && cell.readValue != 0){
                    rowNumNotPossible[row][a-1] = 1;
                    columnNumNotPossible[column][a-1] = 1;
                }
            }
        }

        for(int row=0; row<boardSize; row++){
            for(auto& compartment: iterateComponentRow[row]){
                const int compartmentIndexDiff = compartment.second-compartment.first;
                int maxNum = 0;
                int minNum = 10;
                for(int i = compartment.first; i<compartment.second+1; i++){
                    const SetSolverSquareSet& cell = cboard[row][i];
                    if(cell.readValue!=99){
                        if(cell.readValue<minNum){
                            minNum = cell.readValue;
                        }
                        if(cell.readValue>maxNum){
                            maxNum = cell.readValue;
                        }
                    }
                }
                const int minLimit = maxNum-compartmentIndexDiff;
                const int maxLimit = minNum+compartmentIndexDiff;
                for(int i = compartment.first; i<compartment.second+1; i++){
                    SetSolverSquareSet& cell = cboard[row][i];
                    if(cell.readValue==99){
                        // set = (1,1,1,1,1,1,1,1,1)s
                        // representing set = (1,2,3,4,5,6,7,8,9)
                        // filter through: minLimit, maxLimit
                        for(int j=0; j<minLimit-1; j++){
                            // minlimit
                            cell.set[j] = 0;
                        }
                        for(int j=8; j>maxLimit-1; j--){
                            // maxLimit
                            cell.set[j] = 0;
                        }
                        for(int j=0; j<boardSize; j++){
                            // filter through: rowNumNotPossible, columnNumNotPossible
                            if(rowNumNotPossible[row][j]==1 || columnNumNotPossible[i][j]==1){
                                cell.set[j] = 0;
                            }
                        }
                    }
                }
            }
        }

        // column verison
        for(int column=0; column<boardSize; column++){
            for(auto& compartment: iterateComponentColumn[column]){
                const int compartmentIndexDiff = compartment.second-compartment.first;
                int maxNum = 0;
                int minNum = 10;
                for(int i = compartment.first; i<compartment.second+1; i++){
                    const SetSolverSquareSet& cell = cboard[i][column];
                    if(cell.readValue!=99){
                        if(cell.readValue<minNum){
                            minNum = cell.readValue;
                        }
                        if(cell.readValue>maxNum){
                            maxNum = cell.readValue;
                        }
                    }
                }

                const int minLimit = maxNum-compartmentIndexDiff;
                const int maxLimit = minNum+compartmentIndexDiff;

                for(int i = compartment.first; i<compartment.second+1; i++){
                    SetSolverSquareSet& cell = cboard[i][column];
                    if(cell.readValue==99){
                        // set = (1,1,1,1,1,1,1,1,1)s
                        // representing set = (1,2,3,4,5,6,7,8,9)
                        // filter through: minLimit, maxLimit
                        for(int j=0; j<minLimit-1; j++){
                            // minlimit
                            cell.set[j] = 0;
                        }

                        for(int j=8; j>maxLimit-1; j--){
                            // maxLimit
                            cell.set[j] = 0;
                        }
                    }
                }
            }
        }

        // compartment inconsistencies
        // come back to this
        /*
        for(int i=0; i<boardSize; i++){
            for(auto& compartment: iterateComponentRow[i]){
                for(int j = compartment.first; j<compartment.second+1; j++){
                }
            }
        }
        */
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
                        iterateComponentRow[i].push_back(compartmentIndexes);
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
                        iterateComponentRow[i].push_back(compartmentIndexes);
                        for(int x=start; x<j; x++){
                            compartmentRow[i][x] = compartmentIndexes;
                        }

                    }
                    compartmentLenCount = 0;
                }
            }
        }

        //Column Compartment
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
                        iterateComponentColumn[j].push_back(compartmentIndexes);
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
                        iterateComponentColumn[j].push_back(compartmentIndexes);
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
