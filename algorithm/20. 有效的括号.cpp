#include "header.hpp"

class Solution
{
public:
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
