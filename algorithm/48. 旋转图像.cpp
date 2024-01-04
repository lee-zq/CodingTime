#include "header.hpp"

class Solution
{
public:
/*
解析：旋转前后的索引位置对应关系：[i,j] <=> [j, n-1-i]
*/
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        auto tmp = matrix;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                matrix[j][n - 1 - i] = tmp[i][j];
            }
        }
    }
};