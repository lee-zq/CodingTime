
/*
Nsight Systems：用于高层次的系统级性能分析，帮助你识别整个应用的瓶颈，例如 GPU 内核启动延迟、数据传输等问题。 
Nsight Compute：用于深入分析单个 CUDA 内核的性能瓶颈，帮助你优化内核代码。
通常，你可以使用 Nsight Systems 先找到瓶颈的 CUDA 内核，然后使用 Nsight Compute 对这些内核进行详细的性能分析。
一般分两步走：先在运行环境中生成报告，然后在可视化软件中查看分析报告。
Tips：早期cuda可能包含nvvp或者nvprof，这两个工具已经被废弃了，性能分析以nsight为准。
*/
#include <stdio.h>
#include <cuda_runtime.h>

// 向量加法 cuda kernel
__global__ void vector_add(float *a, float *b, float *c, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        c[i] = a[i] + b[i];
    }
}

__global__ void transposeNative(float* input, float* output, int m, int n)
{
    int colID_input = threadIdx.x + blockDim.x * blockIdx.x;
    int rowID_input = threadIdx.y + blockDim.y * blockIdx.y;
    if (rowID_input < m && colID_input < n)
    {
        int index_input = colID_input + rowID_input * n;
        int index_output = rowID_input + colID_input * m;
        output[index_output] = input[index_input];
    }
}

// 向量加法 host函数
void vector_add_host(float *a, float *b, float *c, int n)
{
    // 申请显存
    float *dev_a, *dev_b, *dev_c;
    cudaMalloc((void **)&dev_a, n * sizeof(float));
    cudaMalloc((void **)&dev_b, n * sizeof(float));
    cudaMalloc((void **)&dev_c, n * sizeof(float));

    // 将数据从主机内存拷贝到显存
    cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice);

    // 启动kernel
    transposeNative<<<(n+127)/128, 128>>>(dev_a, dev_b, 10000, 10000);
    vector_add<<<(n + 255) / 256, 256>>>(dev_a, dev_b, dev_c, n);
    vector_add<<<(n + 255) / 256, 256>>>(dev_a, dev_b, dev_c, n);
    vector_add<<<(n + 255) / 256, 256>>>(dev_a, dev_b, dev_c, n);

    // 将数据从显存拷贝到主机内存
    cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost);

    // 释放显存
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}

// 矩阵转置 host函数
void transpose_host(float* input, float* output, int m, int n)
{
    // 申请显存
    float* dev_input, *dev_output;
    cudaMalloc((void**)&dev_input, m * n * sizeof(float));
    cudaMalloc((void**)&dev_output, m * n * sizeof(float));

    // 将数据从主机内存拷贝到显存
    cudaMemcpy(dev_input, input, m * n * sizeof(float), cudaMemcpyHostToDevice);

    // 启动kernel
    dim3 block(16, 16);
    dim3 grid((n + block.x - 1) / block.x, (m + block.y - 1) / block.y);
    transposeNative<<<grid, block>>>(dev_input, dev_output, m, n);

    // 将数据从显存拷贝到主机内存
    cudaMemcpy(output, dev_output, m * n * sizeof(float), cudaMemcpyDeviceToHost);

    // 释放显存
    cudaFree(dev_input);
    cudaFree(dev_output);
}

int main()
{
    int n = 100000000;
    float *a = new float[n];
    float *b = new float[n];
    float *c = new float[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = 100.0f;
        b[i] = 200.0f;
    }

    int loop = 1000;
    while (loop--){
        vector_add_host(a, b, c, n);
    }

    delete[] a;
    delete[] b;
    delete[] c;
    printf("Done\n");
    return 0;
}


