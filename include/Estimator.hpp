#ifndef ESTIMATOR_HPP_INCLUDE
#define ESTIMATOR_HPP_INCLUDE

#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For essential matrix/pnp/etc

#include "Camera.hpp" // Find a better way than to pass the camera around?
#include "Feature.hpp"
#include "Map.hpp"

class Estimator {
  public:
    Estimator();
    bool process_image(Camera cam, std::vector<Feature> features); // note: this actually only takes in the features
  private:
    // Estimator needs to compare features to previously triangulated points,
    // so needs to store a map
    Map map_;
    cv::Mat rvec, tvec; // Store current pose?
};

#endif
