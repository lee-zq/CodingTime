#include "header.hpp"

class Solution
{
public:
    /*
题意：计算每天是几天后升温
解析：暴力遍历。对每天，从当前日期向后遍历，升温则记录并跳出，继续下一日期的计算
解法2用栈操作。构建结果数组等长于温度数组且初始化为0
遍历温度数组，当当前日期i(也即数组索引)对应的温度大于栈顶元素对应的温度，
那么结果数组的栈顶值索引位置的结果为i-top(),弹出栈顶元素
每次遍历都将当前数组索引压栈。遍历完。
*/
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        vector<int> ans(temperatures.size(), 0);
        for (size_t i = 0; i < temperatures.size() - 1; i++)
        {
            for (size_t j = i + 1; j < count; j++)
            {
                if (temperatures[j] > temperatures[i])
                {
                    ans[i] = j - i;
                    break;
                }
            }
        }
        return ans;
    }
    vector<int> dailyTemperatures_V2(vector<int>& temperatures)
    {
        std::stack<int> stack;
        std::vector<int> answer(temperatures.size(), 0);
        for (size_t i = 0; i < temperatures.size(); i++)
        {
            while (!stack.empty() && temperatures[stack.top()] < temperatures[i])
            {
                answer[stack.top()] = i - stack.top();
                stack.pop();
            }
            stack.push(i);
        }
        return answer;
    }
};