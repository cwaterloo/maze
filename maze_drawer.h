#ifndef MAZE_DRAWER_H_
#define MAZE_DRAWER_H_

#include <vector>

#include "maze.h"

namespace maze {

enum class PointType { kEmpty, kWall, kStart, kStop, kPath };

Maze<int> DrawMaze(const Maze<PointType> &maze, int dpc);

} // namespace maze

#endif // MAZE_DRAWER_H_
