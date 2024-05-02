#include "simd_header.h"

void add_two_vec_native(const std::vector<int>& vec1, const std::vector<int>& vec2, std::vector<int>& vec3)
{
    Timer t(__FUNCTION__);
    for (int i = 0; i < vec1.size(); i++)
    {
        vec3[i] = vec1[i] + vec2[i];
    }
}

void add_two_vec_simd(const std::vector<int>& vec1, const std::vector<int>& vec2, std::vector<int>& vec3)
{
    Timer t(__FUNCTION__);
    int i = 0;
    for (; i + 8 < vec1.size(); i += 8)
    {
        __m256i a = _mm256_loadu_si256((__m256i*)&vec1[i]);
        __m256i b = _mm256_loadu_si256((__m256i*)&vec2[i]);
        __m256i c = _mm256_add_epi32(a, b);
        _mm256_storeu_si256((__m256i*)&vec3[i], c);
    }
    for (; i < vec1.size(); i++)
    {
        vec3[i] = vec1[i] + vec2[i];
    }
}

void addindex_natie(double* x, int n)
{
    Timer t(__FUNCTION__);
    for (int i = 0; i < n; i++)
    {
        x[i] += i;
    }
}

void addindex_sse(double* x, int n)
{
    Timer t(__FUNCTION__);
    __m256d x_vec, init, incr, ind;
    ind = _mm256_set_pd(3, 2, 1, 0);
    incr = _mm256_set1_pd(4);
    for (int i = 0; i < n; i += 4)
    {
        x_vec = _mm256_loadu_pd(x + i);    // load 4 doubles
        x_vec = _mm256_add_pd(x_vec, ind); // add the two
        ind = _mm256_add_pd(ind, incr);    // update ind
        _mm256_storeu_pd(x + i, x_vec);    // store back
    }
}

void vec_add_test()
{
    auto vec1 = get_rand_vec(1, 1000000);
    auto vec2 = get_rand_vec(2, 1000000);
    std::vector<int> vec3(vec1.size());
    std::vector<int> vec4(vec1.size());
    add_two_vec_native(vec1, vec2, vec3);
    add_two_vec_simd(vec1, vec2, vec4);
    compare_vec(vec3, vec4);
}

void vec_add_idx_test()
{
    auto vec1 = get_rand_vec(1., 10000000);
    auto vec2 = vec1;
    addindex_natie(vec1.data(), vec1.size());
    addindex_sse(vec2.data(), vec2.size());
    compare_vec(vec1, vec2);
}

int main(int argc, char** argv)
{
    vec_add_idx_test();

    return 0;
}