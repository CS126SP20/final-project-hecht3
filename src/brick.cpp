//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/brick.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  brick::brick(cinder::vec2 location) {
    loc_ = location;
    health_ = kMaxHealth;
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

}

