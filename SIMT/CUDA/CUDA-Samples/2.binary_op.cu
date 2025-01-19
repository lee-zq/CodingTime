/*
cuda实现矩阵加法
*/
#include <stdio.h>
#include <vector>
#include <cuda_runtime.h>

#include "../../../base_func/timer.hpp"

__global__ void vec_add_kernel_v1(float* dev_a_ptr, float* dev_b_ptr, float* dev_c_ptr, int n)
{
    const int tid = blockIdx.x * blockDim.x + threadIdx.x;
    // printf("tid: %d, val=%.2f\n", tid, dev_c_ptr[tid]);
    if (tid < n)
    {
        dev_c_ptr[tid] = dev_a_ptr[tid] * dev_b_ptr[tid];
    }
}

void vec_add_func(float* host_a_ptr, float* host_b_ptr, float* host_c_ptr, int element_size)
{
    float* dev_a_ptr;
    float* dev_b_ptr;
    float* dev_c_ptr;
    int mem_size = element_size * sizeof(float);
    cudaMalloc((void**)&dev_a_ptr, mem_size);
    cudaMalloc((void**)&dev_b_ptr, mem_size);
    cudaMalloc((void**)&dev_c_ptr, mem_size);

    int loop = 1000;
    while (loop--)
    {
        // Timer t;
        cudaMemcpy(dev_a_ptr, host_a_ptr, mem_size, cudaMemcpyKind::cudaMemcpyHostToDevice);
        cudaMemcpy(dev_b_ptr, host_b_ptr, mem_size, cudaMemcpyKind::cudaMemcpyHostToDevice);
        vec_add_kernel_v1<<< element_size / 512 + 1 , 512>>>(dev_a_ptr, dev_b_ptr, dev_c_ptr, element_size);
        cudaDeviceSynchronize();
        cudaMemcpy(host_c_ptr, dev_c_ptr, mem_size, cudaMemcpyKind::cudaMemcpyDeviceToHost);
    }

    cudaFree(dev_a_ptr);
    cudaFree(dev_b_ptr);
    cudaFree(dev_c_ptr);
}

int main()
{
    int element_size = 1024 * 1024;
    float* host_a_ptr = (float*)malloc(sizeof(float) * element_size);
    float* host_b_ptr = (float*)malloc(sizeof(float) * element_size);
    float* host_c_ptr = (float*)malloc(sizeof(float) * element_size);
    for (size_t i = 0; i < element_size; i++)
    {
        host_a_ptr[i] = 100.f;
        host_b_ptr[i] = 200.f;
    }
    
    vec_add_func(host_a_ptr, host_b_ptr, host_c_ptr, element_size);

    // for (size_t i = 0; i < element_size; i++)
    // {
    //     if (host_c_ptr[i] - 300.f > 0.01f){
    //         printf("Error at idx=%zd , val=%.2f\n", i, host_c_ptr[i]);
    //         std::abort();
    //     }
    // }

    delete host_a_ptr;
    delete host_b_ptr;
    delete host_c_ptr;

    printf("Success.\n");
    return 0;
}