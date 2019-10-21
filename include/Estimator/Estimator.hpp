#ifndef ESTIMATOR_HPP_INCLUDE
#define ESTIMATOR_HPP_INCLUDE

#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For essential matrix/pnp/etc

#include "Utils/Camera.hpp" // Find a better way than to pass the camera around?
#include "Utils/Feature.hpp"
#include "Utils/Map.hpp"
#include "Utils/Frame.hpp"

class Estimator {
  public:
    Estimator();

    Estimator(std::shared_ptr<Camera> camera);
    Estimator(Camera camera);

    // Main function for this object
    //
    // Fundamental purpose: Generate a frame that can be sent to the optimizer.
    //
    // Different behavior based on:
    // * If map is initialized
    // * If a new keyframe is needed
    Frame process_image(cv::Mat image,
        std::vector<Feature> features);

  private:
    // Estimator needs to compare features to previously triangulated points,
    // so needs to store a map
    
    // Owned Objects
    Map map_;
    std::shared_ptr<Camera> camera_;

    // Functions
    
    // Data
    cv::Mat rvec_, tvec_; // Store current pose?
};

#endif
