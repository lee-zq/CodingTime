#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <random>
#include <chrono>

// timer
#include "../../base_func/timer.hpp"

template <typename T>
std::vector<T> get_rand_vec(T base, int len = 100, int seed = 0)
{
    srand(seed);
    std::vector<T> src(len);
    std::iota(src.begin(), src.end(), base);
    std::random_shuffle(src.begin(), src.end(), [](int i) { return rand() % i; });
    return src;
}

template <typename T>
std::vector<T> get_rand_range_vec(T min_val, T max_val, int len = 100, int seed = 0)
{
    srand(seed);
    std::vector<T> src(len);
    for (int i = 0; i < len; i++)
    {
        src[i] = min_val + (max_val - min_val) * rand() / RAND_MAX;
    }
    return src;
}

template <typename T>
void compare_vec(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    for (int i = 0; i < vec1.size(); i++)
    {
        if (vec1[i] != vec2[i])
        {
            std::cout << "Error: " << i << std::endl;
            break;
        }
    }
}