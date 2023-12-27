#include "header.hpp"

class Solution
{
public:
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
    vector<int> dailyTemperatures2(vector<int>& temperatures)
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