#include "header.hpp"

class Solution
{
public:
/*
解析：典型的dfs回溯问题，在有限的搜索空间内找出符合条件的所有组合；
回溯问题需要单独的辅助函数，这里直观地命名为dfs，dfs函数需要传入状态state（即当前组成的字符串），以根据状态进行选择并进入新的递归调用
这里初始状态为0位置，即首次选择的索引位置，通过将数字字符-'0'映射到int值，
然后每次状态更新，pos位置+1，撤回选择即状态回退；
在状态的size和digits相等时符合题意存储结果并返回。
*/
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