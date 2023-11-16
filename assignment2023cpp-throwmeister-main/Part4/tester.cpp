
#include "SetSolver.h"

using std::cout;
using std::unique_ptr;


int main()
{
    int retval =0;
    {

        unique_ptr<SetSolver>board(new SetSolver());
        
        vector<string>
        skeletonBoard{      "00**0-31*0",
                            "*****0**0",
                            "7*003*-5**",
                            "**05**7**",
                            "*0**0*6-9*",
                            "4***650**",
                            "*2-8**00**",
                            "-23*0*****",
                            "043-608*0-1"};
        
        vector<string> hardSkeletonBoard{
            "02**-6***0",
            "****0**68",
            "**-4***0**",
            "0********",
            "0-1*2***00",
            "******1*-9",
            "**0***0**",
            "7***0****",
            "-27**0**30"
        };

        board->PopulateBoard(hardSkeletonBoard);
        
        std::cout << board->ReturnValue(0, 1) << "\n";

        board->Solve();
        for(size_t row=0;row<9;++row){
            for (size_t col=0; col<9;++col){
                std::cout<< board->ReturnValue(row, col);
            }
            std::cout<< "\n";
        }
    }
}