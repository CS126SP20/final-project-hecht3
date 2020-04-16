//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/ball.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  ball::ball(cinder::vec2 location) {
    loc_ = location;
  }

  void ball::update() {
    loc_ += dir_ * speed_;
    draw();
  }

  void ball::draw() {
    cinder::gl::drawSolidCircle(loc_, radius_);
  }
}