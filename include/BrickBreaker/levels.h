//
// Created by connell on 5/4/20.
//

#ifndef FINALPROJECT_LEVELS_H
#define FINALPROJECT_LEVELS_H

#include "brick.h"

namespace BrickBreaker {
  class levels {
  public:
    static std::vector<std::vector<BrickBreaker::brick>> GenerateLevels();
  };
}


#endif //FINALPROJECT_LEVELS_H
