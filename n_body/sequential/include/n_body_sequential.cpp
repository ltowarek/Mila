#include "n_body_sequential.h"

float ::mila::nbody::sequential::Distance(mila::nbody::sequential::Vector2D vector1,
                                          mila::nbody::sequential::Vector2D vector2) {
  return sqrtf(powf(vector1.x - vector2.x, 2.0f) + powf(vector1.y - vector2.y, 2.0f));
}

mila::nbody::sequential::NBodySequential::NBodySequential(): NBodySequential(1e-5) {
}

mila::nbody::sequential::NBodySequential::NBodySequential(float precision_): precision_(precision_) {
}

float mila::nbody::sequential::NBodySequential::precision() const {
  return precision_;
}
