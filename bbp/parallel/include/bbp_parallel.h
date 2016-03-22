#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

namespace mila {
namespace bbp {
namespace parallel {
class BBP {
 public:
  BBP();

  double precision() const;
 private:
  const double precision_;
};
};  // sequential
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
