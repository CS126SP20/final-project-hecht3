//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <cinder/app/App.h>

const double kDefaultBallRadius = 7.5;
const double kDefaultBallSpeed = 5.0;

namespace BrickBreaker {
  class ball {
  public:
    double radius_;
    double speed_;
    cinder::vec2 dir_;
    cinder::vec2 loc_;
    uint64_t last_collision_time_;
    explicit ball(cinder::vec2 location, double speed, ci::vec2 dir, double radius = kDefaultBallRadius);
    void update();
    void draw();
    void WallCollision();
    void CeilingCollision();
    void PlatformCollision(double mouse_vel);
    void BrickTopBottomCollision();
    void BrickSideCollision();
    ci::vec2 GetLocation();
    ci::vec2 GetDirection();
    double GetRadius();
  };
}


#endif //FINALPROJECT_BALL_H
