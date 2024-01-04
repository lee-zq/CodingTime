#include "header.hpp"

class Solution
{
public:
/*
解析：设置闭合上边界top，下边界down，左边界left，有边界right，
按照从左上到右上、从右上到右下、从右下到左下、从左下到左上的循环过程打印，同时在每个边打印后收缩
对应边界，直至top>down或left>right结束
*/
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