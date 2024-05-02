#include "simd_header.h"

inline float fast_tanh(float x)
{
    float x2 = x * x;
    float a = x * (135135.0f + x2 * (17325.0f + x2 * (378.0f + x2)));
    float b = 135135.0f + x2 * (62370.0f + x2 * (3150.0f + x2 * 28.0f));
    return a / b;
}

void Native_Gelu(float* dst, const float* src, size_t size)
{
    Timer t(__FUNCTION__);
    for (int i = 0; i < size; i++)
    {
        // dst[i] = 0.5f * src[i] * (1.0f + fast_tanh(0.79788458f * (src[i] + 0.044715f * src[i] * src[i] * src[i])));
        dst[i] = fast_tanh(src[i]);
    }
}

void _AVX_Gelu(float* dst, const float* src, size_t size)
{
    Timer t(__FUNCTION__);
    auto var1 = _mm256_set1_ps(0.044715f);
    auto var2 = _mm256_set1_ps(0.79788458f);
    auto var3 = _mm256_set1_ps(378.f);
    auto var4 = _mm256_set1_ps(17325.f);
    auto var5 = _mm256_set1_ps(135135.f);
    auto var6 = _mm256_set1_ps(28.f);
    auto var7 = _mm256_set1_ps(3150.f);
    auto var8 = _mm256_set1_ps(62370.f);
    auto var9 = _mm256_set1_ps(135135.f);
    auto var10 = _mm256_set1_ps(0.5);
    auto varOne = _mm256_set1_ps(1.f);
    auto varNegOne = _mm256_set1_ps(-1.f);

    for (int i = 0; i < size / 8; i++)
    {
        // 计算 x^3
        auto x = _mm256_loadu_ps(src + i * 8);
        auto y = _mm256_mul_ps(x, x);
        y = _mm256_mul_ps(y, x);
        // 计算 0.044715 * x^3
        y = _mm256_mul_ps(y, var1);
        // 计算 0.044715 * x^3 + x
        y = _mm256_add_ps(y, x);
        // 计算 sqrt(2 / PI) * (0.044715 * x^3 + x)
        y = _mm256_mul_ps(y, var2);

        // y = tanh(y)
        {
            auto y2 = _mm256_mul_ps(y, y);
            auto w = _mm256_add_ps(y2, var3);
            w = _mm256_mul_ps(w, y2);
            w = _mm256_add_ps(w, var4);
            w = _mm256_mul_ps(w, y2);
            w = _mm256_add_ps(w, var5);
            w = _mm256_mul_ps(w, y);
            auto z = _mm256_mul_ps(y2, var6);
            z = _mm256_add_ps(z, var7);
            z = _mm256_mul_ps(z, y2);
            z = _mm256_add_ps(z, var8);
            z = _mm256_mul_ps(z, y2);
            z = _mm256_add_ps(z, var9);
            z = _mm256_div_ps(w, z);
            z = _mm256_max_ps(z, varNegOne);
            y = _mm256_min_ps(z, varOne);
        }

        y = _mm256_add_ps(y, varOne);
        y = _mm256_mul_ps(y, x);
        y = _mm256_mul_ps(y, var10);
        _mm256_storeu_ps(dst + i * 8, y);
    }
}

void test_gelu()
{
    auto vec1 = get_rand_range_vec<float>(-10.1f, 100.f, 1000000);
    std::vector<float> vec2(vec1.size());
    std::vector<float> vec3(vec1.size());
    Native_Gelu(vec2.data(), vec1.data(), vec1.size());
    _AVX_Gelu(vec3.data(), vec1.data(), vec1.size());
    compare_vec(vec2, vec3);
}

int main(int argc, char** argv)
{
    test_gelu();
    return 0;
}