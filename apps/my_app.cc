// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>
#include <stdio.h>
#include <BrickBreaker/levels.h>
#include <Sound/poSoundManager.h>

// Brick sound from: https://freesound.org/people/kramsttop/sounds/170910/
// Brick Texture from: https://www.alamy.com/a-close-up-of-a-red-bricked-wall-bricky-texture-brickwork-jointed-background-seams-of-a-brick-wall-blocks-of-bricks-in-fence-construction-zooming-image222082661.html
// Background from: https://www.canva.com/design/play?template=EADajhczPNQ&type=TADCRcaBSd0
// Platform sound from: https://www.fesliyanstudios.com/royalty-free-sound-effects-download/hammer-hitting-metal-57
// Wall sound from: https://www.sounds-resource.com/pc_computer/terraria/sound/2890/


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
  using namespace cinder;
  using app::KeyEvent;

  /** The default pixel offset from the wall for bricks being drawn. */
  constexpr int kWallOffset = 15;
  /**
   * The threshold for how close an object has to get before a collision occurs.
   */
  constexpr int kCollisionPixelThreshold = 3;
  /** The menu grid dimension. The menu is currently 5 by 5. */
  constexpr int kMenuGridDim = 5;
  /** The default amount of damage a ball does to a brick on collision. */
  constexpr int kDefaultBallHitHealthDecrease = 100;
  /**
   * Tenth of a second in microseconds. Is used to prevent balls from getting
   * stuck in constexprant collisions.
   */
  constexpr int kTwentiethOfSecondInMicroseconds = 50000;
  /** The amount of balls the ball powerup creates. */
  constexpr int kBallPowerupCreationNum = 5;
  /**
   * The default amount of time for the platform powerup to last in microseconds.
   * Is currently set to 10 seconds.
   */
  constexpr int kDefaultPlatformPowerupDuration = 10000000;
  /** The max level that has been created so far in levels.cpp */
  constexpr int kMaxLevel = 3;
  /** Pixel offset to exclude window header. */
  constexpr int kWindowHeightOffset = 5;
  /** The line width for the lines that make up the menu. */
  constexpr int kMenuLineWidth = 10;

  void MyApp::setup() {
    background = loadImage(app::loadAsset("background.png"));
    background_texture = (gl::Texture::create(background));
  }

  void MyApp::update() {
    if (balls_.size() == 0 && !is_start_) {
      const ivec2 size = {app::getWindowBounds().x2 / 2,
                          app::getWindowBounds().y2 / 2};
      bricks_.clear();
      const Color color = Color(1, 0, .2f);
      PrintText(std::string("Game over!"), color, size, getWindowCenter());
    } else {
      if (!level_clicked_) {
        DrawMenuScreen();
      } else if (bricks_.empty()) {
        is_start_ = true;
        if (current_level_ <= max_level_) {
          SelectLevel(++current_level_);
        } else {
          balls_.clear();
        }
      } else {
        gl::clear();
        gl::color(1, 1, 1);
        background_texture->bind();
        gl::draw(background_texture, getWindowBounds());
        UpdateBricks();
        UpdateBalls();
        UpdatePlatforms();
        UpdatePowerups();
      }
    }
  }

  void MyApp::draw() {}

  // https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
  void MyApp::mouseMove(app::MouseEvent event) {
    last_mouse_loc_ = current_mouse_loc_;
    current_mouse_loc_ = event.getPos();
  }

  void MyApp::mouseDrag(app::MouseEvent event) {
    mouseMove(event);
  }

  void MyApp::mouseDown(app::MouseEvent event) {
    if (event.isLeft()) {
      clicks_++;
    }
  }


  MyApp::MyApp() {
    brick_sound = app::loadAsset("brick_tap.wav");
    platform_sound = app::loadAsset("platform_tap.wav");
    wall_sound = app::loadAsset("wall_tap.wav");
    po::SoundManager::get();
    menu_grid_width_ = app::getWindowBounds().x2 / kMenuGridDim;
    menu_grid_height_ = app::getWindowBounds().y2 / kMenuGridDim;
    is_start_ = true;
    level_clicked_ = false;
    time_ = 0;
    clicks_ = 0;
    platform_powerup_count_ = 0;
    max_level_ = kMaxLevel;
    current_level_ = 0;
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
          brick_iterator->DecreaseHealth(kDefaultBallHitHealthDecrease);
          ball_iterator->BrickTopBottomCollision();
          po::SoundManager::get()->play(brick_sound);
        } else if (CheckSideCollision(*ball_iterator,
                                      *brick_iterator)) {
          brick_iterator->DecreaseHealth(kDefaultBallHitHealthDecrease);
          ball_iterator->BrickSideCollision();
          po::SoundManager::get()->play(brick_sound);
        }
      }
      if (brick_iterator->GetHealth() <= 0) {
        if (brick_iterator->CheckContainsPowerup()) {
          powerups_.emplace_back(vec2(
            (brick_iterator->GetLowerLeftCorner().x +
             brick_iterator->GetLowerRightCorner().x) / 2,
            (brick_iterator->GetLowerLeftCorner().y +
             brick_iterator->GetLowerRightCorner().y) / 2), balls_[0].GetSpeed());
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
    last_platform_loc_ = platforms_[0].GetLocation();
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
      platform_iterator->ChangeLocation(vec2(last_mouse_loc_.x,
                                             platform_iterator->GetLocation().y));
      platform_iterator->update();
    }
    float change_in_platform_loc_x_ =
      last_platform_loc_.x - platforms_[0].GetLocation().x;
    platform_vel_ = change_in_platform_loc_x_ / time_elapsed;
    time_ = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::
      now().time_since_epoch()).count();
  }

  void MyApp::UpdateBalls() {
    for (auto ball_iterator = balls_.begin(); ball_iterator != balls_.end();) {
      if (last_click_count_ < clicks_ && is_start_) {
        is_start_ = false;
        play_platform_sound_ = false;
        ball_iterator->SetDirection(vec2(
          ball_iterator->GetLocation().x - last_mouse_loc_.x,
          ball_iterator->GetLocation().y - last_mouse_loc_.y));
        last_click_count_ = clicks_;
      }
      // We can get platforms[0] here because at the start, platforms are always
      // initialized before balls
      if (is_start_) {
        ball_iterator->SetLocation(vec2(platforms_[0].GetPlatformTopMiddle().x,
                                   platforms_[0].GetPlatformTopMiddle().y -
                                   ball_iterator->GetRadius()));
      } else if ((ball_iterator->GetLocation().x <=
                  getWindowBounds().x1 + ball_iterator->GetRadius() +
                  kCollisionPixelThreshold ||
                  ball_iterator->GetLocation().x + kCollisionPixelThreshold >=
                  getWindowBounds().x2 - ball_iterator->GetRadius()) &&
                 time_ - ball_iterator->last_brick_wall_collision_time_ >
                 kTwentiethOfSecondInMicroseconds) {
        ball_iterator->WallCollision();
        po::SoundManager::get()->play(wall_sound);
        ball_iterator->last_brick_wall_collision_time_ = time_;
      } else if (ball_iterator->GetLocation().y <=
                 getWindowBounds().y1 + kWindowHeightOffset +
                 ball_iterator->GetRadius()) {
        if (time_ - ball_iterator->last_brick_wall_collision_time_ >
            kTwentiethOfSecondInMicroseconds) {
          ball_iterator->CeilingCollision();
          ball_iterator->last_brick_wall_collision_time_ = time_;
        }
        po::SoundManager::get()->play(wall_sound);
        ball_iterator->last_brick_wall_collision_time_ = time_;
      } else {
        for (BrickBreaker::platform platform : platforms_) {
          if (ball_iterator->GetLocation().x + ball_iterator->GetRadius() >
              platform.GetPlatformBounds().getX1() &&
              ball_iterator->GetLocation().x - ball_iterator->GetRadius() <
              platform.GetPlatformBounds().getX2() &&
              ball_iterator->GetLocation().y + kCollisionPixelThreshold >=
              platform.GetPlatformBounds().getY1() -
              ball_iterator->GetRadius() &&
              ball_iterator->GetLocation().y - kCollisionPixelThreshold <=
              platform.GetPlatformBounds().getY1() -
              ball_iterator->GetRadius()) {
            // Prevent ball getting stuck in constant platform collisions
            if (time_ - ball_iterator->last_platform_collision_time_ >
                kTwentiethOfSecondInMicroseconds) {
              ball_iterator->PlatformCollision(platform_vel_);
              ball_iterator->last_platform_collision_time_ = time_;
              if (play_platform_sound_) {
                po::SoundManager::get()->play(platform_sound);
              }
              play_platform_sound_ = true;
            }
          }
        }
      }
      ball_iterator->update();
      if (ball_iterator->GetLocation().y > getWindowBounds().y2) {
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
        if (platform_powerup_count_ > 0 &&
            time_ - kDefaultPlatformPowerupDuration > platform_powerup_time_) {
          platform_iterator->ChangeWidth(
            1 / kDefaultPlatformWidthIncreaseFactor);
          platform_powerup_count_--;
        }
        if (CheckPowerupCollection(*powerup_iterator, *platform_iterator)) {
          if (powerup_iterator->GetType() == BrickBreaker::BALL) {
            for (int i = 0; i < kBallPowerupCreationNum; i++) {
              BrickBreaker::ball ball_to_add = BrickBreaker::ball(
                balls_[0].GetLocation(), balls_[0].GetSpeed(),
                vec2(rand() - rand(), rand() - rand()));
              balls_.push_back(ball_to_add);
            }
          } else if (powerup_iterator->GetType() == BrickBreaker::PLATFORM) {
            for (auto &platform : platforms_) {
              platform.ChangeWidth(kDefaultPlatformWidthIncreaseFactor);
              platform_powerup_time_ = time_;
              platform_powerup_count_++;
            }
          }
          powerup_iterator = powerups_.erase(powerup_iterator);
        } else {
          ++powerup_iterator;
        }
      }
    }
  }

  bool MyApp::CheckSideCollision(BrickBreaker::ball &ball,
                                 BrickBreaker::brick &brick) {
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

  bool MyApp::CheckTopBottomCollision(BrickBreaker::ball &ball,
                                      BrickBreaker::brick &brick) {
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

  bool MyApp::CheckPowerupCollection(BrickBreaker::powerup &powerup,
                                     BrickBreaker::platform &platform) {
    bool within_sides =
      powerup.GetLocation().x + BrickBreaker::kPowerupSize +
      kCollisionPixelThreshold >=
      platform.GetPlatformBounds().x1 &&
      powerup.GetLocation().x - BrickBreaker::kPowerupSize <=
      platform.GetPlatformBounds().x2 + kCollisionPixelThreshold;
    bool within_vertical =
      powerup.GetLocation().y + BrickBreaker::kPowerupSize +
      kCollisionPixelThreshold >=
      platform.GetPlatformBounds().y1 &&
      powerup.GetLocation().y - BrickBreaker::kPowerupSize <=
      platform.GetPlatformBounds().y2 + kCollisionPixelThreshold;
    return within_sides && within_vertical;
  }

  void MyApp::DrawMenuScreen() {
    gl::color(0, 0, 1);
    gl::lineWidth(kMenuLineWidth);
    for (int i = 0; i <= kMenuGridDim; i++) {
      for (int j = 0; j <= kMenuGridDim; j++) {
        const vec2 center = vec2(
          i * menu_grid_width_ + (menu_grid_width_ / 2),
          j * menu_grid_height_ + menu_grid_height_ * .9);
        const ivec2 size = {menu_grid_width_, menu_grid_height_};
        const Color color = Color(0, 0, 1);
        PrintText(std::to_string(i + j * kMenuGridDim), color, size, center);
      }
      gl::drawLine(vec2(i * menu_grid_width_, getWindowBounds().y1),
                   vec2(i * menu_grid_width_,
                        getWindowBounds().y2));
      gl::drawLine(
        vec2(getWindowBounds().x1, i * menu_grid_height_),
        vec2(getWindowBounds().x2, i * menu_grid_height_));
    }
    if (clicks_ > last_click_count_) {
      size_t level = GetLevelClicked(last_mouse_loc_);
      if (level != -1) {
        level_clicked_ = true;
        SelectLevel(level);
      }
    }
    last_click_count_ = clicks_;
  }

  void MyApp::SelectLevel(size_t level_number) {
    bricks_.clear();
    balls_.clear();
    platforms_.clear();
    powerups_.clear();
    is_start_ = true;
    for (const auto &i : levels_[level_number]) {
      bricks_.push_back(i);
    }
    vec2 platform_init_loc = vec2(getWindowCenter().x,
                                  getWindowBounds().y2 - kWallOffset);
    BrickBreaker::platform platform = BrickBreaker::platform(platform_init_loc);
    platforms_.push_back(platform);
    BrickBreaker::ball ball = BrickBreaker::ball(
      vec2(platform.GetLocation().x,
           platform.GetLocation().y - platform.GetHeight()),
      kDefaultBallSpeed, vec2(10, -10));
    balls_.push_back(ball);
  }

  size_t MyApp::GetLevelClicked(vec2 loc_clicked) {
    for (int i = 0; i < kMenuGridDim; i++) {
      for (int j = 0; j < kMenuGridDim; j++) {
        if (loc_clicked.x > i * menu_grid_width_ &&
            loc_clicked.x < (i + 1) * menu_grid_width_ &&
            loc_clicked.y > j * menu_grid_height_ &&
            loc_clicked.y < (j + 1) * menu_grid_height_) {
          // True level number is the below number + 1 because of 0 indexing
          if (i + j * menu_grid_width_ <= max_level_) {
            current_level_ = i + j * menu_grid_width_;
            return current_level_;
          }
        }
      }
    }
    current_level_ = -1;
    return -1;
  }

  // Following is from Snake project given code
  template<typename C>
  void MyApp::PrintText(const std::string &text, const C &color,
                        const ivec2 &size,
                        const vec2 &loc) {
    gl::color(color);

    auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

    const auto box_size = box.getSize();
    const vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = gl::Texture::create(surface);
    gl::draw(texture, locp);
  }

}  // namespace myapp
