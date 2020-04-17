// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>


namespace myapp {

  using cinder::app::KeyEvent;

  int kBrickOffset = 30;
  int kWallOffset = 15;

  void MyApp::setup() {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location);
        bricks_.push_back(brick);
      }
    }
    ci::vec2 platform_init_loc = ci::vec2(getWindowCenter().x, getWindowBounds().y2 - kWallOffset);
    BrickBreaker::platform platform = BrickBreaker::platform(platform_init_loc);
    platforms_.push_back(platform);
    BrickBreaker::ball ball = BrickBreaker::ball(ci::vec2(platform.loc_.x, platform.loc_.y - platform.height_), kDefaultBallSpeed);
    balls_.push_back(ball);
  }

  void MyApp::update() {
    for (BrickBreaker::brick brick : bricks_) {
      brick.update();
    }
    for (BrickBreaker::ball ball : balls_) {
      ball.update();
    }
    for (BrickBreaker::platform platform : platforms_) {
      platform.update();
    }
  }

  void MyApp::draw() {}

  // https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
  void MyApp::mouseMove(ci::app::MouseEvent event) {
    mouse_move_ = event.getPos();

  }

  void MyApp::mouseDrag(ci::app::MouseEvent event) {
    mouseMove(event);
  }

  void MyApp::RemoveBrick(int brick_id) {

  }

  void MyApp::RemoveBall(int ball_id) {

  }

  void MyApp::RemovePlatform(int platform_id) {

  }

  MyApp::MyApp() {

  }

}  // namespace myapp
