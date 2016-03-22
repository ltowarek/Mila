#include "bbp_parallel.h"

mila::bbp::parallel::BBP::BBP() : precision_(1e-5f) {
}

float mila::bbp::parallel::BBP::precision() const {
  return precision_;
}
