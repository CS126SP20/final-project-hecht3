//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/brick.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  brick::brick(cinder::vec2 location, int health) {
    loc_ = location;
    if (health < kMaxHealth) {
      health_ = health;
    } else {
      health_ = kDefaultBrickHealth;
    }
    draw();
  }

  void brick::update() {
    if (health_ > 0) {
      draw();
    }
  }

  // Below is incorrect
  void brick::draw() {
    ci::gl::color(0, 0, 1);
    cinder::Rectf rect = cinder::Rectf(loc_.x, loc_.y, loc_.x + kBrickWidth, loc_.y + kBrickHeight);
    cinder::gl::drawSolidRect(rect);
  }

  ci::vec2 brick::GetUpperLeftCorner() {
    return loc_;
  }

  ci::vec2 brick::GetUpperRightCorner() {
    return ci::vec2(loc_.x + kBrickWidth, loc_.y);
  }

  ci::vec2 brick::GetLowerLeftCorner() {
    return ci::vec2(loc_.x, loc_.y + kBrickHeight);
  }

  ci::vec2 brick::GetLowerRightCorner() {
    return ci::vec2(loc_.x + kBrickWidth, loc_.y + kBrickHeight);
  }
}

