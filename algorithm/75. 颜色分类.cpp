#include "header.hpp"

class Solution {
public:
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

    void sortColors(vector<int>& nums) {
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