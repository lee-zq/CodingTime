// 定义一个和opencv的cv::Mat类似的类，用于存储图像数据
// 该类的数据存储方式为行优先，即按行存储
// 该类的数据类型为uint8_t，即每个像素点占用一个字节
// 该类的数据类型为三通道，即每个像素点有三个通道
// 该类的数据类型为BGR，即每个像素点的三个通道分别为B、G、R
// 该类的数据类型为连续存储，即每行的数据是连续存储的
// 该类的数据类型为非共享存储，即不支持浅拷贝
// 该类的数据类型为非线程安全，即不支持多线程操作

#ifndef SIMD_CVMAT_HPP
#define SIMD_CVMAT_HPP

#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

class cvMat
{
public:
    cvMat() : rows(0), cols(0), channels(0)
    {
    }
    cvMat(int rows, int cols, int channels) : rows(rows), cols(cols), channels(channels)
    {
        assert(rows > 0 && cols > 0 && channels > 0);
        data.resize(rows * cols * channels);
    }
    cvMat(const cvMat& mat) : rows(mat.rows), cols(mat.cols), channels(mat.channels)
    {
        assert(rows > 0 && cols > 0 && channels > 0);
        data = mat.data;
    }
    cvMat& operator=(const cvMat& mat)
    {
        rows = mat.rows;
        cols = mat.cols;
        channels = mat.channels;
        data = mat.data;
        return *this;
    }

    void setPixel(int row, int col, int channel, uint8_t value)
    {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        assert(channel >= 0 && channel < channels);
        data[(row * cols + col) * channels + channel] = value;
    }

    uint8_t getPixel(int row, int col, int channel) const
    {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        assert(channel >= 0 && channel < channels);
        return data[(row * cols + col) * channels + channel];
    }

    bool is_same(cvMat& img)
    {
        if (img.rows != rows || img.cols != cols || img.channels != channels)
        {
            std::cout << "shape no match!" << std::endl;
            return false;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::vector<int> self_pixel, in_pixel;
                for (size_t c = 0; c < channels; c++)
                {
                    self_pixel.push_back((int)this->data[(i * cols + j) * channels + c]);
                    in_pixel.push_back((int)img.data[(i * cols + j) * channels + c]);
                }
                printf("Local: [%d,%d] ", i, j);
                printf("self_pixel: (%d,%d,%d) ", self_pixel[0], self_pixel[1], self_pixel[2]);
                printf("in_pixel: (%d,%d,%d)\n", in_pixel[0], in_pixel[1], in_pixel[2]);
                if (self_pixel != in_pixel){
                    printf("error. no same\n");
                    return -1;
                }
            }
        }
        printf("success. same\n");
        return true;
    }

    void print() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                for (int k = 0; k < channels; k++)
                {
                    std::cout << static_cast<int>(getPixel(i, j, k)) << " ";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    int rows;
    int cols;
    int channels;
    std::vector<uint8_t> data;
};

#endif // SIMD_CVMAT_HPP

// // Path: SIMD/main.cpp
// #include <iostream>
// #include "cvMat.hpp"

// int main()
// {
//     cvMat mat(2, 2, 3);
//     mat.setPixel(0, 0, 0, 0);
//     mat.setPixel(0, 0, 1, 1);
//     mat.setPixel(0, 0, 2, 2);
//     mat.setPixel(0, 1, 0, 3);
//     mat.setPixel(0, 1, 1, 4);
//     mat.setPixel(0, 1, 2, 5);
//     mat.setPixel(1, 0, 0, 6);
//     mat.setPixel(1, 0, 1, 7);
//     mat.setPixel(1, 0, 2, 8);
//     mat.setPixel(1, 1, 0, 9);
//     mat.setPixel(1, 1, 1, 10);
//     mat.setPixel(1, 1, 2, 11);
//     mat.print();
//     return 0;
// }
// ```