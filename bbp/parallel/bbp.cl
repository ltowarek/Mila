constant float kPowersOfTwo[] = {1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f, 2048.0f,
                                 4096.0f, 8192.0f, 16384.0f, 32768.0f, 65536.0f, 131072.0f, 262144.0f, 524288.0f,
                                 1048576.0f, 2097152.0f, 4194304.0f, 8388608.0f, 16777216.0f, 33554432.0f};
constant int kPowersOfTwoSize = 26;

float LargestPowerOfTwoLessOrEqual(float n) {
    int i = 0;
    for (i = 0; i < kPowersOfTwoSize; ++i) {
        if (kPowersOfTwo[i] > n) {
            break;
        }
    }
    return i;
}

float ModularExponentiation(float b, float e, float m) {
    if (m == 1.0f) {
        return 0.0f;
    }

    float n = e;
    float r = 1.0f;
    float p = LargestPowerOfTwoLessOrEqual(e);
    float t = pow(2.0f, p - 1.0f);

    for (int i = 0; i < p; ++i) {
        if (n >= t) {
            r *= b;
            r -= convert_int(r / m) * m;
            n -= t;
        }

        t *= 0.5f;

        if (t >= 1.0f) {
            r *= r;
            r -= convert_int(r / m) * m;
        }
    }

    return r;
}

float Series(float j, float d) {
    float sum = 0.0f;

    for (int k = 0; k < d; ++k) {
        float ak = 8.0f * k + j;
        float p = d - k;
        float t = ModularExponentiation(16.0f, p, ak);
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

kernel void bbp(int starting_position, global float *results) {
    const int kTid = get_global_id(0);
    const int position = starting_position + kTid;
    float s1 = Series(1, position);
    float s2 = Series(4, position);
    float s3 = Series(5, position);
    float s4 = Series(6, position);
    float tmp_result = 4.0f * s1 - 2.0f * s2 - s3 - s4;
    tmp_result = tmp_result - convert_int(tmp_result) + 1.0f;
    results[kTid] = tmp_result;
}

