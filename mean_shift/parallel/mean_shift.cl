float GaussianKernel(const float kDistance, const float kBandwidth) {
    return (1.0f / (sqrt(2.0f * M_PI_F) * kBandwidth)) * exp(-0.5f * pow(kDistance / kBandwidth, 2.0f));
}

kernel void MeanShift(constant float4 *actual_points, const int kNumberOfPoints, const float kBandwidth, global float4 *shifted_points, global float *distances) {
    const int kTid = get_global_id(0);
    float4 shift = { 0.0f, 0.0f, 0.0f, 0.0f };
    float scale = 0.0f;

    for (int i = 0; i < kNumberOfPoints; ++i) {
        float distance_value = distance(actual_points[kTid], actual_points[i]);
        float weight = GaussianKernel(distance_value, kBandwidth);
        shift += weight * actual_points[i];
        scale += weight;
    }

    shifted_points[kTid] = shift / scale;
    distances[kTid] = distance(actual_points[kTid], shifted_points[kTid]);
}
