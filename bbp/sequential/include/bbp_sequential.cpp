#include "bbp_sequential.h"

float mila::bbp::sequential::BBP::ComputeDigit(size_t position) {
    auto series_1 = Series(1, position);
    auto series_2 = Series(4, position);
    auto series_3 = Series(5, position);
    auto series_4 = Series(6, position);
    auto result = 4.0f * series_1 - 2.0f * series_2 - series_3 - series_4;  // BBP formula
    result = result - truncf(result) + 1.0f;
    return result;
}

float mila::bbp::sequential::BBP::Series(size_t j, size_t d) {
    auto sum = 0.0f;

    for (size_t k = 0; k < d; ++k) {
        auto ak = 8.0f * k + j;
        auto p = d - k;
        auto t = ModularExponentiation(16.0f, p, ak);
        sum += t / ak;
        sum -= truncf(sum);
    }

    for (size_t k = d; k <= d + 100; ++k) {
        auto ak = 8.0f * k + j;
        auto p = static_cast<float>(d) - static_cast<float>(k);
        auto t = powf(16.0f, p) / ak;

        if (t < precision_) {
            break;
        }

        sum += t;
        sum -= truncf(sum);
    }

    return sum;
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
    auto i = size_t{0};
    for (i = 0; i < kPowersOfTwo.size(); ++i) {
        if (kPowersOfTwo[i] > n) {
            break;
        }
    }
    return i;
}

mila::bbp::sequential::BBP::BBP(double precision): precision_(precision) {

}

mila::bbp::sequential::BBP::BBP(): precision_(1e-5) {

}

double mila::bbp::sequential::BBP::precision() const {
    return precision_;
}

std::string mila::bbp::sequential::BBP::ConvertFractionToHex(float number, size_t number_of_digits) {
    const auto kHex = std::string("0123456789ABCDEF");
    auto digit = std::string(number_of_digits, '-');
    auto value = fabsf(number);
    for (size_t i = 0; i < number_of_digits; ++i) {
        value = 16.0f * (value - floorf(value));
        digit[i] = kHex[static_cast<size_t>(value)];
    }
    return digit;
}

std::vector<float> mila::bbp::sequential::BBP::ComputeDigits(size_t number_of_digits, size_t starting_position) {
    auto digits = std::vector<float>(number_of_digits, 0.0f);
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] = ComputeDigit(starting_position + i);
    }
    return digits;
}

std::vector<std::string> mila::bbp::sequential::BBP::ConvertFractionsToHex(std::vector<float> numbers,
                                                                           size_t number_of_digits) {
    auto digits = std::vector<std::string>(numbers.size(), "-");
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] = ConvertFractionToHex(numbers[i], number_of_digits);
    }
    return digits;
}

std::string mila::bbp::sequential::BBP::Run(size_t number_of_digits, size_t starting_position) {
    auto digits = ComputeDigits(number_of_digits, starting_position);
    auto hex_digits = ConvertFractionsToHex(digits, 1);
    auto output = std::string("");
    for (auto digit : hex_digits) {
        output += digit[0];
    }
    return output;
}
