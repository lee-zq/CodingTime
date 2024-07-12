#include "include/arm_neon.hpp"
#include "include/base_func.hpp"
#include <stdint.h>

// void convert_uint8_to_float(uint8_t* src, float* dest, int size)
// {
//     int i = 0;
//     uint8x8_t v_zero = vdup_n_u8(0);
//     float32x4_t v_scale = vdupq_n_f32(1.0f / 255.0f);

//     for (i = 0; i < size - 8; i += 8)
//     {
//         uint8x8_t v_src = vld1_u8(src + i);
//         uint8x8_t v_mask = vclt_u8(v_src, v_zero);                             // 负数掩码
//         int16x8_t v_int16 = vreinterpretq_s16_u16(vshll_n_u8(v_src, 8));       // 扩展为16位整数
//         float32x4_t v_low = vcvtq_f32_s32(vmovl_s16(vget_low_s16(v_int16)));   // 转换低32位
//         float32x4_t v_high = vcvtq_f32_s32(vmovl_s16(vget_high_s16(v_int16))); // 转换高32位

//         v_low = vmulq_f32(v_low, v_scale); // 归一化到0-1范围
//         v_high = vmulq_f32(v_high, v_scale);

//         vst1q_f32(dest + i, vcombine_f32(v_low, v_high)); // 存储结果
//     }

//     // 对剩余的少于8个元素进行处理
//     for (; i < size; i++)
//     {
//         dest[i] = src[i] / 255.0f;
//     }
// }

void uint16_to_float32_neon(uint16_t* src, float* dest, int size)
{
    int i = 0;
    uint16x8_t vec_src;
    float32x4_t vec_dest1, vec_dest2;
    float32x4_t zero = vdupq_n_f32(0);

    for (i = 0; i < size - 8; i += 8)
    {
        // Load 8 uint16 values
        vec_src = vld1q_u16(src + i);

        // Convert uint16 to float32
        vec_dest1 = vcvtq_f32_u32(vmovl_u16(vget_low_u16(vec_src)));
        vec_dest2 = vcvtq_f32_u32(vmovl_u16(vget_high_u16(vec_src)));

        // Store 8 float32 values
        vst1q_f32(dest + i, vec_dest1);
        vst1q_f32(dest + i + 4, vec_dest2);
    }

    // Handle the remaining elements (less than 8) with NEON
    for (; i < size; i++)
    {
        dest[i] = (float)src[i];
    }
}

void convert_uint8_to_int8(uint8_t* src, int8_t* dest, int size)
{
    int i = 0;
    for (i = 0; i < size - 8; i += 8)
    {
        uint8x8_t v_src = vld1_u8(src + i);
        int8x8_t v_dst = vreinterpret_u8_s8(v_src);

        vst1_s8(dest + i, v_dst); // 存储结果
    }
    for (; i < size; i++)
    {
        dest[i] = (int8_t)src[i];
    }
}

void convert_int8_to_uint8(int8_t* src, uint8_t* dest, int size)
{
    int i = 0;
    for (i = 0; i < size - 8; i += 8)
    {
        int8x8_t v_src = vld1_s8(src + i);
        uint8x8_t v_dst = vreinterpret_s8_u8(v_src);

        vst1_u8(dest + i, v_dst); // 存储结果
    }
    for (; i < size; i++)
    {
        dest[i] = (int8_t)src[i];
    }
}

int main()
{
    int len = 256;
    std::vector<int8_t> src(len, 0);
    std::vector<uint8_t> dst(len, 0);
    for (size_t i = 0; i < src.size(); i++)
    {
        src[i] = i-127;
    }
    convert_int8_to_uint8(src.data(), dst.data(), len);
    for (size_t i = 0; i < src.size(); i++)
    {
        printf("src: %d, dst:%d\n", src[i], dst[i]);
    }

    return 0;
}
