float GaussianKernel(const float distance, const float bandwidth) {
    return (1.0f / (sqrt(2.0f * M_PI_F) * bandwidth)) * exp(-0.5f * pow(distance / bandwidth, 2.0f));
}

kernel void MeanShift(global float4 *actual_points, global float4 *original_points, const int number_of_points, const float bandwidth, global float4 *shifted_points, global float *distances) {
    const int tid = get_global_id(0);
    float4 shift = { 0.0f, 0.0f, 0.0f, 0.0f };
    float scale = 0.0f;

    for (int i = 0; i < number_of_points; ++i) {
        float distance_value = distance(actual_points[tid], original_points[i]);
        float weight = GaussianKernel(distance_value, bandwidth);
        shift += weight * original_points[i];
        scale += weight;
    }

    shifted_points[tid] = shift / scale;
    distances[tid] = distance(actual_points[tid], shifted_points[tid]);
}
