#include "header.cpp"

class Solution {
public:
    /*
解析：建立dp表，表示以每个元素为结尾的子序列的和，那么有状态转移方程：
dp[i] = max(dp[i-1]+nums[i], nums[i]) 得到下一个元素结尾的最大子序列和

ps:由于状态转移之和前一个状态相关，那么dp表可以压缩到O(1)空间;
*/
    int maxSubArray(vector<int>& nums) {
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size();i++){
            dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
        }
        int ret = *std::max_element(dp.begin(), dp.end());
        return ret;
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

