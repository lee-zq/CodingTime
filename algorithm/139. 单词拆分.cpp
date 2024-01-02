#include "header.hpp"

class Solution
{
public:
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