//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <cinder/app/App.h>

constexpr double kDefaultBallRadius = 7.5;
constexpr double kDefaultBallSpeed = 5.0;

namespace BrickBreaker {
  using namespace cinder;

  class ball {
  public:
    /**
     * The constructor for a ball
     *
     * @param dir the initial direction for the ball to travel in
     * @param location the initial location of the ball
     * @param radius the radius of the ball
     * @param speed the speed of the ball. Increases when the ball collides with
     *        objects until it reaches a max speed
     */
    ball(vec2 location, double speed, vec2 dir,
         double radius = kDefaultBallRadius);

    void update();

    void draw();

    /** Called when the ball hits a wall. Changes x direction to its opposite */
    void WallCollision();

    /**
     * Called when the ball hits the ceiling.
     * Changes y direction to its opposite.
     */
    void CeilingCollision();

    /**
     * Called when the ball hits the platform.
     * Changes y direction to its opposite.
     */
    void PlatformCollision(double mouse_vel);

    /**
     * Called when the ball hits the top or bottom of a brick.
     * Changes y direction to its opposite.
     */
    void BrickTopBottomCollision();

    /**
     * Called when the ball hits the side of a brick.
     * Changes x direction to its opposite.
     */
    void BrickSideCollision();

    void SetLocation(vec2 new_location);

    void SetDirection(vec2 new_direction);

    vec2 GetLocation() const;

    vec2 GetDirection() const;

    double GetRadius() const;

    double GetSpeed() const;

    /** The system time when the ball last collided with a brick or wall. */
    uint64_t last_brick_wall_collision_time_;
    /** The system time when the ball last collided with the platform. */
    uint64_t last_platform_collision_time_;
  private:
    /** The radius of the ball. */
    double radius_;
    /** The speed of the ball. */
    double speed_;
    /** The direction the ball is traveling in. */
    vec2 dir_;
    /** The location of the ball. */
    vec2 loc_;
  };
}


#endif //FINALPROJECT_BALL_H
