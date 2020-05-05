//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/brick.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  using namespace cinder;
  
  const int kPowerupProb = 90;
  const int kPowerupProbDenom = 100;
  ImageSourceRef img;
  gl::Texture2dRef mTexture;

  brick::brick(const vec2& location, int health) {
    loc_ = location;
    has_powerup_ = false;
    if (health < kMaxHealth) {
      health_ = health;
    } else {
      health_ = kDefaultBrickHealth;
    }
    if (rand() % kPowerupProbDenom > kPowerupProb) {
      has_powerup_ = true;
    }
    img = loadImage(app::loadAsset("brick.jpg"));
    mTexture = (gl::Texture::create(img));
  }

  void brick::update() {
    if (health_ > 0) {
      draw();
    }
  }

  void brick::draw() {
    mTexture->bind();
    gl::color(1, .6, 0);
    gl::setMatricesWindow(app::getWindowSize());
    Rectf rect = Rectf(loc_.x, loc_.y, loc_.x + kBrickWidth, loc_.y + kBrickHeight);
    //geom::RoundedRect rectR = geom::RoundedRect(rect, 5);
    //gl::drawSolidRoundedRect(rect, 5, 0, vec2(3, .5), vec2(.1, 7));
    gl::draw(mTexture, rect);
  }

  vec2 brick::GetUpperLeftCorner() {
    return loc_;
  }

  vec2 brick::GetUpperRightCorner() {
    return vec2(loc_.x + kBrickWidth, loc_.y);
  }

  vec2 brick::GetLowerLeftCorner() {
    return vec2(loc_.x, loc_.y + kBrickHeight);
  }

  vec2 brick::GetLowerRightCorner() {
    return vec2(loc_.x + kBrickWidth, loc_.y + kBrickHeight);
  }
}

