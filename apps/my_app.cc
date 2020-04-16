// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>


namespace myapp {

  using cinder::app::KeyEvent;

  MyApp::MyApp() {}

  void MyApp::setup() {

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
  void MyApp::mouseMove(cinder::app::MouseEvent event) {
    mouse_move_ = event.getPos();

  }

  void MyApp::mouseDrag(cinder::app::MouseEvent event ) {
    mouseMove(event);
  }

  void MyApp::RemoveBrick(int brick_id) {

  };

  void MyApp::RemoveBall(int ball_id) {

  }

  void MyApp::RemovePlatform(int platform_id) {

  }

}  // namespace myapp
