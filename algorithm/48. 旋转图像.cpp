#include "header.hpp"

class Solution
{
public:
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