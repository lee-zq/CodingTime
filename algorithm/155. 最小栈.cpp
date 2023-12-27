#include "header.hpp"

class MinStack
{
public:
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