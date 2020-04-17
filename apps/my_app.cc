// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>


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
    BrickBreaker::ball ball = BrickBreaker::ball(ci::vec2(platform.loc_.x, platform.loc_.y - platform.height_), kDefaultBallSpeed, 0);
    balls_.push_back(ball);
  }

  void MyApp::update() {
    ci::gl::clear();
    for (auto brick_iterator = bricks_.begin(); brick_iterator != bricks_.end();) {
      brick_iterator->update();
      if (brick_iterator->health_ <= 0) {
        brick_iterator = bricks_.erase(brick_iterator);
      } else {
        ++brick_iterator;
      }
    }
    for (auto ball_iterator = balls_.begin(); ball_iterator != balls_.end();) {
      ball_iterator->update();
      if (ball_iterator->loc_.y > getWindowBounds().y2) {
        ball_iterator = balls_.erase(ball_iterator);
      } else {
        ++ball_iterator;
      }
    }
    for (auto platform_iterator = platforms_.begin(); platform_iterator != platforms_.end();) {
      platform_iterator->loc_ = ci::vec2(mouse_loc_.x, platform_iterator->loc_.y);
      platform_iterator->update();
      if (false) {
        // Add condition here for power-up extension
      } else {
        ++platform_iterator;
      }
    }
  }

  void MyApp::draw() {}

  // https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
  void MyApp::mouseMove(ci::app::MouseEvent event) {
    mouse_loc_ = event.getPos();
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
