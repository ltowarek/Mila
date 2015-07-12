#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>

const std::vector<double> kPowersOfTwo = {1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0,
                                          4096.0, 8192.0, 16384.0, 32768.0, 65536.0, 131072.0, 262144.0, 524288.0,
                                          1048576.0, 2097152.0, 4194304.0, 8388608.0, 16777216.0, 33554432.0};

double LargestPowerOfTwoLessOrEqual(const double kN) {
    assert (kN <= kPowersOfTwo.back());

    int i = 0;
    for (i = 0; i < kPowersOfTwo.size(); ++i) {
        if (kPowersOfTwo[i] > kN) {
            break;
        }
    }
    return i;
}

double BinaryModularExponentiation(const double kB, const double kN, const double kK) {
    if (kK == 1.0) {
        return 0.0;
    }

    double n = kN;
    double r = 1.0;
    double p = LargestPowerOfTwoLessOrEqual(kN);
    double t = pow(2.0, p - 1.0);

    for (int i = 0; i < static_cast<int>(p); ++i) {
        if (n >= t) {
            r *= kB;
            r -= static_cast<int>(r / kK) * kK;
            n -= t;
        }

        t *= 0.5;

        if (t >= 1.0) {
            r *= r;
            r -= static_cast<int>(r / kK) * kK;
        }

    }

    return r;
}

double Series(const double j, const double d) {
    double sum = 0.0;

    for (int k = 0; k < d; ++k) {
        double ak = 8.0 * k + j;
        double p = d - k;
        double t = BinaryModularExponentiation(16.0, p, ak);
        sum += t / ak;
        sum -= static_cast<int>(sum);
    }

    for (int k = d; k <= d + 100; ++k) {
        double ak = 8.0 * k + j;
        double t = pow(16.0, d - k) / ak;

        if (t < 1e-17) {
            break;
        }

        sum += t;
        sum -= static_cast<int>(sum);
    }

    return sum;
}

double BBP(const double position) {
    double s1 = Series(1, position);
    double s2 = Series(4, position);
    double s3 = Series(5, position);
    double s4 = Series(6, position);
    double result = 4.0 * s1 - 2.0 * s2 - s3 - s4;
    result = result - static_cast<int>(result) + 1.0;
    return result;
}

int main() {
    printf("%f\n", BBP(1000000));
    return 0;
}
