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
            for (size_t x = 0; x < 8; x++)
            {
                printf("(%d,%d,%d)[%d %d] ", dst_ptr[3 * x], dst_ptr[3 * x + 1], dst_ptr[3 * x + 3], row, col + x);
            }
            std::cout << std::endl;
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
                img.setPixel(i, j, k, i + j + k);
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
    int src_h = 34;
    int src_w = 36;
    cvMat src = createImg(src_h, src_w, 3);
    cvMat dst_native;
    cvMat dst_neon;
    native_resize(src, dst_native, src_w / 2, src_h / 2);
    half_resize(src, dst_neon);
    // DownscaleUvNeonScalar(src, dst_neon);
    // dst_neon.print();
    dst_native.is_same(dst_neon);

    return 0;
}