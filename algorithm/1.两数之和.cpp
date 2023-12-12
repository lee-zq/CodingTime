#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>

std::vector<int> get_rand_vec(int len=100, int seed = 0){
    srand(seed);
    std::vector<int> src(len);
    std::iota(src.begin(), src.end(), 0);
    std::random_shuffle(src.begin(), src.end(), [](int i){return rand() % i;});
    return src;
}

class Solution {
public:
    std::vector<int> twoSum_v0(std::vector<int>& nums, int target) {
        for (int i = 0; i < nums.size();i++){
            for (int j = i + 1; j < nums.size();j++){
                if (nums[i]+nums[j]==target){
                    return {i, j};
                }
            }
        }
            return std::vector<int>();
    }   
    
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::map<int, int> m;
        for (int i = 0; i < nums.size();i++){
            if (m.find(target-nums[i])!=m.end()){
                return {m[target - nums[i]], i};
            }else{
                m[nums[i]] = i;
            }
        }
        return std::vector<int>();
    }   
};

int main(){
    std::vector<int> src = get_rand_vec(10000);
    auto beginTime = std::chrono::high_resolution_clock::now();
    Solution s;
    std::vector<int> dst = s.twoSum(src, 10);
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count() << "ms\n";

    for (auto& i : dst)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}