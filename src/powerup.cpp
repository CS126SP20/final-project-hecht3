//
// Created by connell on 4/29/20.
//

#include <BrickBreaker/powerup.h>

namespace BrickBreaker {

  powerup::powerup(ci::vec2 location, double speed) {
    loc_ = location;
    speed_ = speed;
    size_ = kPowerupSize;
    type_ = powerup_type(rand() % kPowerupNumTypes);
  }

  void powerup::update() {
    // Adjust location according to velocity
    loc_.x += dir_.x * speed_;
    loc_.y += dir_.y * speed_;
    draw();
  }

  void powerup::draw() {
    ci::gl::color(1, 0, 0);
    cinder::Rectf rect = cinder::Rectf(loc_.x, loc_.y, loc_.x + size_, loc_.y + size_);
    cinder::gl::drawSolidRect(rect);
  }
}
