#include <iostream>
#include <time.h>

int clock_method()
{   // CPU时钟计时单元，每秒为1000个时钟周期
    clock_t begin_time = clock();
    printf("running...\n");
    usleep(100000);
    clock_t end_time = clock();
    float seconds = float(end_time - begin_time) / 1000; //最小精度到ms
    printf("%fms\n", seconds);
    return 0;
}

#include <iostream>
#include <chrono>

int high_resolution_clock_method()
{
    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    printf("running...\n");
    usleep(100000);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds timeInterval = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
    std::cout << timeInterval.count() << "ms\n";
}

int high_resolution_clock_method()
{
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
    printf("running...\n");
    usleep(100000);
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    milliseconds timeInterval = std::chrono::duration_cast<milliseconds>(endTime - beginTime);
    std::cout <<  << timeInterval.count() << "ms\n";
}

// rand()函数: 产生一个0到RAND_MAX之间的伪随机整数
// srand(int)函数: 用来设置rand()产生随机数时的随机数种子