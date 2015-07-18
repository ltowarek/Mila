#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <string>

const std::vector<float> kPowersOfTwo = {1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f, 2048.0f,
                                         4096.0f, 8192.0f, 16384.0f, 32768.0f, 65536.0f, 131072.0f, 262144.0f, 524288.0f,
                                         1048576.0f, 2097152.0f, 4194304.0f, 8388608.0f, 16777216.0f, 33554432.0f};

float LargestPowerOfTwoLessOrEqual(const float kN) {
    assert (kN <= kPowersOfTwo.back());

    int i = 0;
    for (i = 0; i < kPowersOfTwo.size(); ++i) {
        if (kPowersOfTwo[i] > kN) {
            break;
        }
    }
    return i;
}

float BinaryModularExponentiation(const float kB, const float kN, const float kK) {
    if (kK == 1.0f) {
        return 0.0f;
    }

    float n = kN;
    float r = 1.0f;
    float p = LargestPowerOfTwoLessOrEqual(kN);
    float t = powf(2.0f, p - 1.0f);

    for (int i = 0; i < static_cast<int>(p); ++i) {
        if (n >= t) {
            r *= kB;
            r -= static_cast<int>(r / kK) * kK;
            n -= t;
        }

        t *= 0.5f;

        if (t >= 1.0f) {
            r *= r;
            r -= static_cast<int>(r / kK) * kK;
        }

    }

    return r;
}

float Series(const float j, const float d) {
    float sum = 0.0f;

    for (int k = 0; k < d; ++k) {
        float ak = 8.0f * k + j;
        float p = d - k;
        float t = BinaryModularExponentiation(16.0, p, ak);
        sum += t / ak;
        sum -= static_cast<int>(sum);
    }

    for (float k = d; k <= d + 100; ++k) {
        float ak = 8.0f * k + j;
        float t = powf(16.0f, d - k) / ak;

        if (t < 1e-17) {
            break;
        }

        sum += t;
        sum -= static_cast<int>(sum);
    }

    return sum;
}

float BBP(const float position) {
    float s1 = Series(1, position);
    float s2 = Series(4, position);
    float s3 = Series(5, position);
    float s4 = Series(6, position);
    float result = 4.0f * s1 - 2.0f * s2 - s3 - s4;
    result = result - static_cast<int>(result) + 1.0f;
    return result;
}

void DoubleToHex(const float input, const int precision, std::string &output) {
    std::string hex = "0123456789ABCDEF";

    float tmp = fabsf(input);

    for (int i = 0; i < precision; ++i) {
        tmp = 16.0f * (tmp - floorf(tmp));
        output[i] = hex[(int)tmp];
    }

    output[precision] = 0;
}

int main() {
    const long number_of_digits = 1000;
    std::vector<float> digits(number_of_digits, 0.0);
    std::string output = "";
    for (int i = 0; i < number_of_digits; ++i) {
        digits[i] = BBP(i);
        std::string hex = "";
        DoubleToHex(digits[i], 10, hex);
        output += hex[0];
    }
    output[number_of_digits] = 0;
    printf("%s\n", output.c_str());
    return 0;
}
