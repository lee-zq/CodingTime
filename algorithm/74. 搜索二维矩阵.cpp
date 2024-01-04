#include "header.hpp"

class Solution
{
public:
/*
解析：二维二分查找。先定位行，然后二分查找
*/
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int row = matrix.size();
        int col = matrix[0].size();
        for (size_t r = 0; r < row; r++)
        {
            vector<int>& line = matrix[r];
            if (line.front() <= target && line.back() >= target)
            {
                int left = 0;
                int right = line.size() - 1;
                while (left <= right)
                {
                    int mid = (left + right) / 2;
                    if (line[mid] == target)
                    {
                        return true;
                    }
                    else if (line[mid] > target)
                    {
                        right = mid - 1;
                    }
                    else if (line[mid] < target)
                    {
                        left = mid + 1;
                    }
                }
                break;
            }
        }
        return false;
    }
};

int main()
{
    return 0;
}