// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <BrickBreaker/ball.h>
#include <BrickBreaker/brick.h>
#include <BrickBreaker/platform.h>
#include <BrickBreaker/powerup.h>

namespace myapp {
  using namespace cinder;

class MyApp : public app::App {

public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseMove(app::MouseEvent event) override;
  void mouseDrag(app::MouseEvent event) override;
  void mouseDown(app::MouseEvent event) override;
private:
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
  size_t GetLevelClicked(vec2 loc_clicked);

  template<typename C> void PrintText(const std::string &text, const C &color, const ivec2 &size,
                 const vec2 &loc);

  /** The data source for the brick collision sound. */
  DataSourceRef brick_sound;
  /** The data source for the platform collision sound. */
  DataSourceRef platform_sound;
  /** The data source for the wall collision sound. */
  DataSourceRef wall_sound;
  /** The image source for the background. */
  ImageSourceRef background;
  /** The texture object for the background. */
  gl::Texture2dRef background_texture;
  /** The current mouse location. */
  ivec2 current_mouse_loc_;
  /** The last mouse location. */
  ivec2 last_mouse_loc_;
  /** The last recorded platform location. */
  ivec2 last_platform_loc_;
  /** How fast the platform is moving. Is used to affect the ball's dir. */
  double platform_vel_;
  /** Vector of all of the balls that exist. */
  std::vector<BrickBreaker::ball> balls_;
  /** Vector of all of the bricks that exist. */
  std::vector<BrickBreaker::brick> bricks_;
  /** Vector of all of the platforms that exist. */
  std::vector<BrickBreaker::platform> platforms_;
  /** Vector of all of the powerups that exist. */
  std::vector<BrickBreaker::powerup> powerups_;
  /** Vector the levels. Gets loaded on start up through levels.cc. */
  std::vector<std::vector<BrickBreaker::brick>> levels_;
  /** The number of times the user has clicked since the app started. */
  int clicks_;
  /** The level the user clicked. */
  bool level_clicked_;
  /**
   * The number of times the user clicked previously. Is used to detect changes
   * in click count.
   */
  int last_click_count_;
  /** The pixel width of a menu level tile. */
  int menu_grid_width_;
  /** The pixel height of a menu level tile. */
  int menu_grid_height_;
  /** The number of platform powerups collected. */
  int platform_powerup_count_;
  /** The max level that is possible to load. */
  int max_level_;
  /** The level currently being played. */
  size_t current_level_;
  /** System time. */
  uint64_t time_;
  /** The amount of time the platform powerup has been applied, if at all. */
  uint64_t platform_powerup_time_;
  /** Whether or not it's the start of a level. */
  bool is_start_;
  /** Whether or not to play the platform sound. Is false at start of level. */
  bool play_platform_sound_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
