// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include <BrickBreaker/ball.h>
#include <cinder/app/RendererGl.h>
#include <BrickBreaker/brick.h>

TEST_CASE("Test ball" "[Constructor][radius][location][update]") {
  BrickBreaker::ball ball = BrickBreaker::ball(ci::vec2(1, 1), 5, ci::vec2(0, 7), 20);
  SECTION("Constructor") {
    REQUIRE(ball.GetRadius() == 20);
    REQUIRE(ball.GetDirection() == ci::vec2(0, 7));
    REQUIRE(ball.GetLocation() == ci::vec2(1, 1));
  }
}

TEST_CASE("Test brick" "") {
  BrickBreaker::brick brick = BrickBreaker::brick(ci::vec2(1, 1), 100);
}