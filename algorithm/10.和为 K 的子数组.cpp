#include "header.hpp"

class Solution {
public:
/*
解析：双层遍历累计和为k的子数组，这里面存在诸多重复计算；
考虑将每个位置的前缀和算出来并存入map，弱国map中存在前缀和-k的元素，那么可以知道，这两个前缀和之间的差距子数组就是答案
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
            pre += nums[i];
            if (mp.find(pre-k)!=mp.end()){
                ret += mp[pre];
            }
            mp[pre] = 1;
        }
    }
};