#include "header.hpp"

class Solution {
public:
/*
解析：类似于求路径和的问题，典型dp二维最优路径问题。
可以归纳出递推公式：dp[i,j] = min(dp[i-1,j],dp[i,j-1]) + grid[i,j]
dp表第一行和第一列可以方便求出，每个位置的最小路径是前一个最小路径+当前位置的值
然后在([1,1],[m-1,n-1])范围内递推求出所有结果，最后[m-1,n-1]位置的值即为最小路径和
*/
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
        int base;
        for (size_t i = 0; i < dp.size(); i++)
        {
            for (size_t j = 0; j < dp[0].size(); j++)
            {
                if (i==0&&j==0){
                    base = grid[i][j];
                    continue;
                }else if(i==0&&j!=0){
                    base = dp[i][j - 1];
                }
                else if (i!=0&&j==0)
                {
                    base = dp[i-1][j];
                }else
                {
                    base = std::min(dp[i - 1][j], dp[i][j - 1]);
                }
                dp[i][j] = base + grid[i][j];
            }
        }
        return dp.back().back();
    }
    int minPathSum(vector<vector<int>>& grid) {
        vector<int>> dp_col(grid[0].size(), 0);
        vector<int>> dp_row(grid.size(), 0);
        dp_col[0] = grid[0][0];
        for (size_t i = 1; i < dp_col.size(); i++)
        {
            dp_col[i] = dp_col[i - 1] + gird[0][i];
        }

        for (size_t i = 1; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[0].size(); j++)
            {
                if(j==0){
                    dp[j] = dp[j] + gird[i][0];
                }else{
                    dp[j] = std::min(dp[j-1], dp[j]) + grid[i][j];
                }
            }
        }
        return dp.back();
    }
};

int main(){

}