//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/platform.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  using namespace cinder;

  platform::platform(vec2 location, int width) {
    loc_ = location;
    width_ = width;
  }

  void BrickBreaker::platform::update() {
    draw();
  }

  void platform::draw() {
    gl::color(0.5f, 0.5f, 0.5f);
    Rectf rect = Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2),
                       loc_.x + (width_ / 2), loc_.y + (height_ / 2));
    gl::drawSolidRoundedRect(rect, 5);
  }

  void platform::ChangeWidth(double width_change_factor) {
    width_ = width_change_factor * width_;
  }

  Rectf platform::GetPlatformBounds() const {
    return Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2),
                 loc_.x + (width_ / 2), loc_.y - (height_ / 2));
  }

  vec2 platform::GetPlatformTopMiddle() const {
    return vec2(loc_.x, loc_.y - kPlatformHeight / 2);
  }

  int platform::GetPlatformWidth() const {
    return width_;
  }

  ci::vec2 platform::GetLocation() const {
    return loc_;
  }

  int platform::GetHeight() const {
    return height_;
  }

  void platform::ChangeLocation(vec2 new_location) {
    loc_ = new_location;
  }


}