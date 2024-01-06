#include "header.hpp"

class Solution
{
public:
    /*
解析：这个二维数组的属性是每行升序，每列升序，但是不是any item of line[i+1] > any item of line[i]
所以不能暴力地通过比对每行的值先确定行位置再二分查找。
考虑到从右上角开始比对target，如果
target < nums[x][y] , 那么y--;
target > nums[x][y] , 那么x++;
直到target==nums[x][y]或者x y 越界
*/
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        int x = 0;
        int y = n - 1;
        while (x < m && y >= 0)
        {
            if (matrix[x][y] == target)
            {
                return true;
            }
            if (matrix[x][y] < target)
            {
                x++;
            }
            else
            {
                y--;
            }
        }
        return false;
    }
};