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
    // Level 0
    for (double i = 0; i < 10; i+=1.5) {
      for (int j = 0; j < 10; j+=2) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 1
    bricks.clear();
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j+=2) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        int health;
        if (i % 2 == 0) {
          health = kDefaultBrickHealth * 2;
        } else {
          health = kDefaultBrickHealth;
        }
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        health);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 2
    bricks.clear();
    for (int i = 0; i < 10; i++) {
      for (double j = 0; j < 10; j+=1.5) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        int health;
        if (i % 3 == 0) {
          health = kDefaultBrickHealth * 3;
        } else if (i % 3 == 1) {
          health = kDefaultBrickHealth / 2;
        } else {
          health = kDefaultBrickHealth * 2;
        }
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        health);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 3
    bricks.clear();
    for (int i = 0; i < 10; i++) {
      for (double j = 0; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset + kDefaultBrickHeight) + kWallOffset);
        int health;
        if (i % 3 == 0) {
          health = kDefaultBrickHealth * 2;
        } else if (i % 3 == 1) {
          health = kDefaultBrickHealth / 2;
        } else {
          health = kDefaultBrickHealth * 2;
        }
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        health);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);

    // Level 4
    bricks.clear();
    for (int i = 0; i < 12; i++) {
      for (double j = 0; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kDefaultBrickWidth) + kWallOffset,
          j * (kBrickOffset / 2 + kDefaultBrickHeight) + kWallOffset);
        int health;
        if (j == 9) {
          health = kDefaultBrickHealth * 3;
        } else {
          health = kDefaultBrickHealth;
        }
        BrickBreaker::brick brick = BrickBreaker::brick(location,
                                                        health);
        bricks.push_back(brick);
      }
    }
    levels_vec.push_back(bricks);
    return levels_vec;
  }
}