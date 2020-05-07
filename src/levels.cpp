//
// Created by connell on 5/4/20.
//

#include <BrickBreaker/levels.h>

const int kBrickOffset = 30;
const int kWallOffset = 15;

namespace BrickBreaker {
  std::vector<std::vector<BrickBreaker::brick>> levels::GenerateLevels() {
    std::vector<std::vector<BrickBreaker::brick>> levels_vec;
    std::vector <BrickBreaker::brick> bricks;
    // Level 1
    for (int i = 0; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 2
    bricks.clear();
    for (int i = 8; i < 10; i++) {
      for (int j = 8; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 3
    bricks.clear();
    for (int i = 5; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 4
    bricks.clear();
    for (int i = 5; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);
    return levels_vec;
  }
}