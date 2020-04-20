// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>


namespace myapp {

  using cinder::app::KeyEvent;

  int kBrickOffset = 30;
  int kWallOffset = 15;

  void MyApp::setup() {
    is_start_ = true;
    time_ = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location);
        bricks_.push_back(brick);
      }
    }
    ci::vec2 platform_init_loc = ci::vec2(getWindowCenter().x,
                                          getWindowBounds().y2 - kWallOffset);
    BrickBreaker::platform platform = BrickBreaker::platform(platform_init_loc);
    platforms_.push_back(platform);
    BrickBreaker::ball ball = BrickBreaker::ball(
      ci::vec2(platform.loc_.x, platform.loc_.y - platform.height_),
      kDefaultBallSpeed, ci::vec2(10, -10));
    balls_.push_back(ball);
  }

  void MyApp::update() {
    ci::gl::clear();
    UpdateBricks();
    UpdateBalls();
    UpdatePlatforms();
  }

  void MyApp::draw() {}

  // https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
  void MyApp::mouseMove(ci::app::MouseEvent event) {
    last_mouse_loc_ = current_mouse_loc_;
    current_mouse_loc_ = event.getPos();
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

  void MyApp::UpdateBricks() {
    for (auto brick_iterator = bricks_.begin();
         brick_iterator != bricks_.end();) {
      brick_iterator->update();
      for (auto ball_iterator = balls_.begin();
           ball_iterator != balls_.end(); ++ball_iterator) {
        // Check collision with top of brick
        if (CheckTopBottomCollision(*ball_iterator, *brick_iterator)) {
          brick_iterator->health_ -= 100;
          ball_iterator->BrickTopBottomCollision();
        } else if (CheckSideCollision(*ball_iterator,
                                                  *brick_iterator)) {
          brick_iterator->health_ -= 100;
          ball_iterator->BrickSideCollision();
        }
      }
      if (brick_iterator->health_ <= 0) {
        brick_iterator = bricks_.erase(brick_iterator);
      } else {
        ++brick_iterator;
      }
    }
  }

  void MyApp::UpdatePlatforms() {
    double time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::
      now().time_since_epoch()).count() - time_;
    float change_in_mouse_loc_x = last_mouse_loc_.x - current_mouse_loc_.x;
    mouse_vel_ = change_in_mouse_loc_x / time_elapsed;
    for (auto platform_iterator = platforms_.begin();
         platform_iterator != platforms_.end();) {
      if (last_mouse_loc_.x >
          getWindowBounds().x2 - kDefaultPlatformWidth / 2) {
        last_mouse_loc_.x = getWindowBounds().x2 - kDefaultPlatformWidth / 2;
      } else if (last_mouse_loc_.x <
                 getWindowBounds().x1 + kDefaultPlatformWidth / 2) {
        last_mouse_loc_.x = getWindowBounds().x1 + kDefaultPlatformWidth / 2;
      }
      platform_iterator->loc_ = ci::vec2(last_mouse_loc_.x,
                                         platform_iterator->loc_.y);
      platform_iterator->update();
      if (false) {
        // Add condition here for power-up extension
      } else {
        ++platform_iterator;
      }
    }
    time_ = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::
      now().time_since_epoch()).count();
  }

  void MyApp::UpdateBalls() {
    for (auto ball_iterator = balls_.begin(); ball_iterator != balls_.end();) {
      if (ball_iterator->loc_.x <= getWindowBounds().x1 + ball_iterator->GetRadius() ||
          ball_iterator->loc_.x >= getWindowBounds().x2 - ball_iterator->GetRadius()) {
        ball_iterator->WallCollision();
      } else if (ball_iterator->loc_.y <=
                 getWindowBounds().y1 + ball_iterator->GetRadius()) {
        ball_iterator->CeilingCollision();
      } else {
        for (BrickBreaker::platform platform : platforms_) {
          if (ball_iterator->loc_.x + ball_iterator->GetRadius() >
              platform.GetPlatformBounds().getX1() &&
              ball_iterator->loc_.x - ball_iterator->GetRadius() <
              platform.GetPlatformBounds().getX2() &&
              ball_iterator->loc_.y + 3 >=
              platform.GetPlatformBounds().getY1() -
              ball_iterator->GetRadius() && ball_iterator->loc_.y - 3 <=
                                    platform.GetPlatformBounds().getY1() -
                                    ball_iterator->GetRadius() && !is_start_) {
            ball_iterator->PlatformCollision(mouse_vel_);
          }
        }
      }
      ball_iterator->update();
      if (ball_iterator->loc_.y > getWindowBounds().y2) {
        ball_iterator = balls_.erase(ball_iterator);
      } else {
        ++ball_iterator;
      }
    }
    is_start_ = false;
  }

  bool MyApp::CheckSideCollision(BrickBreaker::ball ball,
                                             BrickBreaker::brick brick) {
    bool within_vert_bound = ball.GetLocation().y + ball.GetRadius() >
                             brick.GetUpperLeftCorner().y &&
                             ball.GetLocation().y - ball.GetRadius() <
                             brick.GetLowerLeftCorner().y;
    bool brick_hit_left = ball.GetLocation().x + ball.GetRadius() - 3 <=
                          brick.GetUpperLeftCorner().x &&
                          ball.GetLocation().x + ball.GetRadius() + 3 >=
                          brick.GetUpperLeftCorner().x &&
                          ball.GetDirection().x >= 0;
    bool brick_hit_right = ball.GetLocation().x - ball.GetRadius() + 3 >=
                           brick.GetUpperRightCorner().x &&
                           ball.GetLocation().x - ball.GetRadius() - 3 <=
                           brick.GetUpperRightCorner().x &&
                           ball.GetDirection().x <= 0;
    return within_vert_bound && (brick_hit_left || brick_hit_right);
  }

  bool MyApp::CheckTopBottomCollision(BrickBreaker::ball ball,
                                              BrickBreaker::brick brick) {
    bool within_horiz_bound = ball.GetLocation().x + ball.GetRadius() >
                              brick.GetUpperLeftCorner().x &&
                              ball.GetLocation().x - ball.GetRadius() <
                              brick.GetUpperRightCorner().x;
    bool brick_hit_top = ball.GetLocation().y + ball.GetRadius() + 3 >=
                            brick.GetUpperLeftCorner().y &&
                            ball.GetLocation().y + ball.GetRadius() - 3 <=
                            brick.GetUpperLeftCorner().y &&
                            ball.GetDirection().y >= 0;
    bool brick_hit_bottom = ball.GetLocation().y - ball.GetRadius() - 3 <=
                         brick.GetLowerLeftCorner().y &&
                         ball.GetLocation().y - ball.GetRadius() + 3 >=
                         brick.GetLowerLeftCorner().y &&
                         ball.GetDirection().y <= 0;
    return within_horiz_bound && (brick_hit_top || brick_hit_bottom);
  }

}  // namespace myapp
