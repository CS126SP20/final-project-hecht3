//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <cinder/app/App.h>

namespace BrickBreaker {
  class ball {
  public:
    const double radius_ = 2;
    double speed_;
    double dir_;
    cinder::vec2 loc_;
    ball(cinder::vec2 location);
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_BALL_H
