#ifndef DUAL_VALUE_H_
#define DUAL_VALUE_H_

#include <compare>

namespace maze {

class DualValue final {
public:
  explicit DualValue(int a, int b);
  DualValue(const DualValue &) = default;
  DualValue &operator=(const DualValue &) = default;
  DualValue(DualValue &&) = default;
  DualValue &operator=(DualValue &&) = default;
  DualValue operator+(const DualValue &other) const;
  std::strong_ordering operator<=>(const DualValue &other) const;
  bool operator==(const DualValue &other) const = default;
  bool operator!=(const DualValue &other) const = default;
  bool operator>(const DualValue &other) const = default;
  bool operator<(const DualValue &other) const = default;
  bool operator>=(const DualValue &other) const = default;
  bool operator<=(const DualValue &other) const = default;

  static DualValue SqrtOfTwo();
  static DualValue One();
  static DualValue Zero();

private:
  int a_;
  int b_;
};

} // namespace maze

#endif // DUAL_VALUE_H_
