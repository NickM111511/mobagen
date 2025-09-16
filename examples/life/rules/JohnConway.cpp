#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int maxSize = world.SideSize();
  int neighborCount[maxSize][maxSize];

  for (int i = 0; i < maxSize; i++) {
    for (int j = 0; j < maxSize; j++) {
      neighborCount[i][j] = 0;
    }
  }

  for (int line = 0; line < maxSize; line++) {
    for (int column = 0; column < maxSize; column++) {
      Point2D currentTile(line, column);

      if (world.Get(currentTile) == true) {
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
              Point2D checkTile(line + i, column + j);
              if (line + i < 0) {
                if (column + j < 0) {
                  neighborCount[maxSize - 1][maxSize - 1] += 1; //CountNeighbors(world, checkTile);
                } else {
                  neighborCount[maxSize - 1][(column + j) % maxSize] += 1; //CountNeighbors(world, checkTile);
                }
              }
              else if (column + j < 0) {
                neighborCount[(maxSize + j) % maxSize][maxSize - 1] += 1; //CountNeighbors(world, checkTile);
              }
              else {
                neighborCount[(maxSize + j) % maxSize][(column + j) % maxSize] += 1; //CountNeighbors(world, checkTile);
              }
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < maxSize; i++) {
    for (int j = 0; j < maxSize; j++) {
      if (neighborCount[i][j] == 0 || neighborCount[i][j] == 1) {
        world.SetNext(Point2D(i, j), false);
      }
      else if (neighborCount[i][j] == 2) {
        continue;
      }
      else if (neighborCount[i][j] == 3) {
        world.SetNext(Point2D(i, j), true);
      }
      else {
        world.SetNext(Point2D(i, j), false);
      }
    }
  }

  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  return 1;
}
