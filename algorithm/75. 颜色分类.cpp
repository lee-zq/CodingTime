#include "header.hpp"

class Solution {
public:
/*
解析：只有三种元素，一种解法是统计后再直接按顺序赋值
第二种解法是用双指针，第一次遍历将所有0置换到最前面，第二次遍历将1置换到0后面，结束
*/
    void sortColors(vector<int>& nums) {
        int cnt[3]=  {0,0,0};
        for (size_t i = 0; i < nums.size(); i++)
        {
            cnt[nums[i]]++;
        }
        for (size_t i = 0; i < cnt[0]; i++)
        {
            nums[i] = 0;
        }
        for (size_t i = 0; i < cnt[1]; i++)
        {
            nums[i+cnt[0]] = 1;
        }
        for (size_t i = 0; i < cnt[2]; i++)
        {
            nums[i+cnt[0]+cnt[1]] = 2;
        }
    }

    void sortColors_V2(vector<int>& nums) {
        int p = 0;
        for (size_t i = 0; i < nums.size(); i++)
        {
            if(nums[i]==0){
                nums[i] = nums[p];
                nums[p] = 0;
                p++;
            }
        }
        for (size_t i = p; i < nums.size(); i++)
        {
            if(nums[i]==1){
                nums[i] = nums[p];
                nums[p] = 1;
                p++;
            }
        }
    }
};

// unittest
int main(){
    Solution s;
    vector<int> nums = {2,1,0,2,1,2,2,1,0};
    s.sortColors_V2(nums);
    for (size_t i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }
    return 0;
}