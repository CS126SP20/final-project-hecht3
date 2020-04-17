// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <BrickBreaker/ball.h>
#include <BrickBreaker/brick.h>
#include <BrickBreaker/platform.h>


namespace myapp {

class MyApp : public cinder::app::App {

  cinder::ivec2 mouse_move_;
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

  std::vector<BrickBreaker::ball> balls_;
  std::vector<BrickBreaker::brick> bricks_;
  std::vector<BrickBreaker::platform> platforms_;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
