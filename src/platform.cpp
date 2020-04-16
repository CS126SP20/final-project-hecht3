//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/platform.h>

namespace BrickBreaker {

  const int kDefaultPlatformSize = 5;

  platform::platform(cinder::vec2 location) {
    loc_ = location;
    speed_ = 0;
    size_ = kDefaultPlatformSize;
  }

  void BrickBreaker::platform::update() {
    draw();
  }

  void platform::draw() {

  }

}