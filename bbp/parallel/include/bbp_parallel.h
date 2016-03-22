#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

namespace mila {
namespace bbp {
namespace parallel {
class BBP {
 public:
  BBP();

  float precision() const;
 private:
  const float precision_;
};
};  // sequential
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
