#include "header.hpp"

class Solution
{
public:
/*
解析：先二分查找。锁定目标某一个位置，然后向左右遍历。直到遇到不一样的值或到达边界
*/
    vector<int> searchRange(vector<int>& nums, int target)
    {
        int pos = find_target(nums, target);
        if (pos==-1){
            return {-1, -1};
        }
        int left = pos;
        int right = pos;
        while (left>=0)
        {
            if (nums[left]==target)
            {
                left--;
            }else{
                break;
            }
        }
        left++;

        while (right <= nums.size()-1)
        {
            if (nums[right] == target)
            {
                right++;
            }
            else
            {
                break;
            }
        }
        right--;

        return {left, right};
    }

    int find_target(vector<int>& nums, int target)  // 二分查找
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return -1;
    }
};