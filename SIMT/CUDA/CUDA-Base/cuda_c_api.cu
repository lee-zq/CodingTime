#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
// #include <cuda_runtime.h>
// #include <device_launch_parameters.h>

__global__ void default_kernel()
{
    const int tid = blockIdx.x * blockDim.x + threadIdx.x;
    printf("device print: {[gridDim=(%d,%d,%d), blockDim=(%d,%d,%d)] [blockIdx=(%d,%d,%d), threadIdx=(%d,%d,%d)] "
           "[global_tid=%d]}\n",
           gridDim.x,
           gridDim.y,
           gridDim.z,
           blockDim.x,
           blockDim.y,
           blockDim.z,
           blockIdx.x,
           blockIdx.y,
           blockIdx.z,
           threadIdx.x,
           threadIdx.y,
           threadIdx.z,
           tid);
}

int test_cuda_kernel()
{
    /*
    kernel编写和调用方式
    1. 单独编写kernel，使用<<<grid, block>>>启动内核；
    2. 使用默认流启动kernel时，使用<<<grid, block>>>启动内核；
    3. 使用非空流启动kernel时，使用<<<grid, block, 0, stream>>>启动内核；
    4. kernel函数对于主机线程是异步的，需要显式调用cudaDeviceSynchronize()等待kernel执行完成；
    */

    // 创建一个网格和一个块，类型是dim3，在默认流中启动内核
    dim3 grid(10, 1, 1);
    dim3 block(10, 1, 1);
    // Launch the kernel
    default_kernel<<<grid, block>>>();
    cudaDeviceSynchronize();
    printf("test1 Done\n");
    return 0;
}

int test_cuda_stream()
{
    /*
    cuda流的创建和使用：
    1. 创建非空流，一般使用cudaStreamCreate(&stream)；
    2. 创建带flag的非空流，一般使用cudaStreamCreateWithFlags(&stream, flag)，flag可以用于指定该流和默认流之间的同步策略；
    3. 不同流之间的操作是不保证时序的，同一流内的操作是保证时序的；
    */

    dim3 grid(10, 1, 1);
    dim3 block(10, 1, 1);
    // 1. 直接创建非空流
    cudaStream_t stream1;
    cudaStreamCreate(&stream1);

    // 2. 带flag的非空流
    // 2.1 使用cudaStreamDefault，我理解是和默认流隐式，与默认流交替同步执行，与上述cudaStreamCreate一样
    cudaStream_t stream21;
    cudaStreamCreateWithFlags(&stream21, cudaStreamDefault);
    // 2.2 使用cudaStreamNonBlocking，表示流是异步的，与默认流并行执行
    cudaStream_t stream22;
    cudaStreamCreateWithFlags(&stream22, cudaStreamNonBlocking);

    default_kernel<<<grid, block, 0, stream1>>>();
    default_kernel<<<grid, block, 0, stream21>>>();
    default_kernel<<<grid, block, 0, stream22>>>();
    cudaDeviceSynchronize();

    printf("test2 Done\n");
    return 0;
}


int test_cuda_copy()
{
    /*
    cuda拷贝函数的使用：
    1. 默认同步拷贝函数实际是在默认流上执行的，对于主机线程是阻塞式的；
    2. 非空流异步拷贝函数是在指定流上执行的，对于主机线程是非阻塞式的；
    3. 流内操作是保证时序的, 可以将多个操作提交到一个流后，再等待执行完成，多个流之间是不保证时序的；
    */

    // 创建host内存并初始化
    int mem_size = 1024 * 10;
    int* host_mem = (int*)malloc(mem_size * sizeof(int));
    for (int i = 0; i < mem_size; i++)
    {
        host_mem[i] = i;
    }
    // 1. 默认流同步执行。接口是同步的，但是实际上是异步的，因为cudaMemcpy是阻塞的，会等待拷贝完成
    int* device_mem1;
    cudaMalloc(&device_mem1, mem_size * sizeof(int));
    cudaMemcpy(device_mem1, host_mem, mem_size * sizeof(int), cudaMemcpyHostToDevice);
    // do something on device
    cudaMemcpy(host_mem, device_mem1, mem_size * sizeof(int), cudaMemcpyDeviceToHost);

    // 2. 非空流异步执行。接口是异步的，实际上是异步的，因为cudaMemcpyAsync是非阻塞的，host线程不会等待拷贝完成,需要显式调用cudaDeviceSynchronize()等待拷贝完成
    int* device_mem2;
    cudaMalloc(&device_mem2, mem_size * sizeof(int));
    cudaStream_t stream2;
    cudaStreamCreate(&stream2);
    cudaMemcpyAsync(device_mem2, host_mem, mem_size * sizeof(int), cudaMemcpyHostToDevice, stream2);
    cudaDeviceSynchronize();
    // do something on device
    cudaMemcpyAsync(host_mem, device_mem2, mem_size * sizeof(int), cudaMemcpyDeviceToHost, stream2);
    cudaDeviceSynchronize();

    // 释放内存、流对象、设备内存
    free(host_mem);
    cudaFree(device_mem1);
    cudaFree(device_mem2);
    cudaStreamDestroy(stream2);

    printf("test3 Done\n");
    return 0;
}

int test_cuda_event()
{
    /*
    cuda事件的使用：
    1. cudaEventCreate(&event)创建事件；
    2. cudaEventRecord(event, stream)记录事件，stream为空则在默认流上记录；
    3. cudaEventSynchronize(event)等待事件完成；
    4. cudaEventElapsedTime(&time, start, end)计算两个事件之间的时间差；
    5. cudaEventDestroy(event)销毁事件；
    */

    // 创建host内存并初始化
    int mem_size = 1024 * 10;
    int* host_mem = (int*)malloc(mem_size * sizeof(int));
    for (int i = 0; i < mem_size; i++)
    {
        host_mem[i] = i;
    }
    // 创建device内存
    int* device_mem;
    cudaMalloc(&device_mem, mem_size * sizeof(int));

    // 创建事件
    cudaEvent_t start, end;
    cudaEventCreate(&start);
    cudaEventCreate(&end);

    // 记录事件
    cudaEventRecord(start);
    cudaMemcpy(device_mem, host_mem, mem_size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(host_mem, device_mem, mem_size * sizeof(int), cudaMemcpyDeviceToHost);
    cudaEventRecord(end);

    // 等待事件完成
    cudaEventSynchronize(end);

    // 计算时间差
    float time;
    cudaEventElapsedTime(&time, start, end);
    printf("Time: %f ms\n", time);

    // 释放内存、事件对象、设备内存
    free(host_mem);
    cudaFree(device_mem);
    cudaEventDestroy(start);
    cudaEventDestroy(end);

    printf("test4 Done\n");
    return 0;
}

int test_cuda_stream_sync()
{
    /*
    cuda流的同步：
    1. cudaStreamSynchronize(stream)等待流上的所有操作完成, 相比于cudaDeviceSynchronize()更细粒度，可以只等待一个流上的操作完成；
    2. cudaStreamWaitEvent(stream, event)等待事件完成后再执行流上的操作；
    3. cudaStreamQuery(stream)查询流上的操作是否完成；
    */

    // 创建host内存并初始化
    int mem_size = 1024 * 100;
    int* host_mem = (int*)malloc(mem_size * sizeof(int));
    for (int i = 0; i < mem_size; i++)
    {
        host_mem[i] = i;
    }
    // 创建device内存
    int* device_mem;
    cudaMalloc(&device_mem, mem_size * sizeof(int));

    // 创建流和事件
    cudaStream_t stream;
    cudaStreamCreate(&stream);
    cudaEvent_t event;
    cudaEventCreate(&event);

    // 记录事件
    cudaMemcpyAsync(device_mem, host_mem, mem_size * sizeof(int), cudaMemcpyHostToDevice, stream);
    cudaEventRecord(event, stream);
    cudaMemcpyAsync(host_mem, device_mem, mem_size * sizeof(int), cudaMemcpyDeviceToHost, stream);

    // 等待流上的操作完成
    cudaStreamSynchronize(stream);

    // 释放内存、事件对象、设备内存
    free(host_mem);
    cudaFree(device_mem);
    cudaStreamDestroy(stream);
    cudaEventDestroy(event);

    printf("test5 Done\n");
    return 0;
}

int test_cuda_error()
{
    /*
    cuda错误处理接口
    CUDA常见的错误码有：
    1. cudaSuccess：操作成功；
    2. cudaErrorIllegalAddress：无效的地址, 访存越界 code=700；
    3. cudaErrorMemoryAllocation：内存分配失败；
    4. cudaErrorInitializationError：初始化错误；
    5. cudaErrorLaunchFailure：内核启动失败；

    */

    // cudaGetErrorName函数接受一个错误码，返回错误名称
    __host__ __device__ const char* cudaGetErrorName(cudaError_t error);
    // cudaGetErrorString函数接受一个错误码，返回错误描述
    __host__ __device__ const char* cudaGetErrorString(cudaError_t error);
    // cudaGetLastError函数返回上一次CUDA runtime调用时的错误码，并将CUDA错误码置为cudaSuccess
    __host__ __device__ cudaError_t cudaGetLastError(void);
    // cudaPeekAtLastError函数与上面功能一样，但不会重置CUDA的错误信息
    __host__ __device__ cudaError_t cudaPeekAtLastError(void);

    return 0;
}


int main()
{
    int loop = 1000;
    while (loop--){
        test_cuda_kernel();
        test_cuda_stream();
        test_cuda_copy();
        test_cuda_event();
        test_cuda_stream_sync();
    }

    return 0;
}