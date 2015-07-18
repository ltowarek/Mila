constant float kPowersOfTwo[] = {1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f, 2048.0f,
                                 4096.0f, 8192.0f, 16384.0f, 32768.0f, 65536.0f, 131072.0f, 262144.0f, 524288.0f,
                                 1048576.0f, 2097152.0f, 4194304.0f, 8388608.0f, 16777216.0f, 33554432.0f};
constant int kPowersOfTwoSize = 26;

float LargestPowerOfTwoLessOrEqual(const float kN) {
    int i = 0;
    for (i = 0; i < kPowersOfTwoSize; ++i) {
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
    float t = pow(2.0f, p - 1.0f);

    for (int i = 0; i < p; ++i) {
        if (n >= t) {
            r *= kB;
            r -= convert_int(r / kK) * kK;
            n -= t;
        }

        t *= 0.5f;

        if (t >= 1.0f) {
            r *= r;
            r -= convert_int(r / kK) * kK;
        }
    }

    return r;
}

float Series(const float j, const float d) {
    float sum = 0.0f;

    for (int k = 0; k < d; ++k) {
        float ak = 8.0f * k + j;
        float p = d - k;
        float t = BinaryModularExponentiation(16.0f, p, ak);
        sum += t / ak;
        sum -= convert_int(sum);
    }

    for (float k = d; k <= d + 100; ++k) {
        float ak = 8.0f * k + j;
        float t = pow(16.0f, d - k) / ak;

        if (t < 1e-17) {
            break;
        }

        sum += t;
        sum -= convert_int(sum);
    }

    return sum;
}

kernel void bbp(global float *results) {
    const int kTid = get_global_id(0);
    float s1 = Series(1, kTid);
    float s2 = Series(4, kTid);
    float s3 = Series(5, kTid);
    float s4 = Series(6, kTid);
    float tmp_result = 4.0f * s1 - 2.0f * s2 - s3 - s4;
    tmp_result = tmp_result - convert_int(tmp_result) + 1.0f;
    results[kTid] = tmp_result;
}

