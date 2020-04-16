//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/brick.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  const int kMaxHealth = 100;
  const int kBrickWidth = 5;
  const int kBrickHeight = 2;

  brick::brick(cinder::vec2 location) {
    loc_ = location;
    health_ = kMaxHealth;
  }

  void brick::update() {
    draw();
  }

  // Below is incorrect
  void brick::draw() {
    cinder::Rectf rect = cinder::Rectf();
    cinder::gl::drawSolidRect(rect, loc_);
  }

}

