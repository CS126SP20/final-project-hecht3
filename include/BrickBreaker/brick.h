//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

#include <cinder/app/App.h>

namespace BrickBreaker {
  class brick {
  public:
    const double speed_ = 0.0;
    cinder::vec2 loc_;
    int health_;

    brick(cinder::vec2 location);
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_BLOCK_H
