//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/ball.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  ball::ball(cinder::vec2 location, double speed, double dir) {
    loc_ = location;
    radius_ = kDefaultBallRadius;
    speed_ = speed;
    dir_ = dir;
    draw();
  }

  void ball::update() {
    loc_ += dir_ * speed_;
    draw();
  }

  void ball::draw() {
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawSolidCircle(loc_, radius_);
  }
}