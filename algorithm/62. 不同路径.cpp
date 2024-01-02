#include "header.hpp"

class Solution {
public:
    int uniquePaths_v0(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n,1));
        for (size_t i = 1; i < m; i++)
        {
            for (size_t j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m-1][n-1];
    }
    int uniquePaths(int m, int n) {
        vector<int> dp_col(n,1);
        for (size_t i = 1; i < m; i++)
        {
            for (size_t j = 1; j < n; j++)
            {
                dp_col[j] = dp_col[j] + dp_col[j - 1];
            }
        }
        return dp_col[n];
    }
};

int main(){
    Solution s;
    s.uniquePaths(3, 7);
    return 0;
}