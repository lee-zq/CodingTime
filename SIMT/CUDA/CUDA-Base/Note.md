
这部分内容需要掌握常用的cuda c API调用方法，包括拷贝、流、事件、错误码等。
以及cuda核函数编写和编译方法，包括nvcc编译器的使用。


命令笔记：
 
编译：
默认编译（当前机器匹配）：nvcc ./cuda_nsight.cu -lcublas -std=c++11  -o cuda_nsight.o
编译指定架构（对应ptx版本）：nvcc ./cuda_nsight.cu -lcublas -std=c++11 -arch=compute_86 -o cuda_nsight.o
编译指定架构（对应cubin版本）：nvcc ./cuda_c_api.cu -lcublas -arch=compute_86 -code=sm_86 -o cuda_c_api.o
编译指定支持多重架构：
nvcc x.cu
    -gencode arch=compute_35,code=sm_35
    -gencode arch=compute_50,code=sm_50
    -gencode arch=compute_60

上述编译指令后，会生成3.5/5.0/6.0的cubin文件，以及6.0的PTX代码

nsight system运行命令：
分离运行: 在linux上执行 nsys profile --stats=true --trace=cuda,nvtx ./cuda_c_api.o ，
将生成的两个文件拷贝出来，在windows上打开后缀为.nsys-rep文件，另一个文件也要保证在同一目录下，部分功能需要读取。

cuda代码的优化思路（top-down策略，不要直接深入到汇编层面过度优化而忽略了热点）：
1. 先使用nsight system进行性能分析，找到瓶颈
2. 如果是kernel耗时问题，则使用nsight compute进行核函数分析，找到核函数的瓶颈进行优化
3. 如果是阻塞并行问题，则使用nsight system进行阻塞问题分析，通过cuda流进行计算和访存并行优化
4. 重新使用nsight system进行性能分析，查看优化效果，重复2-4步骤，直到满意

nsight环境检查：
nsys status -e
nsys --version


在wsl中，nsys profile无法使用，报错End of file。 原因是wsl中没有图形界面，需要指定--trace参数中去除不包含opengl。即可以使用nsys profile --stats=true --trace=cuda,nvtx ./cuda_nsight.o来进行分析。


