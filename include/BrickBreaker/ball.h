//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <cinder/app/App.h>

const int kDefaultBallRadius = 10;
const double kDefaultBallSpeed = 5;

namespace BrickBreaker {
  class ball {
  public:
    double radius_;
    double speed_;
    cinder::vec2 dir_;
    cinder::vec2 loc_;
    explicit ball(cinder::vec2 location, double speed, ci::vec2 dir);
    void update();
    void draw();
    void WallCollision();
    void CeilingCollision();
    void PlatformCollision(double mouse_vel);
    void BrickTopCollision();
  };
}


#endif //FINALPROJECT_BALL_H
