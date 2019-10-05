#ifndef LANDMARK_HPP_INCLUDE
#define LANDMARK_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>

#include "Feature.hpp" // Features are measurments of landmarks

// This class represents 3D landmarks 

class Landmark {
  public:
    // Location relative to origin of map
    cv::Point3f location;

    // Keep track of all observations of this landmark
    std::vector<Feature> observations;
};

#endif
