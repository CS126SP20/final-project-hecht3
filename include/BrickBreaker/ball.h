//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <cinder/app/App.h>

const int kDefaultBallRadius = 10;
const int kDefaultBallSpeed = 5;

namespace BrickBreaker {
  class ball {
  public:
    double radius_;
    double speed_;
    double dir_;
    cinder::vec2 loc_;
    explicit ball(cinder::vec2 location, double speed, double dir);
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_BALL_H
