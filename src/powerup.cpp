//
// Created by connell on 4/29/20.
//

#include <BrickBreaker/powerup.h>

namespace BrickBreaker {
  using namespace cinder;

  powerup::powerup(vec2 location, double speed) {
    loc_ = location;
    speed_ = speed;
    size_ = kPowerupSize;
    type_ = powerup_type(rand() % kPowerupNumTypes);
    dir_ = vec2(0, 1 / sqrt(2));
  }

  void powerup::update() {
    // Adjust location according to velocity
    loc_.x += dir_.x * speed_;
    loc_.y += dir_.y * speed_;
    draw();
  }

  void powerup::draw() {
    if (type_ == BALL) {
      gl::color(0, 0, 0);
    } else if (type_ == PLATFORM) {
      gl::color(0.5f, 0.5f, 0.5f);
    }
    Rectf rect = Rectf(loc_.x, loc_.y, loc_.x + size_, loc_.y + size_);
    gl::drawSolidRect(rect);
  }

  powerup_type powerup::GetType() const {
    return type_;
  }

  ci::vec2 powerup::GetLocation() const {
    return loc_;
  }
}
