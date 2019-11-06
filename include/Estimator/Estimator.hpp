#ifndef ESTIMATOR_HPP_INCLUDE
#define ESTIMATOR_HPP_INCLUDE
#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For essential matrix/pnp/etc

#include "Utils/Camera.hpp"
#include "Utils/Feature.hpp"
#include "Utils/Landmark.hpp"
#include "Utils/Map.hpp"
#include "Utils/Frame.hpp"
#include "Utils/Pose.hpp"

/*
 * This object is part of the front end of a visual odometry system.
 * It takes in measurements in the form of features tracked 
 * between images and produces state estimates in the form of 
 * camera poses and landmark positions.
 *
 * For now, the poses produced will be relative to a reference
 * keyframe, so that all keyframes before that one can be 
 * optimized without complicating this module. 
 * Ideally, in the future a small map will be maintained here
 * that can be integrated piece by piece into the larger map.
 *
 * Functionality needed:
 *  * PnP localization relative to a previous keyframe
 *  * Triangulation of new points when a new keyframe is added
 *  * Passing of replaced keyframe to a map
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
    //
    // Params for findEssentialMat:
    int method;
    double prob;
    double threshold;

    // Params for solvePnPRansac
    bool use_extrinsic_guess;
    int iterations_count;
    float reprojection_error;
    double confidence;
    int solve_pnp_method;

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
        std::shared_ptr<Map> map,
        EstimatorParams params);

    // ---------
    // Functions
    // ---------

    // Different behavior based on:
    // * If map is initialized
    // * If a new keyframe is needed
    Frame process_frame(Frame frame);

    bool manual_initialization(
        Frame frame_1,
        Frame frame_2);
    
    Pose get_pose();

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------
    // Keep a pointer to the global map to make passing keyframes 
    // around easier.
    std::shared_ptr<Map> map_;
    std::shared_ptr<Camera> camera_;

    EstimatorParams params_;

    // ---------
    // Functions
    // ---------
    landmark_map_t triangulate_points_(
        Pose pose_1,
        Pose pose_2,
        feature_map_t features_1,
        feature_map_t features_2);
    // ----
    // Data
    // ----
    bool is_initialized_;
};

#endif
