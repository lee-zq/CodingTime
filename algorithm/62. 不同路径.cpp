#include "header.hpp"

class Solution
{
public:
    /*
解析：简单dp问题。可以知道:dp[i,j] = dp[i-1][j] + dp[i][j-1]
而且第一行和第一列其实每个位置的走法都只有一种，所以先将dp表初始化为全1
然后在([1,1],[m-1,n-1])范围内用递推公式求解，最后[m-1,n-1]位置为答案。
*/
    int uniquePaths_v0(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (size_t i = 1; i < m; i++)
        {
            for (size_t j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
    int uniquePaths(int m, int n)
    {
        vector<int> dp_col(n, 1);
        for (size_t i = 1; i < m; i++)
        {
            for (size_t j = 1; j < n; j++)
            {
                dp_col[j] = dp_col[j] + dp_col[j - 1];
            }
        }
        return dp_col[n - 1];
    }
};

int main()
{
    Solution s;
    auto ret = s.uniquePaths(3, 7);
    printf("ret = %d\n", ret);
    return 0;
}