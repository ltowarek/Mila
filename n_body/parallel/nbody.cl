typedef struct {
    float3 position;
    float m;
    float3 velocity;
} Body;

constant float eps = 0.0001f;
constant float dt = 0.01f;

kernel void nbody(global Body *bodies) {
    const int kTid = get_global_id(0);
    const int number_of_bodies = get_global_size(0);

    float3 a = {0.f, 0.f, 0.f};

    for (int i = 0; i < number_of_bodies; ++i) {
        float3 d = bodies[i].position - bodies[kTid].position;
        float invr = rsqrt(d.x * d.x + d.y * d.y + d.z * d.z + eps);
        float f = bodies[i].m * invr * invr * invr;
        a += f * d;
    }

    barrier(CLK_GLOBAL_MEM_FENCE);

    bodies[kTid].position += dt * bodies[kTid].velocity + 0.5f * dt * dt * a;
    bodies[kTid].velocity += dt * a;
}

