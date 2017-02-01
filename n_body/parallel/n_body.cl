typedef struct {
  float active_repulsion_force;
  float active_repulsion_min_distance;
  float passive_repulsion_force;
  float passive_repulsion_min_distance;
  float damping_force;
  float central_force;
  float2 center;
} Parameters;

typedef struct {
    float2 position;
    float2 velocity;
    float2 acceleration;
} Particle;

void ApplyRepulsionForce(const float force_value,
                         const float min_distance,
                         const float2 position,
                         Particle *particle) {
  float2 distance_vector = position - particle->position;
  float distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
  if (distance_squared < min_distance * min_distance) {
    float inverted_distance_squared = 1.0f / distance_squared;
    particle->acceleration -= distance_vector * force_value * inverted_distance_squared;
  }
}

void ApplyCentralForce(const float2 center,
                       const float force_value,
                       Particle *particle) {
  particle->acceleration += (center - particle->position) * force_value;
}

void ApplyRepulsionForceBetweenParticles(const float force_value,
                                         const float min_distance,
                                         const Particle particles[],
                                         size_t number_of_particles,
                                         Particle *particle) {
  for (size_t i = 0; i < number_of_particles; ++i) {
    float2 distance_vector = particle->position - particles[i].position;
    float distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
    if (distance_squared < min_distance * min_distance) {
      if (distance_squared < 1.0f) {
        distance_squared = 1.0f;
      }
      float inverted_distance_squared = 1.0f / distance_squared;
      particle->acceleration += distance_vector * force_value * inverted_distance_squared;
    }
  }
}

void ApplyDampingForce(const float force_value, Particle *particle) {
  particle->velocity *= force_value;
}

void ApplyMotion(Particle *particle) {
  particle->velocity += particle->acceleration;
  particle->position += particle->velocity;
  particle->acceleration = 0.0f;
}

kernel void UpdateParticles(global Particle* input_particles,
                            global Particle* output_particles,
                            global Parameters* parameters,
                            global float2* force_position) {
    const size_t tid = get_global_id(0);
    const size_t number_of_particles = get_global_size(0);

    Particle particle = input_particles[tid];

    ApplyRepulsionForce(parameters->active_repulsion_force,
                        parameters->active_repulsion_min_distance,
                        *force_position,
                        &particle);
    ApplyCentralForce(parameters->center, parameters->central_force, &particle);
    ApplyRepulsionForceBetweenParticles(parameters->passive_repulsion_force,
                                        parameters->passive_repulsion_min_distance,
                                        input_particles,
                                        number_of_particles,
                                        &particle);
    ApplyDampingForce(parameters->damping_force, &particle);
    ApplyMotion(&particle);

    output_particles[tid] = particle;
}
