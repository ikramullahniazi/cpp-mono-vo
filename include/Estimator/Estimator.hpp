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

class EstimatorParams {
  public:
    // ------------
    // Constructors
    // ------------
    EstimatorParams();

    // ---------
    // Functions
    // ---------
    void config_();

    // ----
    // Data
    // ----
    // This determines whether or not the estimator will attempt to initialize
    // a map.
    bool manual_initialization;

  private:
    // -------------
    // Owned Objects
    // -------------
    
    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----

};


class Estimator {
  public:
    // ------------
    // Constructors
    // ------------
    Estimator();
    Estimator(std::shared_ptr<Camera> camera,
        std::shared_ptr<Map> map);
    // Deprecated
    Estimator(Camera camera, Map map);

    // ---------
    // Functions
    // ---------

    // Different behavior based on:
    // * If map is initialized
    // * If a new keyframe is needed
    Frame process_image(cv::Mat image,
        std::vector<Feature> features);

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------
    std::shared_ptr<Map> map_;
    std::shared_ptr<Camera> camera_;

    EstimatorParams params_;

    // ---------
    // Functions
    // ---------
    void initialize_position_();
    void initialize_position_(cv::Mat r0,
        cv::Mat t0);
    
    // ----
    // Data
    // ----
    cv::Mat rotation_vector_;
    cv::Mat translation_vector_;
};

// -----------------
// Utility Functions
// -----------------
// This function triangulates points between the given frames and creates
// a map from the resulting landmarks.
// This is exclusively to be used for simple manual initialization and 
// should be deprecated when a real initialization method is written.
std::shared_ptr<Map> create_map(Frame keyframe_1, Frame keyframe_2);

#endif
