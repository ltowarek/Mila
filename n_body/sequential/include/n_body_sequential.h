#ifndef MILA_N_BODY_SEQUENTIAL_H_
#define MILA_N_BODY_SEQUENTIAL_H_

namespace mila {
namespace nbody {
namespace sequential {

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
