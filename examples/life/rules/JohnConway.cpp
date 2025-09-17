#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  // setting variables
  int maxSize = world.SideSize();
  std::vector<int> neighborCount;
  neighborCount.resize((maxSize * maxSize));

  // iterating over each tile
  for (int line = 0; line < maxSize; line++) {
    for (int column = 0; column < maxSize; column++) {
      // if tile is alive
      if (world.Get(Point2D(column, line)) == true) {
        // iterate over neighboring tiles
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            // exclude own tile
            if (i != 0 || j != 0) {
              Point2D neighborCheck(line + i, column + j);
              if (neighborCheck.x < 0) { // row index needs too low, wrap
                neighborCheck.x += maxSize;
              }
              if (neighborCheck.x >= maxSize) { // row index too high, wrap
                neighborCheck.x %= maxSize;
              }
              if (neighborCheck.y < 0) { // column index too low, wrap
                neighborCheck.y += maxSize;
              }
              if (neighborCheck.y >= maxSize) { // column index too high, wrap
                neighborCheck.y %= maxSize;
              }
              // get tilePosition and wrap if it goes past vector index
              int index = (neighborCheck.x * maxSize) + neighborCheck.y;
              int maxIndex = maxSize * maxSize;
              if(index >= maxIndex) {
                index %= maxIndex;
              }
              // count neighbor at the index
              neighborCount[index] += CountNeighbors(world, Point2D(neighborCheck.x, neighborCheck.y));
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < maxSize; i++) {
    for (int j = 0; j < maxSize; j++) {
      if (neighborCount[(i * maxSize) + j] == 0 || neighborCount[(i * maxSize) + j] == 1) {
        world.SetNext(Point2D(j, i), false);
      }
      else if (neighborCount[(i * maxSize) + j] == 2) {
        if(world.Get(Point2D(j,i)) == true) {
          world.SetNext(Point2D(j, i), true);
        }
        else {
          world.SetNext(Point2D(j, i), false);
        }
      }
      else if (neighborCount[(i * maxSize) + j] == 3) {
        world.SetNext(Point2D(j, i), true);
      }
      else {
        world.SetNext(Point2D(j, i), false);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  return 1;
}
