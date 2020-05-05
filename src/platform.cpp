//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/platform.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  platform::platform(cinder::vec2 location) {
    loc_ = location;
    speed_ = 0;
    width_ = kDefaultPlatformWidth;
    draw();
  }

  void BrickBreaker::platform::update() {
    draw();
  }

  void platform::draw() {
    ci::gl::color(0.5f, 0.5f, 0.5f);
    cinder::Rectf rect = cinder::Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2), loc_.x + (width_ / 2), loc_.y + (height_ / 2));
    cinder::gl::drawSolidRoundedRect(rect, 5);
  }

  ci::Rectf platform::GetPlatformBounds() {
    return cinder::Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2) + 1, loc_.x + (width_ / 2), loc_.y - (height_ / 2) - 1);
  }

  cinder::vec2 platform::GetPlatformTopMiddle() {
    return ci::vec2(loc_.x, loc_.y - kPlatformHeight / 2);
  }

  int platform::GetPlatformWidth() {
    return width_;
  }

  void platform::IncreaseWidth(double width_increase_factor) {
    width_ = width_increase_factor * width_;
  }


}