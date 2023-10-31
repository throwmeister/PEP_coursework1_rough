#include <string>
using std::string;
#include <iostream>

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

int main(){
    string str1 = "ABCXYZAY";
    string str2 = "XYZABCB";
    int x = LCSubStr(str1, str2, str1.length(), str2.length());
    std::cout << x << " is length of substr";
}
