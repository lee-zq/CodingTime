#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> get_rand_vec(int len=100, int seed = 0){
    srand(seed);
    std::vector<int> src(len);
    std::iota(src.begin(), src.end(), 0);
    std::random_shuffle(src.begin(), src.end(), [](int i){return rand() % i;});
    return src;
}