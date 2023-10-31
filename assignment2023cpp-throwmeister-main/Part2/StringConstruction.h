#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;
#include <vector>
using std::vector;

// TODO: your code goes here:

struct stringConstructData
{
    string currStr;
    int currCost;
};


int stringConstruction(const string &targetStr, const int cloneCost, const int appendCost){
    string endStr = "";
    int totalCost = 0;
    int const targetSize = targetStr.size();
    
    // possible solution
    // cloned stringbreakpoint, score
    // Idea: create solution breakpoints
    vector<stringConstructData> clones;
    // Find if next part of targetStr is a substring
    // Then compare that clone cost vs the append cost of it

    while (endStr != targetStr){
        // Idea: wrap whole thing in a for loop iterating over scores in a vector
        // Then, check every score in the vector to solve the score problem
        
        int const endIndex = endStr.size();
        int const targetSizeLeft = targetStr.size() - endIndex;

        string foundSubstring = "";
        // Find if there is a substring in endStr which can be cloned
        for(int n = endIndex; (n>0) || (targetSizeLeft>(endIndex-n)); n--){
            string substring = targetStr.substr(endIndex, n);
            int substringPos = endStr.find(substring);
            if ((substringPos != string::npos) && (substring.length() > 1)){
                foundSubstring = substring;
                break;
            }
        }
        // Clone or append
        // possible altering
        if (!foundSubstring.empty() && ( (cloneCost/foundSubstring.length()) < appendCost)){
            // Clone is more effective

            stringConstructData tmp;
            tmp.currCost = totalCost+cloneCost;
            tmp.currStr = endStr+foundSubstring;
            clones.push_back(tmp);
            // endStr += foundSubstring;
            // totalCost += cloneCost;

        } 
        endStr.push_back(targetStr[endIndex]);
        totalCost += appendCost;
        
        // pointer to clone
        auto it = clones.begin();
        while (it != clones.end()){
            stringConstructData clone = *it;
            if (endIndex+1 == clone.currStr.size()){
                if (clone.currCost < totalCost){
                    totalCost = clone.currCost;
                }
                clones.erase(it);
                continue;
            }
            it++;
        }
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
