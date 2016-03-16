#include "bbp_sequential.h"

float mila::bbp::sequential::BBP::Run() {
    return 0.0f;
}

size_t mila::bbp::sequential::BBP::LargestPowerOfTwoLessOrEqual(size_t n) {
    size_t i = 0;
    for (i = 0; i < kPowersOfTwo.size(); ++i) {
        if (kPowersOfTwo[i] > n) {
            break;
        }
    }
    return i;
}
