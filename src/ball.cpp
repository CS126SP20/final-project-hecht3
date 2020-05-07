//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/ball.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  using namespace cinder;

  const double kFrictionCoefficient = 800;
  const double kMaxSpeedThreshold = 7.0;

  ball::ball(vec2 location, double speed, vec2 dir, double radius) {

    loc_ = location;
    radius_ = radius;
    speed_ = speed;
    dir_ = dir;
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
    gl::color(0, 0, 0);
    gl::drawSolidCircle(loc_, radius_);
  }

  void ball::WallCollision() {
    dir_.x = -dir_.x;
    if (speed_ < kMaxSpeedThreshold) {
      speed_ += .05;
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

  vec2 ball::GetLocation() const {
    return loc_;
  }

  vec2 ball::GetDirection() const {
    return dir_;
  }

  double ball::GetRadius() const {
    return radius_;
  }

  double ball::GetSpeed() const {
    return speed_;
  }

  void ball::SetLocation(vec2 new_location) {
    loc_ = new_location;
  }

  void ball::SetDirection(vec2 new_direction) {
    dir_ = new_direction;
  }
}