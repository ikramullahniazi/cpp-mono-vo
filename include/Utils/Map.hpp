#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp> 

#include "Landmark.hpp"

// Manages the point cloud the estimator builds as it processes images

class Map {
  public:
    Map();
    bool add_feature();
  private:
    std::vector<Landmark> landmarks_;
};

#endif
