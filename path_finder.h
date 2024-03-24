#ifndef PATH_FINDER_H_
#define PATH_FINDER_H_

#include <functional>
#include <optional>
#include <queue>
#include <vector>

#include "cell.h"
#include "dual_value.h"
#include "maze.h"

namespace maze {

class PathFinder final {
public:
  static std::vector<Point> GetShortest(Point start, Point stop,
                                        const Maze<Cell> &maze);

private:
  explicit PathFinder(const Maze<Cell> &maze, Point start, Point stop);

  struct PointWithDistance final {
    Point point;
    DualValue distance = DualValue::Zero();
    bool operator>(const PointWithDistance &other) const {
      return distance > other.distance;
    }
  };

  struct Label final {
    std::optional<DualValue> distance = std::nullopt;
    Point from;
  };

  void LookInto(Point from, Point to, DualValue distance_between);
  void LookAround(Point point);
  std::vector<Point> RestorePath();
  std::vector<Point> GetShortest();

  const Maze<Cell> &maze_;
  Maze<Label> labels_;
  Point start_;
  Point stop_;
  std::priority_queue<PointWithDistance, std::vector<PointWithDistance>,
                      std::greater<PointWithDistance>>
      queue_;
};

} // namespace maze

#endif // PATH_FINDER_H_
