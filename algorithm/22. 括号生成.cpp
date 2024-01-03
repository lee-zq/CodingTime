#include "header.hpp"

class Solution
{
public:
/*
解析，递归生成多有可能的长度为2n的括号字符串，在长度满足条件的前提下，判断合法性，然后存入结果数组
*/
    // 递归生成所有长度为2*n的括号字符串
    // 判断合法括号字符串的保存
    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        string cur_str;
        dfs_generate(cur_str, n * 2, res);
        return res;
    }

    void dfs_generate(string& cur_str, int len, vector<string>& res)
    {
        if (cur_str.size() == len)
        {
            if (isValid(cur_str))
            {
                res.push_back(cur_str);
            }
            return;
        }

        cur_str += ")";
        dfs_generate(cur_str, len, res);
        cur_str.pop_back();

        cur_str += "(";
        dfs_generate(cur_str, len, res);
        cur_str.pop_back();
    }

    // 判断一个括号是有效的
    bool isValid(string& s){
        int balance = 0;
        for (char x : s)
        {
            if (x=='('){
                balance++;
            }
            else if (x == ')')
            {
                balance--;
            }
            if (balance<0){
                return false;
            }
        }
        return balance == 0;
    }
};