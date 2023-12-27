#include "header.hpp"

class Solution
{
public:
    string decodeString(string origin_s)
    {
        std::vector<int> num_stack;
        std::vector<char> digit_stack;
        for (int i = 0; i < origin_s.size();)
        {
            string num_str;
            while (origin_s[i] >= '0' && origin_s[i] <= '9')
            {
                num_str += origin_s[i];
                i++;
            }
            if (num_str != "")
            {
                int num = std::atoi(num_str.c_str());
                num_stack.push_back(num);
                continue;
            }
            if (origin_s[i] == ']')
            {
                int num = num_stack.back();
                num_stack.pop_back();
                string s;
                while (digit_stack.back() != '[')
                {
                    s = digit_stack.back() + s;
                    digit_stack.pop_back();
                }
                digit_stack.pop_back();
                string sum_s;
                for (size_t i = 0; i < num; i++)
                {
                    sum_s += s;
                }
                for (size_t i = 0; i < sum_s.size(); i++)
                {
                    digit_stack.push_back(sum_s[i]);
                }
                i++;
            }
            else
            {
                digit_stack.push_back(origin_s[i]);
                i++;
            }
        }
        string ret;
        for (size_t i = 0; i < digit_stack.size(); i++)
        {
            ret += digit_stack[i];
        }
        return ret;
    }
};

int main()
{
    Solution s;
    string a = "10[a2[b]]";
    auto res = s.decodeString(a);
    printf("%s\n", res.c_str());
    return 0;
}