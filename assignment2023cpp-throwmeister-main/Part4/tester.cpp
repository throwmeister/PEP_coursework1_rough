
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

        board->PopulateBoard(skeletonBoard);

        std::cout << board->ReturnValue(0, 1) << "\n";
    }
}