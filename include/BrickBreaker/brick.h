//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

#include <cinder/app/App.h>

const int kBrickWidth = 50;
const int kBrickHeight = 20;
const int kDefaultBrickHealth = 100;

namespace BrickBreaker {

  const int kMaxHealth = 1000;

  class brick {
  public:
    cinder::vec2 loc_;
    int health_;
    bool has_powerup_;

    brick(cinder::vec2 location, int health);
    void update();
    void draw();
    ci::vec2 GetUpperLeftCorner();
    ci::vec2 GetUpperRightCorner();
    ci::vec2 GetLowerLeftCorner();
    ci::vec2 GetLowerRightCorner();
  };
}


#endif //FINALPROJECT_BLOCK_H
