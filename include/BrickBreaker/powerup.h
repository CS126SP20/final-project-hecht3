//
// Created by connell on 4/29/20.
//

#ifndef FINALPROJECT_POWERUP_H
#define FINALPROJECT_POWERUP_H

#include <cinder/gl/gl.h>

namespace BrickBreaker {

  const int kPowerupNumTypes = 2;
  const int kPowerupSize = 20;

  enum powerup_type {BALL, PLATFORM};

  class powerup {
  public:
    powerup(cinder::vec2 location, double speed);
    // Move assignment operator for deleting a powerup from a vector
    //powerup& operator=(powerup&&) throw() {return *this;};
    cinder::vec2 dir_;
    size_t size_;
    double speed_;
    cinder::vec2 loc_;
    powerup_type type_;
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_POWERUP_H
