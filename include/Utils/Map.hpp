#ifndef MAP_HPP_INCLUDE
#define MAP_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp> 

#include "Utils/Landmark.hpp"
#include "Utils/Frame.hpp"

// Manages the point cloud the estimator builds as it processes images

class Map {
  public:
    // Constructors
    Map();

    // Functions
    bool add_frame(Frame frame);
    // Getters
    std::vector<Landmark> get_landmarks();
    std::vector<Frame> get_keyframes();

    // Data
  private:
    // Owned Objects
    
    // Functions
    
    // Data
    std::vector<Landmark> landmarks_;
    std::vector<Frame> keyframes_;
};

#endif
