#include "header.hpp"

class MinStack
{
public:
/*
解析：这个问题考察了如何定义一个类的能力。
最小栈问题是希望能在常数时间内找到栈中最小值的一个栈实现。

直接用一个vector实现一个栈是容易的，封装top、push、pop等方法即可。
但要在操作过程中同步栈中最小值可以将每个元素绑定一个最小值存入栈中，
在push时，对比当前值和栈顶元素绑定的最小值，从而决定是否更新最小值，其他接口没什么变化。
*/
    MinStack()
    {
        data_.clear();
    }

    void push(int val)
    {
        if (data_.size() == 0)
        {
            data_.push_back(std::pair<int, int>(val, val));
        }
        else
        {
            int min_val = data_.back().second;
            data_.push_back(std::pair<int, int>(val, std::min(min_val, val)));
        }
    }

    void pop()
    {
        data_.pop_back();
    }

    int top()
    {
        return data_.back().first;
    }

    int getMin()
    {
        return data_.back().second;
    }

private:
    std::vector<std::pair<int, int>> data_;
};

int main()
{
    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    obj->pop();
    int param_3 = obj->top();
    int param_4 = obj->getMin();
}