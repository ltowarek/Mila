// CENTER_X passed as a build option
// CENTER_Y passed as a build option
// CENTRAL_FORCE_VALUE passed as a build option
// ACTIVE_REPULSION_FORCE_VALUE passed as a build option
// ACTIVE_REPULSION_FORCE_MIN_DISTANCE passed as a build option
// PASSIVE_REPULSION_FORCE_VALUE passed as a build option
// PASSIVE_REPULSION_FORCE_MIN_DISTANCE passed as a build option
// DAMPING_FORCE_VALUE passed as a build option

typedef struct {
    float2 position;
    float2 velocity;
    float2 acceleration;
} Particle;

Particle ApplyRepulsionForce(global float2 *force_position, Particle particle) {
  Particle output = particle;
  float2 distance_vector = *force_position - particle.position;
  float distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
  if (distance_squared < ACTIVE_REPULSION_FORCE_MIN_DISTANCE * ACTIVE_REPULSION_FORCE_MIN_DISTANCE) {
    float inverted_distance_squared = 1.0f / distance_squared;
    output.acceleration -= distance_vector * ACTIVE_REPULSION_FORCE_VALUE * inverted_distance_squared;
  }
  return output;
}

Particle ApplyCentralForce(Particle particle) {
  Particle output = particle;
  output.acceleration.x += (CENTER_X - output.position.x) * CENTRAL_FORCE_VALUE;
  output.acceleration.y += (CENTER_Y - output.position.y) * CENTRAL_FORCE_VALUE;
  return output;
}

Particle ApplyRepulsionForceBetweenParticles(Particle particle, global Particle *particles, int number_of_particles) {
  Particle output = particle;
  for (size_t i = 0; i < number_of_particles; ++i) {
    float2 distance_vector = particle.position - particles[i].position;
    float distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
    if (distance_squared < PASSIVE_REPULSION_FORCE_MIN_DISTANCE * PASSIVE_REPULSION_FORCE_MIN_DISTANCE) {
      if (distance_squared < 1.0f) {
        distance_squared = 1.0f;
      }
      float inverted_distance_squared = 1.0f / distance_squared;
      output.acceleration += distance_vector * PASSIVE_REPULSION_FORCE_VALUE * inverted_distance_squared;
      particles[i].acceleration -= distance_vector * PASSIVE_REPULSION_FORCE_VALUE * inverted_distance_squared;
    }
  }
  return output;
}

Particle ApplyDampingForce(Particle particle) {
  Particle output = particle;
  output.velocity *= DAMPING_FORCE_VALUE;
  return output;
}

Particle ApplyMotion(Particle particle) {
  Particle output = particle;
  output.velocity += output.acceleration;
  output.position += output.velocity;
  output.acceleration = 0.0f;
  return output;
}

kernel void UpdateParticles(global Particle* input_particles, global Particle* output_particles, global float2* force_position) {
    const int tid = get_global_id(0);
    const int number_of_particles = get_global_size(0);

    Particle particle = input_particles[tid];
    particle = ApplyRepulsionForce(force_position, particle);
    particle = ApplyCentralForce(particle);
    particle = ApplyRepulsionForceBetweenParticles(particle, input_particles, number_of_particles);
    particle = ApplyDampingForce(particle);
    particle = ApplyMotion(particle);

    output_particles[tid] = particle;
}

