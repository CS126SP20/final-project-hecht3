//
// Created by connell on 4/15/20.
//

#ifndef FINALPROJECT_PLATFORM_H
#define FINALPROJECT_PLATFORM_H

#include <cinder/app/App.h>

namespace BrickBreaker {
  class platform {
  public:
    double speed_;
    double size_;
    cinder::vec2 loc_;
    platform(cinder::vec2 location);
    void update();
    void draw();
  };
}


#endif //FINALPROJECT_PLATFORM_H
