#include "header.hpp"

class Solution
{
public:
    /*
解析：解法和二分查找类似，只是在更新搜索区域的时候需要判断target在旋转排序数组的左侧区域还是右侧区域
通过将nums[mid]和nums[0]比较，可以判断mid在哪个范围内，然后在各自范围内进行搜索区域更新。
*/
    int search(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left<=right) 
        {
            int mid = (left + right) / 2;
            if (nums[mid]==target){
                return mid;
            }
            if (nums[0] <= nums[mid])
            {
                if (nums[0] <= target && target < nums[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            else
            {
                if (nums[mid] < target && target <= nums[nums.size()-1])
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};