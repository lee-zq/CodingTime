#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#ifdef __AVX__
#warning X86_64 support - will using SSE/AVX compile
#include <immintrin.h>
#else
#include "sse2neon.h"
#warning ARM NEON support - will using arm_neon compile
#endif