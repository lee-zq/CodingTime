#include "header.hpp"

class Solution {
public:
/*
解析：双层遍历累计和为k的子数组，这里面存在诸多重复计算；
考虑将每个位置的前缀和算出来并存入map，如果map中存在前缀和-k的元素，那么可以知道，这两个前缀和之间的差距子数组就是答案
累计得到答案
*/
    int subarraySum(vector<int>& nums, int k) {
        int ret = 0;
        for (int i = 0; i < nums.size();i++){
            int sum = 0;
            for (int j = i; j < nums.size(); j++)
            {
                sum += nums[j];
                if (sum==k)
                {
                    ret++;
                }
            }
        }
        return ret;
    }

    int subarraySum(vector<int>& nums, int k){
        std::map<int, int> mp;
        int pre = 0;
        mp[0] = 1;
        int ret = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            pre += nums[i]; // 0. 计算当前前缀和
            mp[pre] = 1; // 1. 将当前前缀和存入map
            if (mp.find(pre-k)!=mp.end()){  // 2. 查找是否有当前前缀和-k的值在map中，存在则累积这个值。
                ret += mp[pre];
            }
        }
    }
};