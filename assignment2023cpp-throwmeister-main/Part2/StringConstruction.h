#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
// TODO: your code goes here:

struct stringConstructData
{
    int currStrSize;
    int currCost;
};


int stringConstruction(const string &targetStr, const int cloneCost, const int appendCost){
    string endStr = "";
    int totalCost = 0;
    int const targetSize = targetStr.size();
    
    vector<stringConstructData> clones;

    int biggestCurrentSubstr;

    // Find if next part of targetStr is a substring
    while (endStr.size() != targetSize){  
        int const endSize = endStr.size();
        int const targetSizeLeft = targetStr.size() - endSize;
        int foundSubstring = 0;
        // Find if there is a substring in endStr which can be cloned
        int lenOfSubstr;
        if(targetSizeLeft>endSize){
            lenOfSubstr = endSize;
        } else{
            lenOfSubstr = targetSizeLeft;
        }
        for(int n = 0; (n<endSize) && (targetSizeLeft>n); n++){
            string substringL = targetStr.substr(endSize, lenOfSubstr-n);
            //string substringS = targetStr.substr(endSize, n);
            int substringPos = endStr.find(substringL);
            //int substringHas = endStr.find(substringS);
            if ((substringPos != string::npos) && (substringL.length() > 1)){
                foundSubstring = substringL.length();
                break;
            }
        }
        // Clone or append
        if (!(foundSubstring<1) && ( (cloneCost/foundSubstring) < appendCost)){
            // Clone possible
            stringConstructData tmp;
            tmp.currCost = totalCost+cloneCost;
            tmp.currStrSize = endStr.length()+foundSubstring;
            clones.push_back(tmp);

            // endStr += foundSubstring;
            // totalCost += cloneCost;
        }
        

        endStr.push_back(targetStr[endSize]);
        totalCost += appendCost;

        // curr substr: orig size: 4, substrsize: 2,
        // new subst: orig size 5: substrsize: 4
        // endStr =
        // pointer to clone
        
        auto it = clones.begin();
        while (it != clones.end()){
            stringConstructData clone = *it;
            if (endSize+1 == clone.currStrSize){
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
}

// do not write or edit anything below this line

#endif
