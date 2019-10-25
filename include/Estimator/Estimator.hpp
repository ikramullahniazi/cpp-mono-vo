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
#include "Utils/Pose.hpp"

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
    Estimator(
        std::shared_ptr<Camera> camera,
        std::shared_ptr<Map> map);

    // ---------
    // Functions
    // ---------

    // Different behavior based on:
    // * If map is initialized
    // * If a new keyframe is needed
    Frame process_frame(Frame frame);
    
    Pose get_pose();

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
    void initialize_position_(
        cv::Mat r0,
        cv::Mat t0);
    void initialize_position_(
        Pose pose0);

    bool manual_initialization_(
        Frame keyframe_1,
        Frame keyframe_2);

    // ----
    // Data
    // ----
    Pose pose_;
};

#endif
