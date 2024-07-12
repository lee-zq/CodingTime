#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "../base_func/timer.hpp"
#include "cvMat.hpp"
#include "include/arm_neon.hpp"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

// 函数实现图像resize操作
void native_resize(const cvMat& src, cvMat& dst, int width, int height)
{
    Timer t;
    assert(src.rows > 0 && src.cols > 0 && src.channels > 0);
    assert(width > 0 && height > 0);
    dst = cvMat(height, width, src.channels);
    float scale_x = static_cast<float>(src.cols) / width;
    float scale_y = static_cast<float>(src.rows) / height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < src.channels; k++)
            {
                float x = (j + 0.5) * scale_x - 0.5;
                float y = (i + 0.5) * scale_y - 0.5;
                int x0 = static_cast<int>(x);
                int y0 = static_cast<int>(y);
                int x1 = std::min(x0 + 1, src.cols - 1);
                int y1 = std::min(y0 + 1, src.rows - 1);
                float dx = x - x0;
                float dy = y - y0;
                float v0 = (1 - dx) * src.getPixel(y0, x0, k) + dx * src.getPixel(y0, x1, k);
                float v1 = (1 - dx) * src.getPixel(y1, x0, k) + dx * src.getPixel(y1, x1, k);
                float v = (1 - dy) * v0 + dy * v1;
                dst.setPixel(i, j, k, static_cast<uint8_t>(v));
            }
        }
    }
}

void native_resize_half_and_normalize(std::vector<uint8_t>& src_data,
                                      int src_h,
                                      int src_w,
                                      int src_c,
                                      std::vector<float>& dst_data,
                                      float* mean,
                                      float* std)
{
    cvMat src(src_h, src_w, src_c);
    src.data = src_data;
    cvMat dst;
    native_resize(src, dst, src_w / 2, src_h / 2);
    int dst_height = src_h / 2;
    int dst_width = src_w / 2;
    int dst_channel = src_c;
    dst_data.resize(dst_height * dst_width * dst_channel);
    float* dst_b_ptr = (float*)dst_data.data();
    float* dst_g_ptr = dst_b_ptr + dst_height * dst_width;
    float* dst_r_ptr = dst_g_ptr + dst_height * dst_width;

    for (size_t i = 0; i < dst.rows; i++)
    {
        for (size_t j = 0; j < dst.cols; j++)
        {
            uint8_t* src_ptr = dst.data.data() + (i * dst.cols + j) * dst.channels;
            dst_b_ptr[i * dst.cols + j] = (((float)src_ptr[0] - *mean) / *std);
            dst_g_ptr[i * dst.cols + j] = (((float)src_ptr[1] - *mean) / *std);
            dst_r_ptr[i * dst.cols + j] = (((float)src_ptr[2] - *mean) / *std);
        }
    }
}

// // 函数实现图像resize+normalize操作
// void native_resize_half_and_normalize(std::vector<uint8_t>& src_data,
//                                       int src_h,
//                                       int src_w,
//                                       int src_c,
//                                       std::vector<float>& dst_data,
//                                       float* mean,
//                                       float* std)
// {
//     Timer t;
//     assert(src_h > 0 && src_w > 0 && src_c == 3);
//     uint8_t* src_data_ptr = (uint8_t*)src_data.data();
//     int dst_height = src_h / 2;
//     int dst_width = src_w / 2;
//     int dst_channel = src_c;
//     dst_data.resize(dst_height * dst_width * dst_channel);
//     float* dst_b_ptr = (float*)dst_data.data();
//     float* dst_g_ptr = dst_b_ptr + dst_height * dst_width;
//     float* dst_r_ptr = dst_g_ptr + dst_height * dst_width;

//     for (int i = 0; i < dst_height; i++)
//     {
//         for (int j = 0; j < dst_width; j++)
//         {
//             int x0 = 2 * i;
//             int y0 = 2 * j;
//             int x1 = x0 + 1;
//             int y1 = y0 + 1;

//             float b = src_data[(y0 * src_w + x0) * src_c] + src_data[(y0 * src_w + x1) * src_c] +
//                       src_data[(y1 * src_w + x0) * src_c] + src_data[(y1 * src_w + x1) * src_c];
//             b = (b / 4 - *mean) / *std;
//             dst_b_ptr[i * dst_width + j] = b;

//             float g = src_data[(y0 * src_w + x0) * src_c + 1] + src_data[(y0 * src_w + x1) * src_c + 1] +
//                       src_data[(y1 * src_w + x0) * src_c + 1] + src_data[(y1 * src_w + x1) * src_c + 1];
//             g = (g / 4 - *mean) / *std;
//             dst_g_ptr[i * dst_width + j] = g;

//             float r = src_data[(y0 * src_w + x0) * src_c + 2] + src_data[(y0 * src_w + x1) * src_c + 2] +
//                       src_data[(y1 * src_w + x0) * src_c + 2] + src_data[(y1 * src_w + x1) * src_c + 2];
//             r = (r / 4 - *mean) / *std;
//             dst_r_ptr[i * dst_width + j] = r;
//         }
//     }
// }

void half_resize(const cvMat& src, cvMat& dst)
{
    Timer t;
    assert(src.rows > 0 && src.cols > 0 && src.channels > 0);
    uint8_t* src_data_ptr = (uint8_t*)src.data.data();
    int dst_height = src.rows / 2;
    int dst_width = src.cols / 2;
    int dst_channel = src.channels;
    dst = cvMat(dst_height, dst_width, dst_channel);
    uint8_t* dst_data_ptr = (uint8_t*)dst.data.data();

    int dst_width_aligned = dst_width & (-8);
    int dst_width_remained = dst_width & (7);

    uint8x16x3_t v8_src0;
    uint8x16x3_t v8_src1;
    uint8x8x3_t v8_dst;
    for (int row = 0; row < dst_height; row++)
    {
        int col = 0;
        // simd process
        uint8_t* src_ptr0 = src_data_ptr + (row * 2) * src.cols * src.channels;
        uint8_t* src_ptr1 = src_data_ptr + (row * 2 + 1) * src.cols * src.channels;
        uint8_t* dst_ptr = dst_data_ptr + row * dst_width * dst.channels;
        for (; col < dst_width_aligned; col += 8)
        {
            v8_src0 = vld3q_u8(src_ptr0);
            src_ptr0 += 48;
            v8_src1 = vld3q_u8(src_ptr1);
            src_ptr1 += 48;
            uint16x8_t v16_b_sum0 = vpaddlq_u8(v8_src0.val[0]);
            uint16x8_t v16_g_sum0 = vpaddlq_u8(v8_src0.val[1]);
            uint16x8_t v16_r_sum0 = vpaddlq_u8(v8_src0.val[2]);
            uint16x8_t v16_b_sum1 = vpaddlq_u8(v8_src1.val[0]);
            uint16x8_t v16_g_sum1 = vpaddlq_u8(v8_src1.val[1]);
            uint16x8_t v16_r_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v8_dst.val[0] = vshrn_n_u16(vaddq_u16(v16_b_sum0, v16_b_sum1), 2);
            v8_dst.val[1] = vshrn_n_u16(vaddq_u16(v16_g_sum0, v16_g_sum1), 2);
            v8_dst.val[2] = vshrn_n_u16(vaddq_u16(v16_r_sum0, v16_r_sum1), 2);
            vst3_u8(dst_ptr, v8_dst);
            // for (size_t x = 0; x < 8; x++)
            // {
            //     printf("(%d,%d,%d)[%d %d] ", dst_ptr[3 * x], dst_ptr[3 * x + 1], dst_ptr[3 * x + 3], row, col + x);
            // }
            // std::cout << std::endl;
            dst_ptr += 24;
        }

        // leftover process | 3 channels
        col = dst_width - 8;
        src_ptr0 = src_data_ptr + ((row * 2) * src.cols + col * 2) * src.channels;
        src_ptr1 = src_data_ptr + ((row * 2 + 1) * src.cols + col * 2) * src.channels;
        dst_ptr = dst_data_ptr + (row * dst_width + col) * dst.channels;
        v8_src0 = vld3q_u8(src_ptr0);
        v8_src1 = vld3q_u8(src_ptr1);
        uint16x8_t v16_b_sum0 = vpaddlq_u8(v8_src0.val[0]);
        uint16x8_t v16_g_sum0 = vpaddlq_u8(v8_src0.val[1]);
        uint16x8_t v16_r_sum0 = vpaddlq_u8(v8_src0.val[2]);
        uint16x8_t v16_b_sum1 = vpaddlq_u8(v8_src1.val[0]);
        uint16x8_t v16_g_sum1 = vpaddlq_u8(v8_src1.val[1]);
        uint16x8_t v16_r_sum1 = vpaddlq_u8(v8_src1.val[2]);
        v8_dst.val[0] = vshrn_n_u16(vaddq_u16(v16_b_sum0, v16_b_sum1), 2);
        v8_dst.val[1] = vshrn_n_u16(vaddq_u16(v16_g_sum0, v16_g_sum1), 2);
        v8_dst.val[2] = vshrn_n_u16(vaddq_u16(v16_r_sum0, v16_r_sum1), 2);
        vst3_u8(dst_ptr, v8_dst);
        // uint8_t* src_ptr0 = src_data_ptr + (row * 2) * src.cols * src.channels;
        // uint8_t* src_ptr1 = src_data_ptr + (row * 2 + 1) * src.cols * src.channels;
        // uint8_t* dst_ptr = dst_data_ptr + row * dst_width * dst.channels;
        // for (; col < dst_width; col++)
        // {
        //     int base_b = col * 3;
        //     int base_g = col * 3 + 1;
        //     int base_r = col * 3 + 2;
        //     dst_ptr[col*3] = (src_ptr0[base_b] + src_ptr0[base_b + 3] + src_ptr1[base_b] + src_ptr1[base_b + 3]) / 4;
        //     dst_ptr[col*3 + 1] = (src_ptr0[base_g] + src_ptr0[base_g + 3] + src_ptr1[base_g] + src_ptr1[base_g + 3]) / 4;
        //     dst_ptr[col*3 + 2] = (src_ptr0[base_r] + src_ptr0[base_r + 3] + src_ptr1[base_r] + src_ptr1[base_r + 3]) / 4;
        // }
    }
}


void half_resize_and_normalize(std::vector<uint8_t>& src_data,
                               int src_h,
                               int src_w,
                               int src_c,
                               std::vector<float>& dst_data,
                               float* mean,
                               float* std)
{
    assert(src_h > 0 && src_w > 0 && src_c == 3);
    uint8_t* src_data_ptr = (uint8_t*)src_data.data();
    int dst_height = src_h / 2;
    int dst_width = src_w / 2;
    int dst_channel = src_c;
    dst_data.resize(dst_height * dst_width * dst_channel);
    float* dst_data_ptr = (float*)dst_data.data();
    int dst_width_aligned = dst_width & (-8);
    int dst_width_remained = dst_width & (7);

    float32x4_t v_mean = vdupq_n_f32(-*(mean));
    float32x4_t v_scale = vdupq_n_f32(1.0f / *std);
    uint8x16x3_t v8_src0;
    uint8x16x3_t v8_src1;
    uint16x8_t v16_sum0;
    uint16x8_t v16_sum1;
    float32x4_t vfp32_low;
    float32x4_t vfp32_high;
    for (int row = 0; row < dst_height; row++)
    {
        int col = 0;
        // simd process
        uint8_t* src_ptr0 = src_data_ptr + (row * 2) * src_w * src_c;
        uint8_t* src_ptr1 = src_data_ptr + (row * 2 + 1) * src_w * src_c;
        float* dst_b_ptr = dst_data_ptr + (row * dst_width);
        float* dst_g_ptr = dst_b_ptr + dst_width * dst_height;
        float* dst_r_ptr = dst_g_ptr + dst_width * dst_height;
        for (; col < dst_width_aligned; col += 8)
        {
            v8_src0 = vld3q_u8(src_ptr0);
            src_ptr0 += 48;
            v8_src1 = vld3q_u8(src_ptr1);
            src_ptr1 += 48;
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_b_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_g_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_r_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));

            // vst1q_f32(dst_g_ptr, vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0.val[1]))));
            // vst1q_f32(dst_g_ptr + 4, vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0.val[1]))));
            // vst1q_f32(dst_r_ptr, vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0.val[2]))));
            // vst1q_f32(dst_r_ptr + 4, vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0.val[2]))));
            // for (size_t x = 0; x < 8; x++)
            // {
            //     printf("(%.2f,%.2f,%.2f)[%d %d] ", dst_b_ptr[x], dst_g_ptr[x], dst_r_ptr[x], row, col + x);
            // }
            // std::cout << std::endl;
            dst_b_ptr += 8;
            dst_g_ptr += 8;
            dst_r_ptr += 8;
        }

        // // leftover process | 3 channels
        if (dst_width_remained > 0)
        {
            col = dst_width - 8;
            src_ptr0 = src_data_ptr + ((row * 2) * src_w + col * 2) * src_c;
            src_ptr1 = src_data_ptr + ((row * 2 + 1) * src_w + col * 2) * src_c;
            dst_b_ptr = dst_data_ptr + (row * dst_width + col);
            dst_g_ptr = dst_b_ptr + dst_width * dst_height;
            dst_r_ptr = dst_g_ptr + dst_width * dst_height;
            v8_src0 = vld3q_u8(src_ptr0);
            v8_src1 = vld3q_u8(src_ptr1);
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_b_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_g_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_r_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
        }
    }
}

void half_resize_and_normalize_v2(uint8_t* src_data_ptr,
                                  int src_h,
                                  int src_w,
                                  int src_c,
                                  std::vector<float>& dst_data,
                                  float* mean,
                                  float* std)
{
    int dst_height = src_h >> 1;
    int dst_width = src_w >> 1;
    int dst_channel = src_c;
    dst_data.resize(dst_height * dst_width * dst_channel);
    float* dst_data_ptr = (float*)dst_data.data();
    int dst_width_aligned = dst_width & (-8);
    int dst_width_remained = dst_width & (7);

    float32x4_t v_mean = vdupq_n_f32(-*(mean) / *std);
    float32x4_t v_scale = vdupq_n_f32(1.0f / *std);
    uint8x16x3_t v8_src0;
    uint8x16x3_t v8_src1;
    uint16x8_t v16_sum0;
    uint16x8_t v16_sum1;
    float32x4_t vfp32_low;
    float32x4_t vfp32_high;
    for (int row = 0; row < dst_height; row++)
    {
        int col = 0;
        // simd process
        uint8_t* src_ptr0 = src_data_ptr + (row * 2) * src_w * src_c;
        uint8_t* src_ptr1 = src_data_ptr + (row * 2 + 1) * src_w * src_c;
        float* dst_b_ptr = dst_data_ptr + (row * dst_width);
        float* dst_g_ptr = dst_b_ptr + dst_width * dst_height;
        float* dst_r_ptr = dst_g_ptr + dst_width * dst_height;
        for (; col < dst_width_aligned; col += 8)
        {
            v8_src0 = vld3q_u8(src_ptr0);
            src_ptr0 += 48;
            v8_src1 = vld3q_u8(src_ptr1);
            src_ptr1 += 48;
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_b_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));
            // vst1q_f32(dst_b_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            // vst1q_f32(dst_b_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_g_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));
            // vst1q_f32(dst_g_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            // vst1q_f32(dst_g_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_r_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));
            // vst1q_f32(dst_r_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            // vst1q_f32(dst_r_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));

            dst_b_ptr += 8;
            dst_g_ptr += 8;
            dst_r_ptr += 8;
        }

        // // leftover process | 3 channels
        if (dst_width_remained > 0)
        {
            col = dst_width - 8;
            src_ptr0 = src_data_ptr + ((row * 2) * src_w + col * 2) * src_c;
            src_ptr1 = src_data_ptr + ((row * 2 + 1) * src_w + col * 2) * src_c;
            dst_b_ptr = dst_data_ptr + (row * dst_width + col);
            dst_g_ptr = dst_b_ptr + dst_width * dst_height;
            dst_r_ptr = dst_g_ptr + dst_width * dst_height;
            v8_src0 = vld3q_u8(src_ptr0);
            v8_src1 = vld3q_u8(src_ptr1);
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_b_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_g_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_r_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
        }
    }
}

// arm neon asm
void half_resize_and_normalize_v3_asm(uint8_t* src_data_ptr,
                                      int src_h,
                                      int src_w,
                                      int src_c,
                                      std::vector<float>& dst_data,
                                      float* mean,
                                      float* std)
{
    int dst_height = src_h >> 1;
    int dst_width = src_w >> 1;
    int dst_channel = src_c;
    dst_data.resize(dst_height * dst_width * dst_channel);
    float* dst_data_ptr = (float*)dst_data.data();
    int dst_width_aligned = dst_width & (-8);
    int dst_width_remained = dst_width & (7);

    float32x4_t v_mean = vdupq_n_f32(-*(mean) / *std);
    float32x4_t v_scale = vdupq_n_f32(1.0f / *std);
    uint8x16x3_t v8_src0;
    uint8x16x3_t v8_src1;
    uint16x8_t v16_sum0;
    uint16x8_t v16_sum1;
    float32x4_t vfp32_low;
    float32x4_t vfp32_high;
    float shift = -*(mean) / *std;
    float scale = 1.0f / *std;
    for (int row = 0; row < dst_height; row++)
    {
        int col = 0;
        // simd process
        uint8_t* src_ptr0 = src_data_ptr + (row * 2) * src_w * src_c;
        uint8_t* src_ptr1 = src_data_ptr + (row * 2 + 1) * src_w * src_c;
        float* dst_b_ptr = dst_data_ptr + (row * dst_width);
        float* dst_g_ptr = dst_b_ptr + dst_width * dst_height;
        float* dst_r_ptr = dst_g_ptr + dst_width * dst_height;

        int step = dst_width_aligned >> 3;
        asm volatile(
            "vdup.32 q11,[%6]               \n"
            "vdup.32 q12,[%7]              \n"
            "0:                            \n"
            "vld3.8 {q0, q1, q2}, [%0]!    \n"
            "vld3.8 {q3, q4, q5}, [%1]!    \n"
            "vpaddl.u8 q0,q0               \n"
            "vpaddl.u8 q3,q3               \n"
            "vadd.i16 q0,q0,q3             \n"
            "vshr.s16 q0,q0,#2             \n"
            "vmovl.s16 q0,d0\n"
            "vmovl.s16 q6,d1\n"
            "vcvt.f32.u32 q0,q0\n"
            "vcvt.f32.u32 q6,q6\n"
            "vmov q7, q11\n"
            "vmov q8, q11\n"
            "vmla.f32 q7,q0,q12\n"
            "vmla.f32 q8,q6,q12\n"
            "vst1.32 q7,[%2]! \n"
            "vst1.32 q8,[%2]! \n"
            "\n"
            "subs %5 #1                    \n"
            "bne  0b                       \n"
            : "=r"(src_ptr0), "=r"(src_ptr1), "=r"(dst_b_ptr), "=r"(dst_g_ptr), "=r"(dst_r_ptr), "=r"(step)
            : "0"(src_ptr0), "1"(src_ptr1), "2"(dst_b_ptr), "3"(dst_g_ptr), "4"(dst_r_ptr), "5"(step), "6"(shift), "7"(scale)
            : "cc", "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q11", "q12");

        for (; col < dst_width_aligned; col += 8)
        {
            v8_src0 = vld3q_u8(src_ptr0);
            src_ptr0 += 48;
            v8_src1 = vld3q_u8(src_ptr1);
            src_ptr1 += 48;
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_b_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));

            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_g_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));

            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmlaq_f32(v_mean, vfp32_low, v_scale));
            vst1q_f32(dst_r_ptr + 4, vmlaq_f32(v_mean, vfp32_high, v_scale));

            dst_b_ptr += 8;
            dst_g_ptr += 8;
            dst_r_ptr += 8;
        }

        // // leftover process | 3 channels
        if (dst_width_remained > 0)
        {
            col = dst_width - 8;
            src_ptr0 = src_data_ptr + ((row * 2) * src_w + col * 2) * src_c;
            src_ptr1 = src_data_ptr + ((row * 2 + 1) * src_w + col * 2) * src_c;
            dst_b_ptr = dst_data_ptr + (row * dst_width + col);
            dst_g_ptr = dst_b_ptr + dst_width * dst_height;
            dst_r_ptr = dst_g_ptr + dst_width * dst_height;
            v8_src0 = vld3q_u8(src_ptr0);
            v8_src1 = vld3q_u8(src_ptr1);
            // channel b
            v16_sum0 = vpaddlq_u8(v8_src0.val[0]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[0]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_b_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_b_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel g
            v16_sum0 = vpaddlq_u8(v8_src0.val[1]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_g_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_g_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
            // channel r
            v16_sum0 = vpaddlq_u8(v8_src0.val[2]);
            v16_sum1 = vpaddlq_u8(v8_src1.val[2]);
            v16_sum0 = vshrq_n_u16(vaddq_u16(v16_sum0, v16_sum1), 2);
            vfp32_low = vcvtq_f32_u32(vmovl_u16(vget_low_u16(v16_sum0)));
            vfp32_high = vcvtq_f32_u32(vmovl_u16(vget_high_u16(v16_sum0)));
            vst1q_f32(dst_r_ptr, vmulq_f32(vaddq_f32(vfp32_low, v_mean), v_scale));
            vst1q_f32(dst_r_ptr + 4, vmulq_f32(vaddq_f32(vfp32_high, v_mean), v_scale));
        }
    }
}

void DownscaleUvNeonScalar(const cvMat& srcimg, cvMat& dstimg)
{
    Timer t;
    uint8_t* src = (uint8_t*)srcimg.data.data();
    int32_t src_width = srcimg.cols;
    int32_t src_stride = srcimg.cols * srcimg.channels;

    int dst_height = srcimg.rows / 2;
    int dst_width = srcimg.cols / 2;
    dstimg = cvMat(dst_height, dst_width, srcimg.channels);

    uint8_t* dst = (uint8_t*)dstimg.data.data();
    int32_t dst_stride = dstimg.cols * dstimg.channels;

    uint8x16x2_t v8_src0;
    uint8x16x2_t v8_src1;
    uint8x8x2_t v8_dst;
    int32_t dst_width_align = dst_width & (-8);
    int32_t remain = dst_width & 7;
    int32_t i = 0;

    for (int32_t j = 0; j < dst_height; j++)
    {
        uint8_t* src_ptr0 = src + src_stride * j * 2;
        uint8_t* src_ptr1 = src_ptr0 + src_stride;
        uint8_t* dst_ptr = dst + dst_stride * j;
        int32_t i = 0;
        for (; i < dst_width_align; i += 8) // 16 items output at one time
        {
            v8_src0 = vld2q_u8(src_ptr0);
            src_ptr0 += 32;
            v8_src1 = vld2q_u8(src_ptr1);
            src_ptr1 += 32;
            uint16x8_t v16_u_sum0 = vpaddlq_u8(v8_src0.val[0]);
            uint16x8_t v16_v_sum0 = vpaddlq_u8(v8_src0.val[1]);
            uint16x8_t v16_u_sum1 = vpaddlq_u8(v8_src1.val[0]);
            uint16x8_t v16_v_sum1 = vpaddlq_u8(v8_src1.val[1]);
            v8_dst.val[0] = vshrn_n_u16(vaddq_u16(v16_u_sum0, v16_u_sum1), 2);
            v8_dst.val[1] = vshrn_n_u16(vaddq_u16(v16_v_sum0, v16_v_sum1), 2);
            vst2_u8(dst_ptr, v8_dst);
            // for (size_t x = 0; x < 8; x++)
            // {
            //     printf("(%d,%d)[%d %d] ", dst_ptr[2 * x], dst_ptr[2 * x + 1], j, i + x);
            // }
            // std::cout << std::endl;
            dst_ptr += 16;
        }
        //process leftover
        i = dst_width - 8;
        src_ptr0 = src + src_stride * j * 2 + i * 2 * 2;
        src_ptr1 = src_ptr0 + src_stride;
        dst_ptr = dst + dst_stride * j + i * 2;
        v8_src0 = vld2q_u8(src_ptr0);
        v8_src1 = vld2q_u8(src_ptr1);
        uint16x8_t v16_u_sum0 = vpaddlq_u8(v8_src0.val[0]);
        uint16x8_t v16_v_sum0 = vpaddlq_u8(v8_src0.val[1]);
        uint16x8_t v16_u_sum1 = vpaddlq_u8(v8_src1.val[0]);
        uint16x8_t v16_v_sum1 = vpaddlq_u8(v8_src1.val[1]);
        v8_dst.val[0] = vshrn_n_u16(vaddq_u16(v16_u_sum0, v16_u_sum1), 2);
        v8_dst.val[1] = vshrn_n_u16(vaddq_u16(v16_v_sum0, v16_v_sum1), 2);
        vst2_u8(dst_ptr, v8_dst);
    }
}

// 函数实现创建一个图像
cvMat createImg(int rows, int cols, int channels)
{
    cvMat img(rows, cols, channels);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                img.setPixel(i, j, k, i + j);
            }
        }
    }
    return img;
}

template <typename T>
std::string print_bits(T val)
{
    std::bitset<sizeof(T) * 8> bits(val);
    std::cout << "The binary representation of " << val << " is: " << bits.to_string() << std::endl;
    return bits.to_string();
}

int main()
{
    int src_h = 622;
    int src_w = 426;
    cvMat src = createImg(src_h, src_w, 3);
    cvMat dst_native;
    cvMat dst_neon;
    // src.print(0);
    // for (size_t i = 0; i < 22; i++)
    // {
    //     /* code */
    // native_resize(src, dst_native, src_w / 2, src_h / 2);
    // half_resize(src, dst_neon);
    // DownscaleUvNeonScalar(src, dst_neon);
    //     // dst_neon.print();
    // dst_native.is_same(dst_neon);
    // }
    std::vector<uint8_t> src_data = src.data;
    std::vector<float> dst_neon_data((src_h / 2) * (src_w / 2) * 3);
    std::vector<float> dst_native_data((src_h / 2) * (src_w / 2) * 3);
    std::vector<float> mean = {1.f, 1.f, 1.f};
    std::vector<float> std = {10.f, 10.f, 10.f};
    // native_resize_half_and_normalize(src_data, src_h, src_w, 3, dst_native_data, mean.data(), std.data());
    // half_resize_and_normalize(src_data, src_h, src_w, 3, dst_neon_data, mean.data(), std.data());

    // half_resize_and_normalize_v2(src_data.data(), src_h, src_w, 3, dst_neon_data, mean.data(), std.data());
    // for (size_t i = 0; i < dst_neon_data.size(); i++)
    // {
    //     printf("i=%d %.4f, %.4f\n", i, dst_neon_data[i], dst_native_data[i]);
    //     if (dst_neon_data[i] != dst_native_data[i])
    //     {
    //         printf("error\n");
    //     }
    // }
    int count = 50;
    Timer t1;
    for (size_t i = 0; i < count; i++)
    {
        half_resize_and_normalize(src_data, src_h, src_w, 3, dst_neon_data, mean.data(), std.data());
    }
    printf("v1: %.4f ms\n", t1.elapsed() / 1000.f / count);

    Timer t2;
    for (size_t i = 0; i < count; i++)
    {
        half_resize_and_normalize_v2(src_data.data(), src_h, src_w, 3, dst_neon_data, mean.data(), std.data());
    }
    printf("v2: %.4f ms\n", t2.elapsed() / 1000.f / count);
    return 0;
}