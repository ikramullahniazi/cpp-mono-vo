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
    // Constructors
    Estimator();

    Estimator(std::shared_ptr<Camera> camera,
        std::shared_ptr<Map> map);

    // Deprecated
    Estimator(Camera camera, Map map);

    // Functions

    // Different behavior based on:
    // * If map is initialized
    // * If a new keyframe is needed
    Frame process_image(cv::Mat image,
        std::vector<Feature> features);

    // Data

  private:
    // Owned Objects
    std::shared_ptr<Map> map_;
    std::shared_ptr<Camera> camera_;

    // Functions
    void initialize_position_();
    void initialize_position_(cv::Mat r0,
        cv::Mat t0);
    
    // Data
    cv::Mat rotation_vector_;
    cv::Mat translation_vector_;
};

#endif
