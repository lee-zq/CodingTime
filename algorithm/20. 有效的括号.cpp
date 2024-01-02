#include "header.hpp"

class Solution
{
public:
/*
解析：使用栈进行匹配，匹配则消除匹配对，直到遍历完，栈为空则括号有效
*/
    bool isValid(string s)
    {
        std::vector<char> stack;
        for (size_t i = 0; i < s.size(); i++)
        {
            char ch = s[i];
            if (stack.size() == 0)
            {
                stack.push_back(ch);
                continue;
            }
            char top = stack.back();
            if ((top == '(' && ch == ')') || (top == '[' && ch == ']') || (top == '{' && ch == '}'))
            {
                stack.pop_back();
            }else{
                stack.push_back(ch);
            }
        }
        return !stack.size();
    }
};
