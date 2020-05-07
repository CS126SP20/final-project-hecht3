//
// Created by connell on 4/29/20.
//

#ifndef FINALPROJECT_POWERUP_H
#define FINALPROJECT_POWERUP_H

#include <cinder/gl/gl.h>

/**
 * The factor to increase the platform width by when
 * a platform powerup is collected.
 * */
constexpr double kDefaultPlatformWidthIncreaseFactor = 1.5;

namespace BrickBreaker {
  using namespace cinder;

  /** The number of possible powerup types. */
  constexpr int kPowerupNumTypes = 2;
  /** The pixel size of a powerup. */
  constexpr int kPowerupSize = 20;

  /** The possible types of powerups. Currently includes two. */
  enum powerup_type {
    BALL, PLATFORM
  };

  class powerup {
  public:
   /**
    * Constructor for a powerup.
    *
    * @param location the location of the powerup
    * @param speed the speed the powerup falls at
    */
    powerup(vec2 location, double speed);

    void update();

    void draw();

    powerup_type GetType() const;

    vec2 GetLocation() const;

  private:
    /** The direction the powerup is moving in. Is always directly down. */
    vec2 dir_;
    /** The size of one side of the square powerup. */
    size_t size_;
    /** The speed the powerup falls at. */
    double speed_;
    /** The location of the center of the powerup */
    vec2 loc_;
    /** The type of the powerup assigned randomly on construction */
    powerup_type type_;
  };
}


#endif //FINALPROJECT_POWERUP_H
