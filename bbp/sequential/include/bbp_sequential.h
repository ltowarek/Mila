#ifndef MILA_BBP_SEQUENTIAL_H_
#define MILA_BBP_SEQUENTIAL_H_

#include <cstddef>
#include <vector>

namespace mila {
    namespace bbp {
        namespace sequential {
            const std::vector<size_t> kPowersOfTwo =  {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                                       4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
                                                       1048576, 2097152, 4194304, 8388608, 16777216, 33554432};
            class BBP {
            public:
                float Run();
                size_t LargestPowerOfTwoLessOrEqual(size_t n);
            };
        };  // sequential
    };  // bbp
}  // mila

#endif  // MILA_BBP_SEQUENTIAL_H_
