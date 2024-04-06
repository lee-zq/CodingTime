#include "header.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

std::vector<int> get_rand_vec(int len = 100, int seed = 0)
{
    srand(seed);
    std::vector<int> src(len);
    std::iota(src.begin(), src.end(), 0);
    std::random_shuffle(src.begin(), src.end(), [](int i) { return rand() % i; });
    return src;
}

void bubble_sort(std::vector<int>& src)
{
    for (int i = src.size() - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (src[j] > src[j + 1])
            {
                int tmp = src[j];
                src[j] = src[j + 1];
                src[j + 1] = tmp;
            }
        }
    }
}

void select_sort(std::vector<int>& src)
{
    for (int i = src.size() - 1; i >= 0; i--)
    {
        int max_idx = i;
        for (int j = 0; j < i; j++)
        {
            if (src[max_idx] < src[j])
            {
                max_idx = j;
            }
        }
        int tmp = src[i];
        src[i] = src[max_idx];
        src[max_idx] = tmp;
    }
}
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quickSort(std::vector<int>& nums, int start, int end)
{
    int left = start;
    int right = end;
    int key = nums[start];
    while (left < right)
    {
        while (left < right && nums[left] <= key)
        {
            left++;
        }
        while (left < right && nums[right] >= key)
        {
            right--;
        }
        swap(&nums[left], &nums[right]);
    }
    // left==right 终止
    swap(&nums[start], &nums[left]);
    // 递归
    quickSort(nums, start, left - 1);
    quickSort(nums, left, right);
}

int main()
{
    auto src = get_rand_vec(10);
    // select_sort(src);
    quickSort(src, 0, src.size() - 1);
    for (size_t i = 0; i < src.size(); i++)
    {
        std::cout << src[i] << ", ";
    }
    std::cout << std::endl;
}
