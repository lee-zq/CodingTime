#include "header.hpp"

class Solution {
public:
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