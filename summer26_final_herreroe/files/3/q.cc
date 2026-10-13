#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

using Cell = std::pair<int, int>;

int BfsShortestDistance(const std::vector<std::vector<char>> &grid, Cell start,
                         Cell target) {
  const int rows = static_cast<int>(grid.size());

  // visited[r][c] doubles as the check so we don't revisit cells and blow up the queue
  std::vector<std::vector<bool>> visited(rows);
  for (int r = 0; r < rows; ++r) {
    visited[r].assign(grid[r].size(), false);
  }

  std::queue<std::pair<Cell, int>> toVisit;  // (cell, distance from start)
  toVisit.push({start, 0});
  visited[start.first][start.second] = true;

  // Standard up/down/left/right moves
  const int dRow[] = {-1, 1, 0, 0};
  const int dCol[] = {0, 0, -1, 1};

  while (!toVisit.empty()) {
    auto [cell, dist] = toVisit.front();
    toVisit.pop();

    if (cell == target) {
      return dist;
    }

    for (int dir = 0; dir < 4; ++dir) {
      int nr = cell.first + dRow[dir];
      int nc = cell.second + dCol[dir];

      // Bounds check first (rows can even have different widths if the
      // grid is jagged, so we check against that row's actual size)
      if (nr < 0 || nr >= rows) continue;
      if (nc < 0 || nc >= static_cast<int>(grid[nr].size())) continue;

      if (visited[nr][nc]) continue;
      if (grid[nr][nc] == '1') continue;  // Blocked

      visited[nr][nc] = true;
      toVisit.push({{nr, nc}, dist + 1});
    }
  }

  // Ran out of places to explore and never hit the target
  return -1;
}

}

int fastestToTarget(std::vector<std::vector<char>> &grid) {
  // Nothing on the grid at all
  if (grid.empty()) {
    return -1;
  }

  // Track whether we actually found each marker, since a malformed grid
  // shouldn't cause to read garbage coordinates
  bool foundY = false, foundF = false, foundT = false;
  Cell you{}, friendPos{}, target{};

  for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
    for (int c = 0; c < static_cast<int>(grid[r].size()); ++c) {
      switch (grid[r][c]) {
        case 'y':
          you = {r, c};
          foundY = true;
          break;
        case 'f':
          friendPos = {r, c};
          foundF = true;
          break;
        case 't':
          target = {r, c};
          foundT = true;
          break;
        default:
          break;  // 0 or 1
      }
    }
  }

  // Grid didn't have everything it needed so nothing sensible to compute
  if (!foundY || !foundF || !foundT) {
    return -1;
  }

  int yourDistance = BfsShortestDistance(grid, you, target);
  int friendDistance = BfsShortestDistance(grid, friendPos, target);

  // Neither of you can get there -> the only case that's truly -1
  if (yourDistance == -1 && friendDistance == -1) {
    return -1;
  }

  if (yourDistance == -1) return 2;    // You can't reach it, friend can
  if (friendDistance == -1) return 1;  // Friend can't reach it, you can

  if (yourDistance < friendDistance) return 1;
  if (friendDistance < yourDistance) return 2;
  return 3;  // Exact tie
}