//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/platform.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  using namespace cinder;

  platform::platform(vec2 location) {
    loc_ = location;
    speed_ = 0;
    width_ = kDefaultPlatformWidth;
    draw();
  }

  void BrickBreaker::platform::update() {
    draw();
  }

  void platform::draw() {
    gl::color(0.5f, 0.5f, 0.5f);
    Rectf rect = Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2), loc_.x + (width_ / 2), loc_.y + (height_ / 2));
    gl::drawSolidRoundedRect(rect, 5);
  }

  Rectf platform::GetPlatformBounds() {
    return Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2) + 1, loc_.x + (width_ / 2), loc_.y - (height_ / 2) - 1);
  }

  vec2 platform::GetPlatformTopMiddle() {
    return vec2(loc_.x, loc_.y - kPlatformHeight / 2);
  }

  int platform::GetPlatformWidth() {
    return width_;
  }

  void platform::ChangeWidth(double width_change_factor) {
    width_ = width_change_factor * width_;
  }


}