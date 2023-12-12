#include "header.hpp"

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> result;
        int left = 0;
        int top = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;

        while (true)
        {
            for (int i = left; i <= right; i++)
            {
                result.push_back(matrix[top][i]);
            }
            if (++top > down)
                break;
            for (int i = top; i <= down; i++)
            {
                result.push_back(matrix[i][right]);
            }
            if (--right < left)
                break;
            for (int i = right; i >= left; i--)
            {
                result.push_back(matrix[down][i]);
            }
            if (--down < top)
                break;
            for (int i = down; i >= top; i--)
            {
                result.push_back(matrix[i][left]);
            }
            if (++left > right)
                break;
        }
        return result;
    }
};