#include "header.hpp"

class Solution
{
public:
    void rotate(vector<int>& nums, int k)
    {
        if (nums.size()==0){
            return;
        }
        k = k % nums.size();
        std::vector<int> tmp(nums.end() - k, nums.end());
        for (int i = nums.size() - 1; i >= k; i--)
        {
            nums[i] = nums[i - k];
        }
        for (int i = 0; i < k;i++){
            nums[i] = tmp[i];
        }
    }
}
