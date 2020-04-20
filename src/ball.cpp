//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/ball.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {

  const double kFrictionCoefficient = 500;
  const double kMaxSpeedThreshold = 7.0;

  ball::ball(cinder::vec2 location, double speed, ci::vec2 dir) {
    loc_ = location;
    radius_ = kDefaultBallRadius;
    speed_ = speed;
    dir_ = dir;
    draw();
  }

  void ball::update() {
    double orig_x = dir_.x;
    // Normalize vectors
    dir_.x = dir_.x / sqrt(pow(dir_.x, 2) + pow(dir_.y, 2));
    dir_.y = dir_.y / sqrt(pow(orig_x, 2) + pow(dir_.y, 2));
    // Adjust location according to velocity
    loc_.x += dir_.x * speed_;
    loc_.y += dir_.y * speed_;
    draw();
  }

  void ball::draw() {
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawSolidCircle(loc_, radius_);
  }

  void ball::WallCollision() {
    dir_.x = -dir_.x;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .01;
    }
  }

  void ball::CeilingCollision() {
    dir_.y = -dir_.y;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .01;
    }
  }

  void ball::PlatformCollision(double mouse_vel) {
    dir_.y = -dir_.y;
    dir_.x -= kFrictionCoefficient * mouse_vel;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .01;
    }
  }

  void ball::BrickTopBottomCollision() {
    dir_.y = -dir_.y;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .01;
    }
  }

  void ball::BrickSideCollision() {
    dir_.x = -dir_.x;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .01;
    }
  }

  ci::vec2 ball::GetLocation() {
    return loc_;
  }

  ci::vec2 ball::GetDirection() {
    return dir_;
  }

  double ball::GetRadius() {
    return radius_;
  }
}