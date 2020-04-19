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
    ci::gl::color(0, 1, 0);
    cinder::Rectf rect = cinder::Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2), loc_.x + (width_ / 2), loc_.y + (height_ / 2));
    cinder::gl::drawSolidRect(rect);
  }

  ci::Rectf platform::GetPlatformBounds() {
    return cinder::Rectf(loc_.x - (width_ / 2), loc_.y - (height_ / 2) + 1, loc_.x + (width_ / 2), loc_.y - (height_ / 2) - 1);
  }


}