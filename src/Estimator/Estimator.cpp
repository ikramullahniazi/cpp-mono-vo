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
  // Defaults from:
  // https://docs.opencv.org/4.1.0/d9/d0c/group__calib3d.html#ga13f7e34de8fa516a686a56af1196247f
  method = cv::RANSAC;
  prob = 0.999;
  threshold = 1.0;
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
  is_initialized_ = false;
}

Estimator::Estimator(
    std::shared_ptr<Camera> camera,
    std::shared_ptr<Map> map,
    EstimatorParams params)
{
  camera_ = camera;
  map_ = map;
  params_ = params;
  is_initialized_ = false;
}

// ---------
// Functions
// ---------

Frame Estimator::process_frame(
    Frame current_frame)
{
  return current_frame;
}


bool Estimator::manual_initialization(
    Frame frame_1,
    Frame frame_2)
{
  /*
   * Frames come from feature tracker, so they don't have pose
   * estimates yet. 
   */

  // Use essential matrix to find pose estimate for frame 2.
  // Since we can only find up to scale poses anyway, we'll
  // use the generated unit vector in the direction of 
  // translation as the actual translation vector.
  
  cv::Mat K = camera_->K;
  std::vector<cv::Point2f> pts_1 = 
    unpack_feature_map(frame_1.features).coords;
  std::vector<cv::Point2f> pts_2 = 
    unpack_feature_map(frame_2.features).coords;

  cv::Mat E = cv::findEssentialMat(
      pts_1,
      pts_2,
      K,
      params_.method,
      params_.prob,
      params_.threshold,
      cv::noArray());

  cv::Mat R, t;

  bool success = false;
  is_initialized_ = success;
  return success;
}

landmark_map_t Estimator::triangulate_points_(
    Pose pose_1,
    Pose pose_2,
    feature_map_t features_1,
    feature_map_t features_2)
{
  // Prep data to feed to cv::triangulatePoints
  cv::Mat K = camera_->K;

  cv::Mat T_1 = form_transformation_matrix(
      pose_1.R,
      pose_1.t);
  cv::Mat P_1 = K * T_1(cv::Rect(0,0, 4,3));

  cv::Mat T_2 = form_transformation_matrix(
      pose_2.R,
      pose_2.t);
  cv::Mat P_2 = K * T_2(cv::Rect(0,0, 4,3));

  FeatureMapAsVectors map_vectors_1 = unpack_feature_map(
      features_1);
  FeatureMapAsVectors map_vectors_2 = unpack_feature_map(
      features_2);

  std::vector<cv::Point2f> points_1 = map_vectors_1.coords;
  std::vector<cv::Point2f> points_2 = map_vectors_2.coords;

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

  landmark_map_t out_map;

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
    int temp_id = features_1.at(i).id;

    Landmark temp_landmark = Landmark(
        temp_id,
        temp_point);
    out_map.insert({temp_id, temp_landmark});
  }
  return out_map;
}
