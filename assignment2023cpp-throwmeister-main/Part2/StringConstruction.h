#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;
#include <vector>
using std::vector;

// FOR TESTING - REMOVE FINAL SOLUTION
#include <iostream>
using std::cout;


// TODO: your code goes here:

int stringConstruction(string &targetStr, int cloneCost, int appendCost){
    string endStr = "";
    int totalCost = 0;
    int const targetSize = targetStr.size();
    
    // possible solution
    // cloned stringbreakpoint, score
    // Idea: create solution breakpoints

    vector<std::pair<string, int>> clones;

    // Find if next part of targetStr is a substring
    // Then compare that clone cost vs the append cost of it

    while (endStr != targetStr){
        int endIndex = endStr.size();
        int const targetSizeLeft = targetStr.size() - endIndex;

        cout << "current string: " << endStr << "\n";
        cout << "endIndex: " << endIndex<< "\n";
        cout << "targetSizeLeft " << targetSizeLeft << "\n";

        string foundSubstring = "";
        // Find if there is a substring in endStr which can be cloned
        // more efficient version
        for(int n = endIndex; (n>0) || (targetSizeLeft>(endIndex-n)); n--){
            string substring = targetStr.substr(endIndex, n);
            int substringPos = endStr.find(substring);
            if ((substringPos != string::npos) && (substring.length() > 1)){
                foundSubstring = substring;
                break;
            }
        }
        
        cout << "foundSubstring: " << foundSubstring << "\n";
        // Clone or append
        // possible altering
        if (!foundSubstring.empty() && ( (cloneCost/foundSubstring.length()) < appendCost)){
            // Clone is more effective
            cout << "clone cost calc: " << (cloneCost/foundSubstring.length()) << "\n";
            endStr += foundSubstring;
            totalCost += cloneCost;
        } else{
            // Append is more effective
            endStr.push_back(targetStr[endIndex]);
            totalCost += appendCost;
        };

    }

    return totalCost;
};


/*
        for(int n = 0; (n<endIndex) || (n<targetSizeLeft); n++){
            // Gets substring from index of length n
            string substring = targetStr.substr(endIndex, n);
            int substringPos = endStr.find(substring);
            if (substringPos != string::npos){
                foundSubstring = substring;
            }
        }
*/

// do not write or edit anything below this line

#endif
