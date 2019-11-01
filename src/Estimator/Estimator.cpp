#include "Estimator.hpp"
#include <iostream>

/*
 * EstimatorParams implementations
 */

// Public

// ------------
// Constructors
// ------------
EstimatorParams::EstimatorParams()
{
  config_();
}

// ---------
// Functions
// ---------

void EstimatorParams::config_()
{
  // TODO: Change this when automatic initialization is implemented.
  manual_initialization = true; 
}

// Private

// ---------
// Functions
// ---------

/*
 * Estimator implementations
 */

// Public

// ------------
// Constructors
// ------------
Estimator::Estimator()
{
  camera_ = nullptr;
  map_ = nullptr;
  pose_ = Pose();
}

Estimator::Estimator(
    std::shared_ptr<Camera> camera,
    std::shared_ptr<Map> map)
{
  camera_ = camera;
  map_ = map;
  pose_ = Pose();
}

// ---------
// Functions
// ---------


// Private
bool Estimator::manual_initialization_(
    Frame keyframe_1,
    Frame keyframe_2)
{
  /*
   * Process:
   * 1. Match features between frames
   * 2. Triangulate features
   * 3. Outlier rejection
   * 4. Populate map
   */

  return false;
}

std::vector<Landmark> Estimator::triangulate_points_(
    Pose pose_1,
    Pose pose_2,
    std::vector<Feature> features_1,
    std::vector<Feature> features_2)
{
  // Prep data to feed to cv::triangulatePoints
  cv::Mat K = camera_->get_intrinsic_params();
  cv::Mat T_1 = pose_1.get_transformation_matrix();
  cv::Mat T_2 = pose_2.get_transformation_matrix();



  std::vector<Landmark> out_vector;
  return out_vector;
}
