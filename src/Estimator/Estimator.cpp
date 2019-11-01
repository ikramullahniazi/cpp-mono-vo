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
  // HUGE ASSUMPTION: features_1[i] matches to features_2[i]

  // Prep data to feed to cv::triangulatePoints
  cv::Mat K = camera_->get_intrinsic_params();

  cv::Mat T_1 = pose_1.get_transformation_matrix();
  cv::Mat P_1 = K * T_1(cv::Rect(0,0, 4,3));

  cv::Mat T_2 = pose_2.get_transformation_matrix();
  cv::Mat P_2 = K * T_2(cv::Rect(0,0, 4,3));

  std::vector<cv::Point2f> points_1 = unpack_feature_vector(
      features_1);
  std::vector<cv::Point2f> points_2 = unpack_feature_vector(
      features_2);

  // 4xn vector of results
  cv::Mat points_4d;

  cv::triangulatePoints(
      P_1,
      P_2,
      points_1,
      points_2,
      points_4d);
  
  // Normalize homogeneous vector
  points_4d.row(0) /= points_4d.row(3);
  points_4d.row(1) /= points_4d.row(3);
  points_4d.row(2) /= points_4d.row(3);
  points_4d.row(3) /= points_4d.row(3);

  std::vector<Landmark> out_vector;

  // Now build vector of landmarks
  for (int i = 0; i < points_4d.cols; i++)
  {
    // Convert point in mat to Point3f
    cv::Mat temp_col = points_4d.col(i);
    cv::Point3f temp_point = cv::Point3f(
        temp_col.at<float>(0,0),
        temp_col.at<float>(1,0),
        temp_col.at<float>(2,0));
    // Assign landmark same ID as corresponding features
    int temp_id = points_1.at(i).id;
    // Add to out_vector
    Landmark temp_landmark = Landmark(
        temp_id,
        temp_point);
    out_vector.push_back(temp_landmark);
  }
  return out_vector;
}
