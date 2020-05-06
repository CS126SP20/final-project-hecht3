// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <BrickBreaker/ball.h>
#include <BrickBreaker/brick.h>
#include <BrickBreaker/platform.h>
#include <BrickBreaker/powerup.h>

namespace myapp {

class MyApp : public cinder::app::App {

  cinder::ivec2 current_mouse_loc_;
  cinder::ivec2 last_mouse_loc_;
  double mouse_vel_;
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseMove(cinder::app::MouseEvent event) override;
  void mouseDrag(cinder::app::MouseEvent event) override;
  void mouseDown(cinder::app::MouseEvent event) override;
  void UpdateBricks();
  void UpdateBalls();
  void UpdatePlatforms();
  void UpdatePowerups();
  bool CheckTopBottomCollision(BrickBreaker::ball &ball, BrickBreaker::brick &brick);
  bool CheckSideCollision(BrickBreaker::ball &ball, BrickBreaker::brick &brick);
  bool CheckPowerupCollection(BrickBreaker::powerup &powerup, BrickBreaker::platform &platform);
  void DrawMenuScreen();
  void SelectLevel(size_t level_number);
  size_t GetLevelClicked(ci::vec2 loc_clicked);
  template<typename C> void PrintText(const std::string &text, const C &color, const cinder::ivec2 &size,
                 const cinder::vec2 &loc);

  std::vector<BrickBreaker::ball> balls_;
  std::vector<BrickBreaker::brick> bricks_;
  std::vector<BrickBreaker::platform> platforms_;
  std::vector<BrickBreaker::powerup> powerups_;
  std::vector<std::vector<BrickBreaker::brick>> levels_;
  int clicks_;
  bool level_clicked_;
  int last_click_count_;
  int menu_grid_width_;
  int menu_grid_height_;
  int platform_powerup_count_;
  size_t current_level_;

  uint64_t time_;
  uint64_t platform_powerup_time_;

  bool is_start_;
  bool play_platform_sound_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
