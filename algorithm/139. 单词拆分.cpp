#include "header.hpp"

class Solution
{
public:
/*
解析：dp问题。简历dp表表示s的前i个字符是否能被正确切分。
那么dp递推关系式为 dp[i] = 在s的字串s[0,i]内，存在dp[j]为true且在wordDict中能够查找到s[j,i].
是则跳出当前判断，并进入i+1位置的计算。
*/
    bool wordBreak(string s, vector<string>& wordDict)
    {
        std::unordered_set<string> word_set;
        for (auto& x : wordDict)
        {
            word_set.insert(x);
        }
        std::vector<bool> dp(s.size() + 1,false);
        dp[0] = true;
        for (size_t i = 1; i < s.size()+1; i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                if(dp[j] && word_set.find(s.substr(j,i-j))!=word_set.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};