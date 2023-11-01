#include <string>
using std::string;
#include <iostream>
#include <vector>

int LCSubStr(string str1, string str2, int N, int M)
{
    int LCSuff[N + 1][M + 1];
    int mx = 0;    
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= M; j++)
        {
              if (i == 0 || j == 0){
                LCSuff[i][j] = 0;
              }
 
            else if (str1[i - 1] == str2[j - 1]) {
                LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                mx = std::max(mx, LCSuff[i][j]);
            }
            else
                LCSuff[i][j] = 0;
        }
    }
    return mx;
}

int LCSubStr2(const string &str1, const string &str2){
    int mx = 0;
    int prev = 0;

    auto it = str1.begin();

    while(it != str1.end()){
        char d = str2[prev];
        char c = *it;
        if(c==d){
            prev += 1;
        } else{
            mx = std::max(mx, prev);
            if (prev > 0){
                prev = 0;
                continue;
            }
            prev = 0;
        }
        it++;
    }
    mx = std::max(mx, prev);
    return mx;
}

int main(){
    /*
    string str1 = "afwced";
    string str2 = "dwach";
    int x = LCSubStr(str1, str2, str1.length(), str2.length());
    int y = LCSubStr2(str1, str2);
    std::cout << x << " is length of substr";
    std::cout << y << " is length of substr";
    */

    string test1 = "abcblgmbcntdblgblgmbaipmbcntdblg";
    string test2 = "blgmbaipfdmbcntdblgblgmbaipmbcntdblgblgmbaipcbcntdblgblgmbaipobacjodblgblgmbaiabcblgmbcntdblgblgmbaipmbcntdblgblgmbaipfdmb";
    int g = LCSubStr2(test1, test2);
    int t = 8;
}
