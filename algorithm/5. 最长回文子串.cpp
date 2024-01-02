#include "header.hpp"


class Solution {
public:
/*
解析：动态规划。构建一个nxn的dp表二维数组,dp[i][j]表示i->j的子数组是否可以构成回文串，
dp表初始化，单个字符肯定是回文串，所以将dp中对角线上的元素都置为1，其他位置初始化为0；
dp表递推，以子串长度为axis进行遍历，这样就可以从已初始化的位置向外扩展：
正常情况：dp[i][j] = s[i]==s[j] && dp[i+1][j-1]==1
边界条件：0<=i<=j<n
*/
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