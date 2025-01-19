/*
cuda实现element wise op
*/
#include <stdio.h>
#include <vector>
#include <cuda_runtime.h>

#include "../../../base_func/timer.hpp"

// 后向索引版本，线程配置以输入张量shape排布，计算每个线程对应的数据源位置和目标位置
__global__ void Transpose_kernel_v1(float* dev_a_ptr, float* dev_b_ptr, int m, int n)
{
    const int rowIdx = blockIdx.y * blockDim.y + threadIdx.y;
    const int colIdx = blockIdx.x * blockDim.x + threadIdx.x;

    // printf("rowIdx: %d, colIdx=%d\n", rowIdx, colIdx);
    if (rowIdx < m && colIdx < n)
    {
        dev_b_ptr[colIdx * m + rowIdx] = dev_a_ptr[rowIdx * n + colIdx];
    }
}

// 前向索引版本，线程配置以输出张量shape排布，计算每个线程对应的数据目标位置和原位置
// cuda编程多以这种形式申请计算资源，以一个目标值为单位划分一个线程进行计算，特点是目标值之间不关联
__global__ void Transpose_kernel_v2(float* dev_a_ptr, float* dev_b_ptr, int m, int n)
{
    const int rowIdx = blockIdx.y * blockDim.y + threadIdx.y;
    const int colIdx = blockIdx.x * blockDim.x + threadIdx.x;

    // printf("rowIdx: %d, colIdx=%d\n", rowIdx, colIdx);
    if (rowIdx < n && colIdx < m)
    {
        dev_b_ptr[rowIdx * m + colIdx] = dev_a_ptr[colIdx * n + rowIdx];
    }
}

__global__ void Transpose_kernel_v3(float* dev_a_ptr, float* dev_b_ptr, int m, int n)
{
    const int rowIdx = blockIdx.y * blockDim.y + threadIdx.y;
    const int colIdx = blockIdx.x * blockDim.x + threadIdx.x;

    // printf("rowIdx: %d, colIdx=%d\n", rowIdx, colIdx);
    if (rowIdx < n && colIdx < m)
    {
        dev_b_ptr[rowIdx * m + colIdx] = dev_a_ptr[colIdx * n + rowIdx];
    }
}

void mat_transpose_op_func(float* host_a_ptr, float* host_b_ptr, int m, int n)
{
    float* dev_a_ptr;
    float* dev_b_ptr;
    int mem_size = m * n * sizeof(float);
    cudaMalloc((void**)&dev_a_ptr, mem_size);
    cudaMalloc((void**)&dev_b_ptr, mem_size);

    std::vector<int> block_len_x = {4, 8, 16, 32};
    std::vector<int> block_len_y = {4, 8, 16, 32};
    for (auto x : block_len_x)
    {
        for (auto y : block_len_y)
        {

            dim3 block(x, y);
            // dim3 grid(n / x + 1, m / y + 1); // v1配置 src->dst
            dim3 grid((m + x - 1) / x, (n + y - 1) / y); // v2配置 dst->src
            int loop = 10;
            while (loop--)
            {
                // Timer t;
                cudaMemcpy(dev_a_ptr, host_a_ptr, mem_size, cudaMemcpyKind::cudaMemcpyHostToDevice);
                // Transpose_kernel_v1<<<grid, block>>>(dev_a_ptr, dev_b_ptr, m, n);
                Transpose_kernel_v2<<<grid, block>>>(dev_a_ptr, dev_b_ptr, m, n);

                cudaDeviceSynchronize();
                cudaMemcpy(host_b_ptr, dev_b_ptr, mem_size, cudaMemcpyKind::cudaMemcpyDeviceToHost);
            }
        }
    }

    cudaFree(dev_a_ptr);
    cudaFree(dev_b_ptr);
}

int main()
{
    int m = 2300;
    int n = 1500;
    int element_size = m * n;
    float* host_a_ptr = (float*)malloc(sizeof(float) * element_size);
    float* host_b_ptr = (float*)malloc(sizeof(float) * element_size);
    // int idx = 0;
    // for (size_t i = 0; i < m; i++)
    // {
    //     for (size_t j = 0; j < n; j++)
    //     {
    //         host_a_ptr[i * n + j] = ++idx;
    //         printf("%.2f, ", host_a_ptr[i * n + j]);
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << std::endl;

    mat_transpose_op_func(host_a_ptr, host_b_ptr, m, n);

    // for (size_t i = 0; i < n; i++)
    // {
    //     for (size_t j = 0; j < m; j++)
    //     {
    //         printf("%.2f, ", host_b_ptr[i * m + j]);
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << std::endl;

    delete host_a_ptr;
    delete host_b_ptr;

    printf("Success.\n");
    return 0;
}