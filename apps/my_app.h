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
  cinder::ivec2 last_platform_loc_;
  double platform_vel_;
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

 /**
  * Checks if a ball collided with the right/left side of a brick. Allows for a
  * pixel collision threshold in case the updating of the engine did not update
  * fast enough to catch the collision
  *
  * @param ball the ball that potentially collided
  * @param brick the brick that the ball potentially hit
  * @return whether the ball collided with the side of the brick
  */
  bool CheckSideCollision(BrickBreaker::ball &ball, BrickBreaker::brick &brick);

 /**
  * Checks if a ball collided with the top or bottom of a brick. Allows for a
  * pixel collision threshold in case the updating of the engine did not update
  * fast enough to catch the collision
  *
  * @param ball the ball that potentially collided
  * @param brick the brick that the ball potentially hit
  * @return whether the ball collided with the side of the brick
  */
  bool CheckTopBottomCollision(BrickBreaker::ball &ball, BrickBreaker::brick &brick);

 /**
  * Checks if a powerup was collected by the a platform. Allows for a
  * pixel collision threshold in case the updating of the engine did not update
  * fast enough to catch the collision
  *
  * @param powerup that was potentially collected
  * @param platform the platform that may have collected the powerup
  * @return whether the ball collided with the side of the brick
  */
  bool CheckPowerupCollection(BrickBreaker::powerup &powerup, BrickBreaker::platform &platform);

 /**
  * Is called at the beginning of the game so that the user can select a level
  * to play. Divides the screen into 25 squares, drawing lines to show the
  * squares.
  */
  void DrawMenuScreen();

 /**
  * Sets up a given level by creating one platform, one ball to be launched, and
  * bricks in the specified locations provided by the levels_ array.
  *
  * @param the level to load
  */
  void SelectLevel(size_t level_number);

 /**
  * Is called by DrawMenuScreen() to find out which level was clicked by the
  * user.
  *
  * @param loc_clicked the location clicked by the user
  * @return the level clicked
  */
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
  int max_level_;
  size_t current_level_;

  uint64_t time_;
  uint64_t platform_powerup_time_;

  bool is_start_;
  bool play_platform_sound_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
