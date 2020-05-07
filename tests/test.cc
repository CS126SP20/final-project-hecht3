// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <BrickBreaker/ball.h>
#include <BrickBreaker/brick.h>
#include <BrickBreaker/platform.h>
#include <BrickBreaker/powerup.h>

// There is not a lot of testable code in this project because most operations
// involve the cinder app functions or openGL. Below I have tested all of the
// code that is possible to test.

TEST_CASE("Test ball" "[Constructor][radius][location][direction]") {
  BrickBreaker::ball ball = BrickBreaker::ball(ci::vec2(1, 1), 5,
                                               ci::vec2(0, 7), 20);
  SECTION("Constructor") {
    REQUIRE(ball.GetRadius() == 20);
    REQUIRE(ball.GetDirection() == ci::vec2(0, 7));
    REQUIRE(ball.GetLocation() == ci::vec2(1, 1));
  }
}

TEST_CASE("Test brick" "[Constructor][upper right corner][upper left corner]"
          "[lower right corner][lower left corner]") {
  BrickBreaker::brick brick = BrickBreaker::brick(ci::vec2(1, 1), 100);
  SECTION("Constructor") {
    REQUIRE(brick.GetUpperRightCorner() == ci::vec2(1 + kBrickWidth, 1));
    REQUIRE(brick.GetUpperLeftCorner() == ci::vec2(1, 1));
    REQUIRE(brick.GetLowerRightCorner() ==
            ci::vec2(1 + kBrickWidth, 1 + kBrickHeight));
    REQUIRE(brick.GetLowerLeftCorner() == ci::vec2(1, 1 + kBrickHeight));
  }
}

TEST_CASE("Test platform" "[Constructor][get width][top middle]"
          "[change width][bounds][location]") {
  BrickBreaker::platform platform = BrickBreaker::platform(ci::vec2(1, 1));
  SECTION("Constructor") {
    REQUIRE(platform.GetLocation() == ci::vec2(1, 1));
    REQUIRE(platform.GetPlatformWidth() == kDefaultPlatformWidth);
    REQUIRE(
      platform.GetPlatformTopMiddle() == ci::vec2(1, 1 - kPlatformHeight / 2));
    REQUIRE(platform.GetPlatformBounds().x1 ==
            platform.GetLocation().x - kDefaultPlatformWidth / 2);
    REQUIRE(platform.GetPlatformBounds().y1 ==
            platform.GetLocation().y - kPlatformHeight / 2);
    REQUIRE(platform.GetPlatformBounds().x2 ==
            platform.GetLocation().x + kDefaultPlatformWidth / 2);
    REQUIRE(platform.GetPlatformBounds().y2 ==
            platform.GetLocation().y - kPlatformHeight / 2);
  }
}

TEST_CASE("Test powerup" "[Constructor][get location][get type]") {
  BrickBreaker::powerup powerup = BrickBreaker::powerup(ci::vec2(1, 1), 5);
  SECTION("Constructor") {
    REQUIRE(powerup.GetLocation() == ci::vec2(1, 1));
    REQUIRE(
      powerup.GetType() == (BrickBreaker::BALL || BrickBreaker::PLATFORM));
  }
}