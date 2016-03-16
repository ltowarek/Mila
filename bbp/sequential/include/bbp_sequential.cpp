#include "bbp_sequential.h"

float mila::bbp::sequential::BBP::Run() {
    return 0.0f;
}

float mila::bbp::sequential::BBP::ModularExponentiation(float b, size_t e, float m) {
    if (m == 1.0f) {
        return 0.0f;
    }

    auto c = 1.0f;
    auto p = LargestPowerOfTwoLessOrEqual(e);
    auto t = powf(2.0f, static_cast<float>(p - 1));

    for (size_t i = 0; i < p; ++i) {
        if (e >= t) {
            c *= b;
            c -= trunc(c / m) * m;
            e -= t;
        }

        t *= 0.5f;

        if (t >= 1.0f) {
            c *= c;
            c -= trunc(c / m) * m;
        }
    }

    return c;
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
