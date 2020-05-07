//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

#include <cinder/app/App.h>

constexpr int kDefaultBrickWidth = 50;
constexpr int kDefaultBrickHeight = 20;
constexpr int kDefaultBrickHealth = 300;

namespace BrickBreaker {
  using namespace cinder;

  const int kMaxHealth = 1000;

  class brick {
  public:
   /**
    * The constructor for the brick class.
    *
    * @param location the top right corner of the brick
    * @param health the amount of health the brick will have
    */
    brick(const vec2 &location, int health, int height = kDefaultBrickHeight,
          int width = kDefaultBrickWidth);

    void update();

    void draw();

    vec2 GetUpperLeftCorner();

    vec2 GetUpperRightCorner();

    vec2 GetLowerLeftCorner();

    vec2 GetLowerRightCorner();

    int GetHealth() const;

   /**
    * Checks if the brick contains a powerup. This is determined randomly on
    * construction.
    *
    * @return whether or not the brick has a powerup
    */
    bool CheckContainsPowerup() const;

   /**
    * Used for when a ball hits a brick.
    *
    * @param how much damage the ball did
    */
    void DecreaseHealth(int health_decrease_amount);

  private:
    /** The height of the brick */
    int height_;
    /** The width of the brick */
    int width_;
    /** The current health of the brick */
    int health_;
    /** The location of the top left corner of the brick */
    vec2 loc_;
    /** The initial health of the brick */
    int full_health_;
    /** Whether or not the brick contains a powerup */
    bool has_powerup_;
  };
}


#endif //FINALPROJECT_BLOCK_H
