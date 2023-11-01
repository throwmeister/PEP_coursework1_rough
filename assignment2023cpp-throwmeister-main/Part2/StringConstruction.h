#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
#include <algorithm>
// TODO: your code goes here:

struct stringConstructData
{
    int currStrSize;
    int currCost;
};

int biggestSubstrLen(const string &str1, const string &str2){
    int mx = 0;
    int prev = 0;

    auto it = str1.begin();
    char start = str2[0];

    for(char c: str1){
        char d = str2[prev];
        if(c==d){
            prev++;
        } else{
            mx = std::max(mx, prev);
            if(prev>0){
                prev = 0;
                if(c==start){
                    prev++;
                }
            }
        }
    }
    mx = std::max(mx, prev);
    return mx;
}

int stringConstruction(const string &targetStr, const int cloneCost, const int appendCost){
    string endStr = "";
    int totalCost = 0;
    int const targetSize = targetStr.size();
    
    vector<stringConstructData> clones;
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

        string substringL = targetStr.substr(endSize, lenOfSubstr);
        int len = biggestSubstrLen(endStr, substringL);
        /*
        for(int n = 0; (n<endSize) && (targetSizeLeft>n); n++){
            string substringL = targetStr.substr(endSize, lenOfSubstr-n);
            int substringPos = endStr.find(substringL);
            if ((substringPos != string::npos)){
                foundSubstring = substringL.length();
                break;
            }
        }

        if (foundSubstring!= len){
            std::cout<< "lengths were not the same on iteration:" << endSize << "\n";
        }
        */
        // Clone or append
        if (!(len<2) && ( (cloneCost/len) < appendCost)){
            // Clone possible
            stringConstructData tmp;
            tmp.currCost = totalCost+cloneCost;
            tmp.currStrSize = endStr.length()+len;
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
