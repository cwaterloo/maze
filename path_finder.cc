#include "path_finder.h"

#include <optional>
#include <queue>
#include <vector>

#include "cell.h"
#include "dual_value.h"
#include "maze.h"

namespace maze {

PathFinder::PathFinder(const Maze<Cell> &maze, Point start, Point stop)
    : maze_(maze), labels_(maze.width(), maze.height()), start_(start),
      stop_(stop) {}

void PathFinder::LookInto(Point from, Point to, DualValue distance_between) {
  if (to.x < 0 || to.y < 0 || to.x >= maze_.width() || to.y >= maze_.height() ||
      maze_[to] != Cell::kEmpty) {
    return;
  }

  DualValue distance = *labels_[from].distance + distance_between;

  if (!labels_[to].distance.has_value() || *labels_[to].distance > distance) {
    labels_[to].distance = distance;
    labels_[to].from = from;
    queue_.push({.point = to, .distance = distance});
  }
}

void PathFinder::LookAround(Point point) {
  for (int i : {-1, 1}) {
    for (int j : {-1, 1}) {
      LookInto(point, {.x = point.x + i, .y = point.y + j},
               DualValue::SqrtOfTwo());
      LookInto(point, {.x = point.x + (i - j) / 2, .y = point.y + (i + j) / 2},
               DualValue::One());
    }
  }
}

std::vector<Point> PathFinder::RestorePath() {
  if (!labels_[start_].distance.has_value()) {
    return {};
  }

  std::vector<Point> path;
  Point point = start_;

  while (point != stop_) {
    path.push_back(point);
    point = labels_[point].from;
  }

  path.push_back(point);
  return path;
}

std::vector<Point> PathFinder::GetShortest(Point start, Point stop,
                                           const Maze<Cell> &maze) {
  return PathFinder(maze, start, stop).GetShortest();
}

std::vector<Point> PathFinder::GetShortest() {
  labels_[stop_].distance = DualValue::Zero();
  labels_[stop_].from = stop_;
  queue_.push({.point = stop_, .distance = DualValue::Zero()});

  while (!queue_.empty()) {
    PointWithDistance item = queue_.top();
    queue_.pop();
    if (*labels_[item.point].distance == item.distance) {
      LookAround(item.point);
    }
  }

  return RestorePath();
}

} // namespace maze
