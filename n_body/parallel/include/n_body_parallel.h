#ifndef MILA_N_BODY_PARALLEL_H_
#define MILA_N_BODY_PARALLEL_H_

#include "clpp.h"

namespace mila {
namespace nbody {
namespace parallel {

struct Particle {
  cl_float2 position;
  cl_float2 velocity;
  cl_float2 acceleration;
};

}  // parallel
}  // nbody
}  // mila

#endif  // MILA_N_BODY_PARALLEL_H_
