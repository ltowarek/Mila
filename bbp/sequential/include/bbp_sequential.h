#ifndef MILA_BBP_SEQUENTIAL_H_
#define MILA_BBP_SEQUENTIAL_H_

#include <cmath>
#include <cstddef>
#include <vector>
#include <string>

namespace mila {
    namespace bbp {
        namespace sequential {
            const std::vector<size_t> kPowersOfTwo =  {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                                       4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
                                                       1048576, 2097152, 4194304, 8388608, 16777216, 33554432};
            class BBP {
            public:
                BBP();
                BBP(double precision);

                float ComputeDigit(size_t position);
                float Series(size_t j, size_t d);  // Compute sum_k 16^(d-k)/(8*k*j)
                float ModularExponentiation(float b, size_t e, float m);  // Compute b^e mod m
                size_t LargestPowerOfTwoLessOrEqual(size_t n);
                std::string ConvertFractionToHex(float x, size_t number_of_digits);
                std::vector<float> ComputeDigits(size_t number_of_digits, size_t starting_position);

                double precision() const;
            private:
                const double precision_;
            };
        };  // sequential
    };  // bbp
}  // mila

#endif  // MILA_BBP_SEQUENTIAL_H_
