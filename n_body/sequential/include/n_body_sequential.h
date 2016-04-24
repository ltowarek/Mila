#ifndef MILA_N_BODY_SEQUENTIAL_H_
#define MILA_N_BODY_SEQUENTIAL_H_

#include <cmath>

namespace mila {
namespace nbody {
namespace sequential {

struct Vector2D {
  float x;
  float y;
};

float Distance(Vector2D vector1, Vector2D vector2);

struct Particle {
  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;
};

class NBodySequential {
 public:
  NBodySequential();
  NBodySequential(float precision_);

  float precision() const;
 private:
  const float precision_;
};

}  // sequential
}  // nbody
}  // mila

#endif  // MILA_N_BODY_SEQUENTIAL_H_
