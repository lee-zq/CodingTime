#include "header.hpp"

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.size() == 0)
        {
            return result;
        }
        dfs(0, digits);
        return result;
    }

    void dfs(int pos, string& digits)
    {
        if (pos == digits.size())
        {
            result.push_back(res);
            return;
        }
        int num = digits[pos] - '0';
        for (int i = 0; i < m[num].size(); i++)
        {
            res.push_back(m[num][i]);
            dfs(pos + 1, digits);
            res.pop_back();
        }
    }

private:
    string res;
    vector<string> m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result;
};