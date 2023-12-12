#include "header.cpp"

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size();i++){
            dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
        }
        int ret = *std::max_element(dp.begin(), dp.end());
    }

    int maxSubArray(vector<int>& nums) {  // 状态压缩
        int max_value = nums[0];
        int pre_value = max_value;
        for (int i = 1; i < nums.size();i++){
            pre_value = std::max(pre_value + nums[i], nums[i]);
            if (pre_value>max_value){
                max_value = pre_value;
            }
        }
        return max_value;
    }
};

