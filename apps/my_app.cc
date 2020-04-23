// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>


namespace myapp {

  using cinder::app::KeyEvent;

  const int kBrickOffset = 30;
  const int kWallOffset = 15;
  const int kCollisionPixelThreshold = 3;
  const int kMenuGridX = 5;
  const int kMenuGridY = 5;

  void MyApp::setup() {
    menu_grid_width_ = cinder::app::getWindowBounds().x2 / kMenuGridX;
    menu_grid_height_ = cinder::app::getWindowBounds().y2 / kMenuGridY;
    is_start_ = true;
    level_clicked_ = false;
    time_ = 0;
    last_collision_time_ = time_;
    clicks_ = 0;
    GenerateLevels();
  }

  void MyApp::update() {
    if (!level_clicked_) {
      DrawMenuScreen();
    } else {
      ci::gl::clear();
      UpdateBricks();
      UpdateBalls();
      UpdatePlatforms();
    }
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

  void MyApp::mouseDown(ci::app::MouseEvent event) {
    if (event.isLeft()) {
      clicks_++;
    }
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
              ball_iterator->loc_.y + kCollisionPixelThreshold >=
              platform.GetPlatformBounds().getY1() -
              ball_iterator->GetRadius() && ball_iterator->loc_.y - kCollisionPixelThreshold <=
                                    platform.GetPlatformBounds().getY1() -
                                    ball_iterator->GetRadius() && !is_start_) {
            // Prevent ball getting stuck in constant platform collisions
            if (time_ - last_collision_time_ > 100000) {
              ball_iterator->PlatformCollision(mouse_vel_);
              last_collision_time_ = time_;
            }
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
    bool brick_hit_left = ball.GetLocation().x + ball.GetRadius() - kCollisionPixelThreshold <=
                          brick.GetUpperLeftCorner().x &&
                          ball.GetLocation().x + ball.GetRadius() + kCollisionPixelThreshold >=
                          brick.GetUpperLeftCorner().x &&
                          ball.GetDirection().x >= 0;
    bool brick_hit_right = ball.GetLocation().x - ball.GetRadius() + kCollisionPixelThreshold >=
                           brick.GetUpperRightCorner().x &&
                           ball.GetLocation().x - ball.GetRadius() - kCollisionPixelThreshold <=
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
    bool brick_hit_top = ball.GetLocation().y + ball.GetRadius() + kCollisionPixelThreshold >=
                            brick.GetUpperLeftCorner().y &&
                            ball.GetLocation().y + ball.GetRadius() - kCollisionPixelThreshold <=
                            brick.GetUpperLeftCorner().y &&
                            ball.GetDirection().y >= 0;
    bool brick_hit_bottom = ball.GetLocation().y - ball.GetRadius() - kCollisionPixelThreshold <=
                         brick.GetLowerLeftCorner().y &&
                         ball.GetLocation().y - ball.GetRadius() + kCollisionPixelThreshold >=
                         brick.GetLowerLeftCorner().y &&
                         ball.GetDirection().y <= 0;
    return within_horiz_bound && (brick_hit_top || brick_hit_bottom);
  }

  void MyApp::SelectLevel(int level_number) {
    bricks_.clear();
    balls_.clear();
    platforms_.clear();
    for (int i = 0; i < levels_[level_number].size(); i++) {
      bricks_.push_back(levels_[level_number][i]);
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

  void MyApp::GenerateLevels() {
    std::vector<BrickBreaker::brick> bricks;
    // Level 0
    for (int i = 0; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location, kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_.push_back(bricks);

    // Level 1
    bricks.clear();
    for (int i = 5; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location, kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_.push_back(bricks);

    // Level 2
    bricks.clear();
    for (int i = 5; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location, kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_.push_back(bricks);

    // Level 3
    bricks.clear();
    for (int i = 5; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        ci::vec2 location = cinder::vec2(
          i * (kBrickOffset + kBrickWidth) + kWallOffset,
          j * (kBrickOffset + kBrickHeight) + kWallOffset);
        BrickBreaker::brick brick = BrickBreaker::brick(location, kDefaultBrickHealth);
        bricks.push_back(brick);
      }
    }
    levels_.push_back(bricks);
  }

  void MyApp::DrawMenuScreen() {
    cinder::gl::color(0, 0, 1);
    cinder::gl::lineWidth(10);
    for (int i = 1; i < kMenuGridX; i++) {
      cinder::gl::drawLine(ci::vec2(i * menu_grid_width_, getWindowBounds().y1), ci::vec2(i * menu_grid_width_, getWindowBounds().y2));
    }
    for (int j = 1; j < kMenuGridX; j++) {
      cinder::gl::drawLine(ci::vec2(getWindowBounds().x1, j * menu_grid_height_), ci::vec2(getWindowBounds().x2, j * menu_grid_height_));
    }
    if (clicks_ > last_click_count_) {
      int level = GetLevelClicked(last_mouse_loc_);
      if (level != -1) {
        level_clicked_ = true;
        SelectLevel(level);
      }
    }
    last_click_count_ = clicks_;
  }

  int MyApp::GetLevelClicked(ci::vec2 loc_clicked) {
    for (int i = 0; i < kMenuGridX; i++) {
      for (int j = 0; j < kMenuGridY; j++) {
        if (loc_clicked.x > i * menu_grid_width_ &&
            loc_clicked.x < (i + 1) * menu_grid_width_ &&
            loc_clicked.y > j * menu_grid_height_ &&
            loc_clicked.y < (j + 1) * menu_grid_height_) {
          return i + j*menu_grid_width_;
        }
      }
    }
    return -1;
  }

}  // namespace myapp
