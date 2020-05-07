//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_PLATFORM_H
#define FINALPROJECT_PLATFORM_H

#include <cinder/app/App.h>

constexpr int kDefaultPlatformWidth = 100;
constexpr int kPlatformHeight = 10;

namespace BrickBreaker {
  using namespace cinder;

  class platform {
  public:
   /**
    * Constructor for a platform.
    *
    * @param location the location of the platform
    * @param width the width of the platform
    */
    explicit platform(vec2 location, int width = kDefaultPlatformWidth);

    void update();

    void draw();

    /** Changes the width of the platform. Used when powerups are collected */
    void ChangeWidth(double width_change_factor);

    /** Changes the location of the platform. Platform follows the user's mouse*/
    void ChangeLocation(vec2 new_location);

    vec2 GetPlatformTopMiddle() const;

    /** Only returns the top of the platform */
    Rectf GetPlatformBounds() const;

    int GetPlatformWidth() const;

    vec2 GetLocation() const;

    int GetHeight() const;

  private:
    /** The height of the platform */
    const double height_ = kPlatformHeight;
    /** The width of the platform */
    double width_;
    /** The current location of the platform */
    vec2 loc_;
  };
}


#endif //FINALPROJECT_PLATFORM_H
