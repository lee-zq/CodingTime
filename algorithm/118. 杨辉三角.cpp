#include "header.hpp"

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ans(numRows, vector<int>{});
        ans[0] =    {1};
        for (size_t i = 1; i < numRows; i++)
        {
            ans[i] = {1};
            for (size_t j = 0; j < ans[i - 1].size()-1; j++)
            {
                ans[i].push_back(ans[i - 1][j] + ans[i - 1][j + 1]);
            }
            ans[i].push_back(1);
        }
        return ans;
    }
};

int main(){
    Solution s;
    auto ret = s.generate(3);
    for (size_t i = 0; i < ret.size(); i++)
    {
        for (size_t j = 0; j < ret[i].size(); j++)
        {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }
}