#include <iostream>

#include <utility>

#include "cell.h"
#include "maze.h"
#include "maze_drawer.h"
#include "path_finder.h"

namespace maze {
namespace {

struct MazeDefinition final {
  Maze<Cell> maze;
  Point start;
  Point stop;
};

void InitRandomizer() {
  time_t t;
  time(&t);
  srand(t);
}

MazeDefinition GetRandomMaze() {
  Maze<Cell> maze(112, 63);
  for (int i = 0; i < maze.width(); ++i) {
    maze[{.x = i, .y = 0}] = Cell::kWall;
    maze[{.x = i, .y = maze.height() - 1}] = Cell::kWall;
  }
  for (int i = 0; i < maze.height(); ++i) {
    maze[{.x = 0, .y = i}] = Cell::kWall;
    maze[{.x = maze.width() - 1, .y = i}] = Cell::kWall;
  }
  int empty_cell_count = 0;
  Point start;
  Point stop;
  for (int i = 1; i < maze.width() - 1; ++i) {
    for (int j = 1; j < maze.height() - 1; ++j) {
      Point current = {.x = i, .y = j};
      maze[current] = rand() % 2 == 0 ? Cell::kEmpty : Cell::kWall;

      if (maze[current] != Cell::kEmpty) {
        continue;
      }

      ++empty_cell_count;

      if (rand() % empty_cell_count == 0) {
        start = current;
      }

      if (rand() % empty_cell_count == 0) {
        stop = current;
      }
    }
  }
  return {.maze = std::move(maze), .start = start, .stop = stop};
}

Maze<PointType> GetMazeWithPath(const MazeDefinition &maze_def) {
  Maze<PointType> maze(maze_def.maze.width(), maze_def.maze.height());
  for (int i = 0; i < maze_def.maze.width(); ++i) {
    for (int j = 0; j < maze_def.maze.height(); ++j) {
      Point at = {.x = i, .y = j};
      switch (maze_def.maze[at]) {
      case Cell::kEmpty:
        maze[at] = PointType::kEmpty;
        break;
      case Cell::kWall:
        maze[at] = PointType::kWall;
        break;
      }
    }
  }

  for (Point at :
       PathFinder::GetShortest(maze_def.start, maze_def.stop, maze_def.maze)) {
    maze[at] = PointType::kPath;
  }

  maze[maze_def.start] = PointType::kStart;
  maze[maze_def.stop] = PointType::kStop;

  return maze;
}

void PrintCanvas(const Maze<int> &picture) {
  std::cerr << picture.width() << "x" << picture.height() << "\n";
  int buffer_size = picture.size() * sizeof(int);
  char *buffer = new char[buffer_size];
  for (int i = 0; i < picture.size(); ++i) {
    int value = picture.get()[i];
    buffer[i * 4] = static_cast<char>((value & 0xFF000000) >> 24);
    buffer[i * 4 + 1] = static_cast<char>((value & 0x00FF0000) >> 16);
    buffer[i * 4 + 2] = static_cast<char>((value & 0x0000FF00) >> 8);
    buffer[i * 4 + 3] = static_cast<char>(value & 0x000000FF);
  }
  std::cout.write(buffer, buffer_size);
}

} // namespace

void Run() {
  InitRandomizer();
  PrintCanvas(DrawMaze(GetMazeWithPath(GetRandomMaze()), 64));
}

} // namespace maze

int main() {
  maze::Run();
  return 0;
}
