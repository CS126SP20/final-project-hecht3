// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <BrickBreaker/ball.h>
#include <BrickBreaker/brick.h>
#include <BrickBreaker/platform.h>


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
  void RemoveBrick(int brick_id);
  void RemoveBall(int ball_id);
  void RemovePlatform(int platform_id);
  void UpdateBricks();
  void UpdateBalls();
  void UpdatePlatforms();
  bool CheckTopBottomCollision(BrickBreaker::ball ball, BrickBreaker::brick brick);
  bool CheckSideCollision(BrickBreaker::ball ball, BrickBreaker::brick brick);
  void SelectLevel(int level_number);
  void GenerateLevels();

  std::vector<BrickBreaker::ball> balls_;
  std::vector<BrickBreaker::brick> bricks_;
  std::vector<BrickBreaker::platform> platforms_;
  std::vector<std::vector<BrickBreaker::brick>> levels_;

  uint64_t time_;

  bool is_start_;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
