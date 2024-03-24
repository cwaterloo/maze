#ifndef MAZE_H_
#define MAZE_H_

namespace maze {

struct Point final {
  int x = 0;
  int y = 0;
  bool operator!=(const Point &other) const {
    return x != other.x || y != other.y;
  }
};

template <typename T> class Maze final {
public:
  explicit Maze(int width, int height) : width_(width), height_(height) {
    data_ = new T[width * height];
    for (int i = 0; i < width_ * height_; ++i) {
      data_[i] = T();
    }
  }
  Maze(const Maze &) = delete;
  Maze<T> operator=(const Maze &) = delete;
  Maze(Maze &&other)
      : data_(other.data_), width_(other.width_), height_(other.height_) {
    other.data_ = nullptr;
  }
  Maze<T> &operator=(Maze &&) = default;
  T &operator[](Point point) { return data_[point.y * width_ + point.x]; }
  const T &operator[](Point point) const {
    return data_[point.y * width_ + point.x];
  }
  ~Maze() {
    if (data_ != nullptr) {
      delete[] data_;
    }
  }
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline int size() const { return width_ * height_; }
  inline const T *get() const { return data_; }

private:
  T *data_;
  const int width_;
  const int height_;
};

} // namespace maze

#endif // MAZE_H_
