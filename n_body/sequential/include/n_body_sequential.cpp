#include "n_body_sequential.h"

mila::nbody::sequential::NBodySequential::NBodySequential(): NBodySequential(1e-5) {
}

mila::nbody::sequential::NBodySequential::NBodySequential(float precision_): precision_(precision_) {
}

float mila::nbody::sequential::NBodySequential::precision() const {
  return precision_;
}
