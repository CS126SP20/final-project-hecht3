//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_PLATFORM_H
#define FINALPROJECT_PLATFORM_H

#include <cinder/app/App.h>

const int kDefaultPlatformWidth = 100;
const int kPlatformHeight = 10;

namespace BrickBreaker {
  class platform {
  public:
    const double height_ = kPlatformHeight;
    double width_;
    double speed_;
    cinder::vec2 loc_;
    explicit platform(cinder::vec2 location);
    void update();
    void draw();
    cinder::vec2 GetPlatformTopMiddle();
    ci::Rectf GetPlatformBounds(); // Only return the top of the platform
    int GetPlatformWidth();
    void IncreaseWidth(double width_increase_factor);
  };
}


#endif //FINALPROJECT_PLATFORM_H
