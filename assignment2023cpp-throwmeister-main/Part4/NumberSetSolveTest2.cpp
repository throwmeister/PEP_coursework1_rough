
// Do not add any additional classes.
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "SetSolver.h"


using std::cout;
using std::unique_ptr;

int main() {
    int retval = 0;

    // board 1
    cout<<"\n\n\nBoard 1\n";
    {

        unique_ptr<SetSolver> board(new SetSolver());

        vector<string>
                skeletonBoard{"00**0-31*0",
                              "*****0**0",
                              "7*003*-5**",
                              "**05**7**",
                              "*0**0*6-9*",
                              "4***650**",
                              "*2-8**00**",
                              "-23*0*****",
                              "043-608*0-1"};

        board->PopulateBoard(skeletonBoard);
        board->Solve();

        vector<vector<int>> skeletonAnswer
                {
                        {0,  0, 6,  7,  0, -3, 1,  2,  0},
                        {6,  7, 5,  8,  4, 0,  2,  3,  0},
                        {7,  8, 0,  0,  3, 4,  -5, 1,  2},
                        {8,  9, 0,  5,  2, 6,  7,  4,  3},
                        {5,  0, 1,  2,  0, 7,  6,  -9, 4},
                        {4,  1, 2,  3,  6, 5,  0,  8,  7},
                        {3,  2, -8, 4,  5, 0,  0,  7,  6},
                        {-2, 3, 4,  0,  7, 9,  8,  6,  5},
                        {0,  4, 3,  -6, 0, 8,  9,  0,  -1}
                };
        for (size_t row = 0; row < 9; ++row) {
            for (size_t col = 0; col < 9; ++col) {
                if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                    cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                    retval++;
                }
            }
        }
    }

    if(retval==0) { cout << "Passed"; }
    else{cout<<"Failed";}

    cout<<"\n\n\nBoard 2\n";

    //board 2
    {
        unique_ptr<SetSolver> board(new SetSolver());

        vector<string>
                skeletonBoard{"-6*300**00",
                              "41*30*8*6",
                              "**0**0***",
                              "***-2***70",
                              "0-9**6**00",
                              "0****0***",
                              "**804*06*",
                              "**9*-12***",
                              "00560-42*0"};

        board->PopulateBoard(skeletonBoard);
        board->Solve();

        vector<vector<int>> skeletonAnswer
                {
                        {-6, 4,  3, 0,  0,  8,  7, 0, 0},
                        {4,  1,  2, 3,  0,  7,  8, 9, 6},
                        {3,  2,  0, 4,  5,  0,  6, 8, 7},
                        {5,  3,  4, -2, 8,  6,  9, 7, 0},
                        {0,  -9, 7, 8,  6,  5,  4, 0, 0},
                        {0,  8,  6, 9,  7,  0,  5, 4, 3},
                        {9,  7,  8, 0,  4,  3,  0, 6, 5},
                        {8,  6,  9, 7,  -1, 2,  3, 5, 4},
                        {0,  0,  5, 6,  0,  -4, 2, 3, 0},
                };
        for (size_t row = 0; row < 9; ++row) {
            for (size_t col = 0; col < 9; ++col) {
                if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                    cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                    retval++;
                }
            }
        }
    }

    if(retval==0) { cout << "Passed"; }
    else{cout<<"Failed";}
    cout<<"\n\n\nBoard 3\n";

//    board3

    {
        unique_ptr<SetSolver> board(new SetSolver());

        vector<string>
                skeletonBoard{"0***700*1",
                              "-5**7*0***",
                              "*3-1*****0",
                              "42*0-8***0",
                              "****0*5**",
                              "04**00**6",
                              "07****0**",
                              "***-9***30",
                              "*9-701***0",
        };

        board->PopulateBoard(skeletonBoard);
        board->Solve();

        vector<vector<int>> skeletonAnswer
                {
                        {0,  5, 8,  6,  7,  0, 0, 2, 1},
                        {-5, 8, 9,  7,  6,  0, 3, 1, 2},
                        {2,  3, -1, 8,  5,  6, 4, 7, 0},
                        {4,  2, 3,  0,  -8, 7, 6, 5, 0},
                        {3,  1, 4,  2,  0,  8, 5, 6, 7},
                        {0,  4, 2,  3,  0,  0, 7, 8, 6},
                        {0,  7, 6,  4,  3,  5, 0, 9, 8},
                        {7,  6, 5,  -9, 2,  4, 1, 3, 0},
                        {8,  9, -7, 0,  1,  3, 2, 4, 0},

                };
        for (size_t row = 0; row < 9; ++row) {
            for (size_t col = 0; col < 9; ++col) {
                if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                    cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                    retval++;
                }
            }
        }
    }

    if(retval==0) { cout << "Passed"; }
    else{cout<<"Failed";}

//    board4
    cout<<"\n\n\nBoard 4\n";

    {
        //board 4
        unique_ptr<SetSolver> board(new SetSolver());

        vector<string>
                skeletonBoard{"0-1**90**0",
                              "******4*0",
                              "***7-54*00",
                              "0*502*0*6",
                              "******6**",
                              "5*0**-97*0",
                              "-30**-4****",
                              "0****5***",
                              "0**0**50-2",
        };

        board->PopulateBoard(skeletonBoard);
        board->Solve();

        vector<vector<int>> skeletonAnswer
                {
                        {0,  -1, 7, 8, 9,  0,  2, 3, 0},
                        {7,  5,  6, 9, 8,  3,  4, 2, 0},
                        {6,  8,  9, 7, -5, 4,  3, 0, 0},
                        {0,  4,  5, 0, 2,  1,  0, 7, 6},
                        {4,  7,  8, 3, 1,  2,  6, 9, 5},
                        {5,  6,  0, 2, 3,  -9, 7, 8, 0},
                        {-3, 0,  2, 1, -4, 6,  8, 5, 7},
                        {0,  2,  3, 4, 7,  5,  9, 6, 8},
                        {0,  3,  4, 0, 6,  7,  5, 0, -2}
                };
        for (size_t row = 0; row < 9; ++row) {
            for (size_t col = 0; col < 9; ++col) {
                if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                    cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                    retval++;
                }
            }
        }
    }

    if(retval==0) { cout << "Passed"; }
    else{cout<<"Failed";}

    //board5
    cout<<"\n\n\nBoard 5\n";

    {
        {
            //board 5
            unique_ptr<SetSolver> board(new SetSolver());

            vector<string>
                    skeletonBoard{"0*****-1**",
                                  "0********",
                                  "**0-9***6*",
                                  "*0***0**-5",
                                  "0-4**0**00",
                                  "-26*0***03",
                                  "*****00*2",
                                  "*****3**0",
                                  "*70*****0",
            };

            board->PopulateBoard(skeletonBoard);
            board->Solve();

            vector<vector<int>> skeletonAnswer
                    {
                            {0,  3,  7, 4,  5, 6, -1, 9, 8},
                            {0,  1,  8, 3,  2, 4, 5,  7, 6},
                            {3,  2,  0, -9, 4, 5, 8,  6, 7},
                            {4,  0,  2, 1,  3, 0, 7,  8, -5},
                            {0,  -4, 3, 2,  0, 7, 6,  0, 0},
                            {-2, 6,  5, 0,  7, 8, 9,  0, 3},
                            {9,  5,  6, 7,  8, 0, 0,  3, 2},
                            {7,  8,  4, 6,  9, 3, 2,  5, 0},
                            {8,  7,  0, 5,  6, 2, 3,  4, 0},

                    };
            for (size_t row = 0; row < 9; ++row) {
                for (size_t col = 0; col < 9; ++col) {
                    if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                        cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                        retval++;
                    }
                }
            }
        }
    }

    if(retval==0) { cout << "Passed"; }
    else{cout<<"Failed";}


    cout<<"\n\n\nBoard 6\n";

    //board6

    {
        {
            //board 6
            unique_ptr<SetSolver> board(new SetSolver());

            vector<string>
                    skeletonBoard{"02**-6***0",
                                  "****0**68",
                                  "**-4***0**",
                                  "0********",
                                  "0-1*2***00",
                                  "******1*-9",
                                  "**0***0**",
                                  "7***0****",
                                  "-27**0**30",
            };

            board->PopulateBoard(skeletonBoard);
            board->Solve();

            vector<vector<int>> skeletonAnswer
                    {
                            {0,  2,  3,  1, -6, 7, 8, 9, 0},
                            {5,  3,  2,  4, 0,  9, 7, 6, 8},
                            {6,  5,  -4, 3, 1,  2, 0, 8, 7},
                            {0,  4,  5,  9, 3,  8, 2, 7, 6},
                            {0,  -1, 6,  2, 4,  5, 3, 0, 0},
                            {8,  6,  7,  5, 2,  3, 1, 4, -9},
                            {9,  8,  0,  7, 5,  6, 0, 1, 2},
                            {7,  9,  8,  6, 0,  1, 4, 2, 3},
                            {-2, 7,  9,  8, 0,  4, 5, 3, 0},

                    };
            for (size_t row = 0; row < 9; ++row) {
                for (size_t col = 0; col < 9; ++col) {
                    if ((board->ReturnValue(row, col)) != (skeletonAnswer[row][col])) {
                        cout << "Failed: when checking row: " << row << " col: " << col << "\n";
                        retval++;
                    }
                }
            }
        }
    }

    return 0;
}
