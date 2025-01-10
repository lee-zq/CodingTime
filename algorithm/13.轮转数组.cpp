#include "header.hpp"

class Solution
{
public:
/*
解析：轮转数量k先进行k%n取模；然后前k个数据先保存，然后一次性赋值，最后将k个先保存的数据填入
*/
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
};

// unittest
int main()
{
    std::vector<int> x = {1, 2, 3, 4, 5, 6, 7};
    Solution s;
    s.rotate(x, 3);
    for (auto i : x)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
