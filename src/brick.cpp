//
// Created by connell on 4/15/20.
//

#include <BrickBreaker/brick.h>
#include <cinder/gl/gl.h>

namespace BrickBreaker {
  using namespace cinder;

  const int kPowerupProb = 90;
  const int kPowerupProbDenom = 100;
  const double kTwoThirds = .666;
  const double kOneThird = .333;
  ImageSourceRef img;
  gl::Texture2dRef full_health_brick_texture;
  gl::Texture2dRef two_thirds_health_brick_texture;
  gl::Texture2dRef one_third_health_brick_texture;

  brick::brick(const vec2 &location, int health) {
    loc_ = location;
    has_powerup_ = false;
    if (health < kMaxHealth) {
      health_ = health;
    } else {
      health_ = kDefaultBrickHealth;
    }
    full_health_ = health_;
    if (rand() % kPowerupProbDenom > kPowerupProb) {
      has_powerup_ = true;
    }
    img = loadImage(app::loadAsset("brick.jpg"));
    full_health_brick_texture = (gl::Texture::create(img));
    img = loadImage(app::loadAsset("brick_two_thirds_health.png"));
    two_thirds_health_brick_texture = (gl::Texture::create(img));
    img = loadImage(app::loadAsset("brick_one_third_health.png"));
    one_third_health_brick_texture = (gl::Texture::create(img));
  }

  void brick::update() {
    if (health_ > 0) {
      draw();
    }
  }

  void brick::draw() {
    if (full_health_ >= kMaxHealth * kOneThird) {
      gl::color(.6f, .1f, 0);
    } else if (full_health_ >= kMaxHealth * kTwoThirds) {
      gl::color(.8f, .1f, 0);
    } else {
      gl::color(1, .1f, 0);
    }
    gl::setMatricesWindow(app::getWindowSize());
    Rectf rect = Rectf(loc_.x, loc_.y, loc_.x + kBrickWidth,
                       loc_.y + kBrickHeight);
    if (health_ > full_health_ * kTwoThirds + 1) {
      full_health_brick_texture->bind();
      gl::draw(full_health_brick_texture, rect);
    } else if (health_ > full_health_ * kOneThird + 1) {
      two_thirds_health_brick_texture->bind();
      gl::draw(two_thirds_health_brick_texture, rect);
    } else {
      one_third_health_brick_texture->bind();
      gl::draw(one_third_health_brick_texture, rect);
    }
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

