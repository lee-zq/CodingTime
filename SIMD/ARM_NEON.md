NEON 是 ARM Cortex A 系列处理器支持的数据并行技术，和 SSE/AVX 类似：一条指令以指令级 SIMD 的方式同时对多个数据进行操作，同时，操作的数据个数由向量寄存器的长度和数据类型共同决定。 NEON SIMD 寄存器的长度为 128 位，如果操作 32 位浮点数，可同时操作 4 个；如果操作 16 位整数（short），可同时操作 8 个；而如果操作 8 位整数，则可同时操作 16 个。可见，选择合适的数据类型也是优化性能的重要方法之一，本章中就有相关的实例。

ARMv7 NEON 指令集架构具有 16 个 128 位的向量寄存器，命名为 q0～q15。这 16 个寄存器又可以拆分成 32 个 64 位寄存器，命名为 d0～d31。其中qn和d2n，d2n+1是一样的，故使用汇编编写代码时要注意避免产生寄存器覆盖。

使用 NEON 指令读写数据时，不需要保证数据对齐到 16 字节。GCC 支持的 NEON 指令集的C 语言接口（内置函数，intrinsic）声明在 arm_neon.h 头文件中。 NEON 指令集支持的映射到向量寄存器的向量数据类型命名格式为type size x num。

其中：

①type表示元素的数据类型，目前只支持 float、int和uint。

②size表示每个元素的数据长度位数，float 只支持 32 位浮点数，int 和 unit 支持 8 位、16 位、 32 位和 64 位整数。

③num表示元素数目，即向量寄存器的位数。由于NEON只支持 64 位和 128 位向量寄存器，故size和num的乘积只能是64或128。

如uint16x8_t表示每个元素数据类型为uint，大小为16位，每个向量保存8个数，故使用的向量寄存器长度为128位；如float32x4_t表示每个元素的数据类型为32位浮点，向量寄存器可操作4个数据，故使用128位向量寄存器。

NEON 内置函数命名方式有两种，分别对应源操作数是否涉及标量，具体解释如下。

1）源操作数涉及标量时，数据类型表示为v op dt_n/lane_type。

其中：

①n表示源操作数是标量而返回向量，lane 表示运算涉及向量的一个元素。

②op表示操作，如dup、add、sub、mul、mla等。

③dt是目标向量和源向量长度表示符。

如果目标向量和源向量长度都为64位，dt为空。

如果源向量和目标向量长度一致都为128位，dt为q。

如果目标向量长度比源数向量长度大，且源向量长度都为 64 位、目标向量长度为 128 位，dt为 l（英文字母，不是数字1）。

如果多个源向量长度不一致且都不大于目标向量长度（一个源向量长度为 64 位，另一个为 128 位，目标向量长度为 128 位），dt为 w。

如果目标向量长度比源向量长度小，即目标向量长度dt为 n。

④type表示源数据类型缩写，如u8 表示 uint8；u16 表示 uint16；u32 表示 uint32；s8 表示 int8；s16 表示 int16；s32 表示 int32；f32 表示 float32。

2）源操作数全是向量时，数据类型表示为v op dt_type，其中op、dt和type的含义和源操作数为标量时一致。

下面给出几个实例以增加读者理解。

1）内置函数vmla_f32表示使用64位向量寄存器操作32位浮点数据，即源操作数使用的向量寄存器和目标操作数使用的向量寄存器表示都是float32x2_t。

2）内置函数vmlaq_f32表示使用128位向量寄存器操作32位浮点数据，即源操作数使用的向量寄存器和目标操作数使用的向量表示都是float32x4_t。

3）内置函数vmlal_u32表示使用的目标寄存器是128位向量，源寄存器是64位向量，操作32位无符号整数。

4）内置函数vaddw_s32表示使用的目标寄存器是128位向量，源寄存器一个是64位向量，一个是128位向量。

5）内置函数vmovn_u64表示目标寄存器是64位向量，源寄存器是128位向量，即同时操作两个数。