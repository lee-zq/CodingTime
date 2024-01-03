#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>


int topk(std::vector<int>& src, int k, std::vector<int>& dst)
{
    if (k > src.size())
        return -1;
    dst = std::vector<int>(src.begin(), src.begin() + k);
    int min_idx = std::min_element(dst.begin(), dst.end()) - dst.begin();
    for (int i = k; i < src.size(); ++i)
    {
        int min = dst[min_idx];
        if (src[i] > min)
        {
            dst[min_idx] = src[i];
            min_idx = std::min_element(dst.begin(), dst.end()) - dst.begin();
        }
    }
    return 0;
}

int topk_heap(std::vector<int>& src, int k, std::vector<int>& dst)
{
    if (k > src.size())
        return -1;
    dst = std::vector<int>(src.begin(), src.begin() + k);
    std::make_heap(dst.begin(), dst.end(), std::greater<int>());
    for (int i = k; i < src.size();i++){
        int& top = dst[0];
        if (top < src[i]){
            std::pop_heap(dst.begin(), dst.end(), std::greater<int>());
            dst[dst.size() - 1] = src[i];
            std::push_heap(dst.begin(), dst.end(), std::greater<int>());
        }
    }
    return 0;
}


int main()
{
    int a = 11;
    std::vector<int> src(1000000);
    std::iota(src.begin(), src.end(), 0);
    std::random_shuffle(src.begin(), src.end(), [](int i) { return rand() % i; });
    std::vector<int> dst;
    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point beginTime1 = std::chrono::steady_clock::now();
    topk_heap(src, 1000, dst);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds timeInterval = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
    std::chrono::steady_clock::time_point endTime1 = std::chrono::steady_clock::now();
    std::cout << timeInterval.count() << "ms\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - beginTime1).count() << "ms\n";

    for (auto& i : dst)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}