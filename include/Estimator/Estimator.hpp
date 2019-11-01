#ifndef ESTIMATOR_HPP_INCLUDE
#define ESTIMATOR_HPP_INCLUDE

#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For essential matrix/pnp/etc

#include "Utils/Camera.hpp" // Find a better way than to pass the camera around?
#include "Utils/Feature.hpp"
#include "Utils/Landmark.hpp"
#include "Utils/Map.hpp"
#include "Utils/Frame.hpp"
#include "Utils/Pose.hpp"

/*
 * This object takes in measurements in the form of features
 * tracked between images and produces state estimates in the
 * form of camera poses and landmark positions.
 */

class EstimatorParams {
  public:
    // ------------
    // Constructors
    // ------------
    EstimatorParams();

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    // Indicator for whether or not the estimator needs to run
    // an initialization process.
    bool manual_initialization;

  private:
    // -------------
    // Owned Objects
    // -------------

    // ---------
    // Functions
    // ---------

    /*
     * Initialize the default parameters
     */
    void config_();

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
    Pose pose_;

    EstimatorParams params_;

    // ---------
    // Functions
    // ---------
    bool manual_initialization_(
        Frame keyframe_1,
        Frame keyframe_2);
    std::vector<Landmark> triangulate_points_(
        Pose pose_1,
        Pose pose_2,
        std::vector<Feature> features_1,
        std::vector<Feature> features_2);
    // ----
    // Data
    // ----
};

#endif
