#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
    // check if search has started
    Random random;
    int tileFactor = (w->GetSize()/2);
    int randomNumber = 0;

    if(stack.empty() && !visited[0][0]) {
        stack.emplace_back(0,0);
      visited[0 - tileFactor][0 - tileFactor] = true;
      w->SetNodeColor(Point2D(0 - tileFactor,0 - tileFactor), Color32(255,3,3));
    }

    std::vector<Point2D> nearbyNeighbors = getVisitables(w, stack.back());
    std::vector<Point2D> sortedNeighbors = nearbyNeighbors;

    for(int i = 0; i < nearbyNeighbors.size(); i++) {
        if(nearbyNeighbors[0].y > stack.back().y) {
            sortedNeighbors.push_back(nearbyNeighbors[i]);
        }
    }
    for(int i = 0; i < nearbyNeighbors.size(); i++) {
        if(nearbyNeighbors[0].x < stack.back().x) {
            sortedNeighbors.push_back(nearbyNeighbors[i]);
        }
    }
    for(int i = 0; i < nearbyNeighbors.size(); i++) {
        if(nearbyNeighbors[0].y < stack.back().y) {
            sortedNeighbors.push_back(nearbyNeighbors[i]);
        }
    }
    for(int i = 0; i < nearbyNeighbors.size(); i++) {
        if(nearbyNeighbors[0].x > stack.back().x) {
            sortedNeighbors.push_back(nearbyNeighbors[i]);
        }
    }

    if(!nearbyNeighbors.empty()) {
        randomNumber = random.Range(0,100) % nearbyNeighbors.size();
    }


  if (nearbyNeighbors.size() > 1) { // more than one neighbor, randomly add one
    visited[sortedNeighbors[randomNumber].x - tileFactor][sortedNeighbors[randomNumber].y - tileFactor] = true;
    w->SetNodeColor(Point2D(sortedNeighbors[randomNumber].x - tileFactor,sortedNeighbors[randomNumber].y - tileFactor), Color32(255,3,3));

    if(sortedNeighbors[randomNumber].y > stack.back().y) {
        w->SetNorth(Point2D(sortedNeighbors[randomNumber].x - tileFactor,sortedNeighbors[randomNumber].y - tileFactor), false);
    }
    if(sortedNeighbors[randomNumber].x < stack.back().x) {
        w->SetEast(Point2D(sortedNeighbors[randomNumber].x - tileFactor,sortedNeighbors[randomNumber].y - tileFactor), false);
    }
    if(sortedNeighbors[randomNumber].y < stack.back().y) {
        w->SetSouth(Point2D(sortedNeighbors[randomNumber].x - tileFactor,sortedNeighbors[randomNumber].y - tileFactor), false);
    }
    if(sortedNeighbors[randomNumber].x > stack.back().x) {
        w->SetWest(Point2D(sortedNeighbors[randomNumber].x - tileFactor,sortedNeighbors[randomNumber].y - tileFactor), false);
    }
      stack.push_back(sortedNeighbors[randomNumber]);
  }
  else if (nearbyNeighbors.size() == 1) { // add the one neighbor
    visited[nearbyNeighbors[0].x - tileFactor][nearbyNeighbors[0].y - tileFactor] = true;
    w->SetNodeColor(Point2D(nearbyNeighbors[0].x - tileFactor,nearbyNeighbors[0].y - tileFactor), Color32(255,3,3));
    if(nearbyNeighbors[0].y > stack.back().y) {
        w->SetNorth(Point2D(nearbyNeighbors[0].x - tileFactor,nearbyNeighbors[0].y - tileFactor), false);
    }
    if(nearbyNeighbors[0].x < stack.back().x) {
        w->SetEast(Point2D(nearbyNeighbors[0].x - tileFactor,nearbyNeighbors[0].y - tileFactor), false);
    }
    if(nearbyNeighbors[0].y < stack.back().y) {
        w->SetSouth(Point2D(nearbyNeighbors[0].x - tileFactor,nearbyNeighbors[0].y - tileFactor), false);
    }
    if(nearbyNeighbors[0].x > stack.back().x) {
        w->SetWest(Point2D(nearbyNeighbors[0].x - tileFactor,nearbyNeighbors[0].y - tileFactor), false);
    }
    stack.push_back(nearbyNeighbors[0]);
  } else { // no neighbors, start to backtrack
      if(stack.empty()) {
          return false;
      }
      Point2D cellLocation = stack.back();
      w->SetNodeColor(Point2D(cellLocation.x - tileFactor,cellLocation.y - tileFactor), Color32(0,0,0));
      stack.pop_back();
  }

  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if((i == 0 && j == 0) || (i == 1 && j == 1) || (i == -1 && j == 1) || (i == 1 && j == -1) || (i == -1 && j == -1)) { // makes sure it does not include itself as neighbor
        continue;
      } else { // checks if any of the neighbors would be out of bounds.
        if(p.x + j >= 0 && p.x + j <= w->GetSize()-1 && p.y + i >= 0 && p.y + i <= w->GetSize()-1) {
          if(visited[(p.x + j - sideOver2)][(p.y + i - sideOver2)]) {
            continue;
          } else {
            visitables.emplace_back(p.x + j, p.y + i);
          }
        }
      }
    }
  }

  return visitables;
}
