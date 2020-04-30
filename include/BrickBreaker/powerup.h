//
// Created by connell on 4/29/20.
//

#ifndef FINALPROJECT_POWERUP_H
#define FINALPROJECT_POWERUP_H

#include <cinder/gl/gl.h>

const int kPowerupNumTypes = 2;
const int kPowerupSize = 20;

namespace BrickBreaker {

  enum powerup_type {BALL, PLATFORM};


  class powerup {
  public:
    // Move assignment operator for deleting a powerup from a vector
    powerup& operator=(powerup&&) throw() {return *this;};
    const cinder::vec2 dir_ = ci::vec2(1 / sqrt(2), -1 / sqrt(2));
    size_t size_;
    double speed_;
    cinder::vec2 loc_;
    powerup_type type_;
    explicit powerup(cinder::vec2 location, double speed);
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_POWERUP_H
