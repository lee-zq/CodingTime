
// 基于上述函数实现一个耗时统计的class
#include <chrono>
#include <cstdio>
#include <iostream>
#include <unistd.h>

class Timer
{
public:
    Timer(std::string scope_tag="Default") : m_begin(std::chrono::high_resolution_clock::now()), m_scope_tag(scope_tag)
    {
    }

    ~Timer()
    {
        printf("[%s] Time elapsed: %.4f ms\n", m_scope_tag.c_str(), elapsed()/1000.f);
    }

    void reset()
    {
        m_begin = std::chrono::high_resolution_clock::now();
    }

    template <typename Duration = std::chrono::microseconds>
    int64_t elapsed() const
    {
        return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    int64_t elapsed_milli() const
    {
        return elapsed<std::chrono::milliseconds>();
    }

    int64_t elapsed_micro() const
    {
        return elapsed<std::chrono::microseconds>();
    }

    int64_t elapsed_nano() const
    {
        return elapsed<std::chrono::nanoseconds>();
    }

    int64_t elapsed_seconds() const
    {
        return elapsed<std::chrono::seconds>();
    }

    int64_t elapsed_minutes() const
    {
        return elapsed<std::chrono::minutes>();
    }


private:
    std::chrono::high_resolution_clock::time_point m_begin;
    std::string m_scope_tag;
};
