#include "header.hpp"

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if(n<2){
            return s;
        }
        vector<vector<int>> dp(n, vector<int>(n, false));
        for (size_t i = 0; i < n; i++)
        {
            dp[i][i] = 1;
        }
        int max_length = 1;
        int begin = 0;
        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                // j-i+1 == L
                int j = L + i - 1;
                if (j>=n){
                    break;
                }
                if (s[i]!=s[j]){
                    dp[i][j] = 0;
                }else{
                    if(j-i<3){
                        dp[i][j] = 1;
                    }else{
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                if(dp[i][j]&&(j-i+1>max_length)){
                    max_length = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, max_length);
    }
};