// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>
#include <stdio.h>
#include <BrickBreaker/levels.h>
#include <Sound/poSoundManager.h>

// Brick sound from: https://freesound.org/people/kramsttop/sounds/170910/

namespace myapp {

// Following definitions are from Snake assignment
#if defined(CINDER_COCOA_TOUCH)
  const char kNormalFont[] = "Arial";
  const char kBoldFont[] = "Arial-BoldMT";
  const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
  const char kNormalFont[] = "Arial Unicode MS";
  const char kBoldFont[] = "Arial Unicode MS";
  const char kDifferentFont[] = "Purisa";
#else
  const char kNormalFont[] = "Arial";
  const char kBoldFont[] = "Arial Bold";
  const char kDifferentFont[] = "Papyrus";
#endif
  using cinder::app::KeyEvent;

  const int kWallOffset = 15;
  const int kCollisionPixelThreshold = 3;
  const int kMenuGridDim = 5;
  const int kDefaultBallHitHealthDecrease = 100;
  const int kTenthOfSecondInMicroseconds = 100000;
  const int kBallPowerupCreationNum = 5;
  ci::DataSourceRef brick_sound;

  void MyApp::setup() {

  }

  void MyApp::update() {
    if (!level_clicked_) {
      DrawMenuScreen();
    } else if (bricks_.empty()) {
      is_start_ = true;
      SelectLevel(++current_level_);
    } else {
      ci::gl::clear();
      UpdateBricks();
      UpdateBalls();
      UpdatePlatforms();
      UpdatePowerups();
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
    brick_sound = cinder::app::loadAsset(
      "/home/connell/Cinder/projects/final-project-hecht3/assets/brick_tap.wav");
    menu_grid_width_ = cinder::app::getWindowBounds().x2 / kMenuGridDim;
    menu_grid_height_ = cinder::app::getWindowBounds().y2 / kMenuGridDim;
    is_start_ = true;
    level_clicked_ = false;
    time_ = 0;
    last_collision_time_ = time_;
    clicks_ = 0;
    levels_ = BrickBreaker::levels::GenerateLevels();
  }

  void MyApp::UpdateBricks() {
    for (auto brick_iterator = bricks_.begin();
         brick_iterator != bricks_.end();) {
      brick_iterator->update();
      for (auto ball_iterator = balls_.begin();
           ball_iterator != balls_.end(); ++ball_iterator) {
        // Check collision with top of brick
        if (CheckTopBottomCollision(*ball_iterator, *brick_iterator)) {
          brick_iterator->health_ -= kDefaultBallHitHealthDecrease;
          ball_iterator->BrickTopBottomCollision();
          po::SoundManager::get()->play(brick_sound);
        } else if (CheckSideCollision(*ball_iterator,
                                      *brick_iterator)) {
          brick_iterator->health_ -= kDefaultBallHitHealthDecrease;
          ball_iterator->BrickSideCollision();
          po::SoundManager::get()->play(brick_sound);
        }
      }
      if (brick_iterator->health_ <= 0) {
        if (brick_iterator->has_powerup_) {
          powerups_.emplace_back(ci::vec2(
            (brick_iterator->GetLowerLeftCorner().x +
             brick_iterator->GetLowerRightCorner().x) / 2,
            (brick_iterator->GetLowerLeftCorner().y +
             brick_iterator->GetLowerRightCorner().y) / 2), balls_[0].speed_);
        }
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
         platform_iterator != platforms_.end(); ++platform_iterator) {
      if (last_mouse_loc_.x >
          getWindowBounds().x2 - platform_iterator->GetPlatformWidth() / 2) {
        last_mouse_loc_.x =
          getWindowBounds().x2 - platform_iterator->GetPlatformWidth() / 2;
      } else if (last_mouse_loc_.x <
                 getWindowBounds().x1 +
                 platform_iterator->GetPlatformWidth() / 2) {
        last_mouse_loc_.x =
          getWindowBounds().x1 + platform_iterator->GetPlatformWidth() / 2;
      }
      platform_iterator->loc_ = ci::vec2(last_mouse_loc_.x,
                                         platform_iterator->loc_.y);
      platform_iterator->update();
    }
    time_ = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::
      now().time_since_epoch()).count();
  }

  void MyApp::UpdateBalls() {
    for (auto ball_iterator = balls_.begin(); ball_iterator != balls_.end();) {
      if (last_click_count_ < clicks_ && is_start_) {
        is_start_ = false;
        ball_iterator->dir_ = ci::vec2(
          ball_iterator->loc_.x - last_mouse_loc_.x,
          ball_iterator->loc_.y - last_mouse_loc_.y);
        last_click_count_ = clicks_;
      }
      // We can get platforms[0] here because at the start, platforms are always
      // initialized before balls
      if (is_start_) {
        ball_iterator->loc_ = ci::vec2(platforms_[0].GetPlatformTopMiddle().x,
                                       platforms_[0].GetPlatformTopMiddle().y -
                                       ball_iterator->GetRadius());
      } else if (ball_iterator->loc_.x <=
                 getWindowBounds().x1 + ball_iterator->GetRadius() ||
                 ball_iterator->loc_.x >=
                 getWindowBounds().x2 - ball_iterator->GetRadius()) {
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
              ball_iterator->GetRadius() &&
              ball_iterator->loc_.y - kCollisionPixelThreshold <=
              platform.GetPlatformBounds().getY1() -
              ball_iterator->GetRadius()) {
            // Prevent ball getting stuck in constant platform collisions
            if (time_ - last_collision_time_ > kTenthOfSecondInMicroseconds) {
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
  }

  void MyApp::UpdatePowerups() {
    for (auto powerup_iterator = powerups_.begin();
         powerup_iterator != powerups_.end();) {
      for (auto platform_iterator = platforms_.begin();
           platform_iterator != platforms_.end(); ++platform_iterator) {
        powerup_iterator->update();
        if (powerup_iterator->loc_.x + BrickBreaker::kPowerupSize +
            kCollisionPixelThreshold >=
            platform_iterator->loc_.x &&
            powerup_iterator->loc_.x - BrickBreaker::kPowerupSize <=
            platform_iterator->loc_.x +
            kCollisionPixelThreshold) {
          if (powerup_iterator->type_ == BrickBreaker::BALL) {
            for (int i = 0; i < kBallPowerupCreationNum; i++) {
              BrickBreaker::ball ball_to_add = BrickBreaker::ball(
                balls_[0].loc_, balls_[0].speed_,
                ci::vec2(rand() - rand(), rand() - rand()));
              balls_.push_back(ball_to_add);
            }
          } else if (powerup_iterator->type_ == BrickBreaker::PLATFORM) {
            for (auto platform_iterator = platforms_.begin();
                 platform_iterator != platforms_.end(); ++platform_iterator) {
              platform_iterator->IncreaseWidth(kDefaultPlatformWidthIncreaseFactor);
            }
          }
          powerup_iterator = powerups_.erase(powerup_iterator);
        } else {
          ++powerup_iterator;
        }
      }
    }
  }

  bool MyApp::CheckSideCollision(BrickBreaker::ball ball,
                                 BrickBreaker::brick brick) {
    bool within_vert_bound = ball.GetLocation().y + ball.GetRadius() >
                             brick.GetUpperLeftCorner().y &&
                             ball.GetLocation().y - ball.GetRadius() <
                             brick.GetLowerLeftCorner().y;
    bool brick_hit_left =
      ball.GetLocation().x + ball.GetRadius() - kCollisionPixelThreshold <=
      brick.GetUpperLeftCorner().x &&
      ball.GetLocation().x + ball.GetRadius() + kCollisionPixelThreshold >=
      brick.GetUpperLeftCorner().x &&
      ball.GetDirection().x >= 0;
    bool brick_hit_right =
      ball.GetLocation().x - ball.GetRadius() + kCollisionPixelThreshold >=
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
    bool brick_hit_top =
      ball.GetLocation().y + ball.GetRadius() + kCollisionPixelThreshold >=
      brick.GetUpperLeftCorner().y &&
      ball.GetLocation().y + ball.GetRadius() - kCollisionPixelThreshold <=
      brick.GetUpperLeftCorner().y &&
      ball.GetDirection().y >= 0;
    bool brick_hit_bottom =
      ball.GetLocation().y - ball.GetRadius() - kCollisionPixelThreshold <=
      brick.GetLowerLeftCorner().y &&
      ball.GetLocation().y - ball.GetRadius() + kCollisionPixelThreshold >=
      brick.GetLowerLeftCorner().y &&
      ball.GetDirection().y <= 0;
    return within_horiz_bound && (brick_hit_top || brick_hit_bottom);
  }

  void MyApp::SelectLevel(size_t level_number) {
    bricks_.clear();
    balls_.clear();
    platforms_.clear();
    powerups_.clear();
    is_start_ = true;
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

  void MyApp::DrawMenuScreen() {
    cinder::gl::color(0, 0, 1);
    cinder::gl::lineWidth(10);
    for (int i = 0; i <= kMenuGridDim; i++) {
      for (int j = 0; j <= kMenuGridDim; j++) {
        const cinder::vec2 center = ci::vec2(
          i * menu_grid_width_ + (menu_grid_width_ / 2),
          j * menu_grid_height_ + menu_grid_height_ * .9);
        const cinder::ivec2 size = {menu_grid_width_, menu_grid_height_};
        const cinder::Color color = cinder::Color(0, 0, 1);
        PrintText(std::to_string(i + j * kMenuGridDim), color, size, center);
      }
      cinder::gl::drawLine(ci::vec2(i * menu_grid_width_, getWindowBounds().y1),
                           ci::vec2(i * menu_grid_width_,
                                    getWindowBounds().y2));
      cinder::gl::drawLine(
        ci::vec2(getWindowBounds().x1, i * menu_grid_height_),
        ci::vec2(getWindowBounds().x2, i * menu_grid_height_));
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
    for (int i = 0; i < kMenuGridDim; i++) {
      for (int j = 0; j < kMenuGridDim; j++) {
        if (loc_clicked.x > i * menu_grid_width_ &&
            loc_clicked.x < (i + 1) * menu_grid_width_ &&
            loc_clicked.y > j * menu_grid_height_ &&
            loc_clicked.y < (j + 1) * menu_grid_height_) {
          // True level number is the below number + 1 because of 0 indexing
          current_level_ = i + j * menu_grid_width_;
          return current_level_;
        }
      }
    }
    return -1;
  }

  // Following is from Snake project given code
  template<typename C>
  void MyApp::PrintText(const std::string &text, const C &color,
                        const cinder::ivec2 &size,
                        const cinder::vec2 &loc) {
    cinder::gl::color(color);

    auto box = ci::TextBox()
      .alignment(ci::TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ci::ColorA(0, 0, 0, 0))
      .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
  }

}  // namespace myapp
