#include "maze_drawer.h"

#include <cstdint>

#include <math.h>

namespace maze {

namespace {

constexpr int kBlack = 0x000000FF;
constexpr int kGrey = 0xC0C0C0FF;
constexpr int kGreen = 0x00FF00FF;
constexpr int kYellow = 0xFFFF00FF;
constexpr int kAqua = 0x00FFFFFF;
const double kPathRadiusFactor = sqrt(2) - 1;

inline double Sqr(double value) { return value * value; }

struct Circles final {
  Maze<int> wall_circle;
  Maze<int> stop_circle;
  Maze<int> start_circle;
  Maze<int> path_circle;
};

Maze<int> MakeCircle(int dpc, int color, double factor = 1.0) {
  Maze<int> circle(dpc, dpc);
  double half_dpc = dpc / 2.0;

  for (int i = 0; i < circle.width(); ++i) {
    for (int j = 0; j < circle.height(); ++j) {
      circle[{.x = i, .y = j}] =
          Sqr(i - half_dpc) + Sqr(j - half_dpc) < Sqr(half_dpc * factor)
              ? color
              : kBlack;
    }
  }

  return circle;
}

void DrawEmpty(Maze<int> &canvas, int dpc, Point at) {
  for (int i = 0; i < dpc; ++i) {
    for (int j = 0; j < dpc; ++j) {
      canvas[{.x = at.x + i, .y = at.y + j}] = kBlack;
    }
  }
}

void DrawRectangle(Maze<int> &canvas, Point at, Point left_top,
                   Point right_bottom) {
  for (int i = left_top.x; i < right_bottom.x; ++i) {
    for (int j = left_top.y; j < right_bottom.y; ++j) {
      canvas[{.x = at.x + i, .y = at.y + j}] = kGrey;
    }
  }
}

void DrawPicture(Maze<int> &canvas, const Maze<int> &src, Point at) {
  for (int i = 0; i < src.width(); ++i) {
    for (int j = 0; j < src.height(); ++j) {
      canvas[{.x = at.x + i, .y = at.y + j}] = src[{.x = i, .y = j}];
    }
  }
}

void DrawCell(Maze<int> &canvas, const Maze<PointType> &maze, Point maze_cell,
              const Circles &circles, int dpc) {
  Point at = {.x = maze_cell.x * dpc, .y = maze_cell.y * dpc};
  switch (maze[maze_cell]) {
  case PointType::kEmpty:
    DrawEmpty(canvas, dpc, at);
    break;
  case PointType::kPath:
    DrawPicture(canvas, circles.path_circle, at);
    break;
  case PointType::kStart:
    DrawPicture(canvas, circles.start_circle, at);
    break;
  case PointType::kStop:
    DrawPicture(canvas, circles.stop_circle, at);
    break;
  case PointType::kWall:
    DrawPicture(canvas, circles.wall_circle, at);
    if (maze_cell.x <= 0 ||
        maze[{.x = maze_cell.x - 1, .y = maze_cell.y}] == PointType::kWall) {
      DrawRectangle(canvas, at, {.x = 0, .y = 0}, {.x = dpc / 2, .y = dpc});
    }

    if (maze_cell.x >= maze.width() - 1 ||
        maze[{.x = maze_cell.x + 1, .y = maze_cell.y}] == PointType::kWall) {
      DrawRectangle(canvas, at, {.x = dpc / 2, .y = 0}, {.x = dpc, .y = dpc});
    }

    if (maze_cell.y <= 0 ||
        maze[{.x = maze_cell.x, .y = maze_cell.y - 1}] == PointType::kWall) {
      DrawRectangle(canvas, at, {.x = 0, .y = 0}, {.x = dpc, .y = dpc / 2});
    }

    if (maze_cell.y >= maze.height() - 1 ||
        maze[{.x = maze_cell.x, .y = maze_cell.y + 1}] == PointType::kWall) {
      DrawRectangle(canvas, at, {.x = 0, .y = dpc / 2}, {.x = dpc, .y = dpc});
    }
    break;
  }
}

} // namespace

Maze<int> DrawMaze(const Maze<PointType> &maze, int dpc) {
  Circles circles = {.wall_circle = MakeCircle(dpc, kGrey),
                     .stop_circle = MakeCircle(dpc, kAqua, kPathRadiusFactor),
                     .start_circle =
                         MakeCircle(dpc, kYellow, kPathRadiusFactor),
                     .path_circle = MakeCircle(dpc, kGreen, kPathRadiusFactor)};
  Maze<int> canvas(maze.width() * dpc, maze.height() * dpc);

  for (int i = 0; i < maze.width(); ++i) {
    for (int j = 0; j < maze.height(); ++j) {
      DrawCell(canvas, maze, {.x = i, .y = j}, circles, dpc);
    }
  }

  return canvas;
}

} // namespace maze
