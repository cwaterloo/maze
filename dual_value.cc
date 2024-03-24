#include "dual_value.h"

#include <compare>
#include <cstdint>

namespace maze {
namespace {

inline int Sign(int64_t value) { return (value > 0) - (value < 0); }

inline uint64_t Sqr(int64_t value) { return value * value; }

inline int64_t Diff(int64_t from, int64_t to) { return from - to; }

int CompareToZero(int64_t a, int64_t b) {
  int sa = Sign(a);
  int sb = Sign(b);

  if (sa == 0 || sb == 0) {
    return sa + sb;
  }

  if (sa == sb) {
    return sa;
  }

  uint64_t sqr_a = Sqr(a);
  uint64_t sqr_b = Sqr(b);

  return sb * (((sqr_a < sqr_b || sqr_a - sqr_b < sqr_b) * 2) - 1);
}

} // namespace

DualValue::DualValue(int a, int b) : a_(a), b_(b) {}

DualValue DualValue::operator+(const DualValue &other) const {
  return DualValue(a_ + other.a_, b_ + other.b_);
}

std::strong_ordering DualValue::operator<=>(const DualValue &other) const {
  switch (CompareToZero(Diff(this->a_, other.a_), Diff(this->b_, other.b_))) {
  case -1:
    return std::strong_ordering::less;
  case 0:
    return std::strong_ordering::equal;
  default:
    return std::strong_ordering::greater;
  }
}

DualValue DualValue::SqrtOfTwo() { return DualValue(0, 1); }

DualValue DualValue::One() { return DualValue(1, 0); }

DualValue DualValue::Zero() { return DualValue(0, 0); }

} // namespace maze
