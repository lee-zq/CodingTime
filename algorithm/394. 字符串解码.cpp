#include "header.hpp"

class Solution
{
public:
    /*
解析：所给字符串中数字表示重复次数，括号表示要复制的内容，像这种需要左右匹配的一般用栈处理
构建两个栈，num_stack作为解析出的数字的容器，digit_stack作为解析出的字符串的容器，
在遍历整个输入字符串的过程中，遇到数字就存入num_stack（注意多位数字）
遇到"]"符号则开始弹出，弹出数字n，弹出字符组成字符串（遇到"["符号终止），并随后弹出"["符合,复制n份字符串后，按顺序再压入栈中，继续遍历
结束后将栈中字符组成字符串即是结果
*/
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