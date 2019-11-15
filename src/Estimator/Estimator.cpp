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
  // Defaults from: https://docs.opencv.org/4.1.0/d9/d0c/group__calib3d.html#ga13f7e34de8fa516a686a56af1196247f
  method = cv::RANSAC;
  prob = 0.999;
  threshold = 1.0;


  // Defaults for PnP
  use_extrinsic_guess = false;
  iterations_count = 100;
  reprojection_error = 8.0;
  confidence = 0.99;
  solve_pnp_method = cv::SOLVEPNP_ITERATIVE;

  // What percentage of lost features causes new keyframe?
  keyframe_percent_threshold = 0.9;
  keyframe_distance_threshold = 10;
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

// Don't use this one!
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

  // TODO: Determine if keyframe or not

  // Localize
  Frame localized_frame = localize_pnp_(current_frame);
  localized_frame.is_processed = true;

  bool keyframe = keyframe_needed_(localized_frame);

  if (keyframe)
  {
    localized_frame.is_keyframe = true;

    std::pair<feature_map_t, feature_map_t> feature_matches = 
      match_feature_maps(
          reference_frame_.features,
          current_frame.features);

    landmark_map_t new_landmarks = triangulate_points_(
        reference_frame_.pose,
        localized_frame.pose,
        feature_matches.first,
        feature_matches.second);

    for (auto const& f : new_landmarks)
    {
      map_->insert_landmark(f.second);
    }

    reference_frame_ = localized_frame;
  }

  map_->insert_frame(localized_frame);

  return localized_frame;
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

  // Need to get all points seen in both frames
  std::pair<feature_map_t, feature_map_t> matched_points = 
    match_feature_maps(frame_1.features, frame_2.features);

  FeatureMapAsVectors feature_vectors_1 = unpack_feature_map(
      matched_points.first);

  FeatureMapAsVectors feature_vectors_2 = unpack_feature_map(
      matched_points.second);

  std::vector<cv::Point2f> pts_1 = feature_vectors_1.coords;
  std::vector<cv::Point2f> pts_2 = feature_vectors_2.coords;

  cv::Mat mask;

  // TODO: compute essential mat and homography, only try to reconstruct
  // if one is good enough
  cv::Mat E = cv::findEssentialMat(
      pts_1,
      pts_2,
      camera_->K,
      params_.method,
      params_.prob,
      params_.threshold,
      mask);

  cv::Mat R, rvec, t;

  // Note:
  // Avoid using recoverPose to triangulate points.
  // It gives SIGNIFICANTLY worse resulting landmarks than triangulatePoints
  // despite using the same (?) underlying functions.
  cv::recoverPose(
      E,
      pts_1,
      pts_2,
      camera_->K,
      R,
      t,
      mask);

  Pose pose_1 = Pose();
  Pose pose_2 = Pose(R, t);

  landmark_map_t landmarks = triangulate_points_(
      pose_1,
      pose_2,
      matched_points.first,
      matched_points.second);

  frame_1.pose = pose_1;
  frame_1.is_keyframe = true;
  frame_1.is_processed = true;

  frame_2.pose = pose_2;
  frame_2.is_keyframe = true;
  frame_2.is_processed = true;

  map_->insert_frame(frame_1);
  map_->insert_frame(frame_2);

  reference_frame_ = frame_2;

  for (auto const& f : landmarks)
  {
    map_->insert_landmark(f.second);
  }

  // TODO: some checks here
  bool success = true;
  is_initialized_ = success;
  return success;
}

// TODO: just take two frames as input
// TODO: this re-triangulates features that have already been seen, 
// maybe give the option to only triangulate new landmarks?
landmark_map_t Estimator::triangulate_points_(
    Pose pose_1,
    Pose pose_2,
    feature_map_t features_1,
    feature_map_t features_2)
{
  // Prep data to feed to cv::triangulatePoints
  cv::Mat K = camera_->K;
  cv::Size size = camera_->size;

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
  std::vector<int> ids = map_vectors_1.ids;

  // 4xn vector of results
  cv::Mat points_4d, projections_1, projections_2;

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

  // Project into each image to check
  projections_1 = P_1 * points_4d;
  projections_1.row(0) /= projections_1.row(2);
  projections_1.row(1) /= projections_1.row(2);
  projections_1.row(2) /= projections_1.row(2);

  projections_2 = P_2 * points_4d;
  projections_2.row(0) /= projections_2.row(2);
  projections_2.row(1) /= projections_2.row(2);
  projections_2.row(2) /= projections_2.row(2);

  landmark_map_t out_map;

  // Now build vector of landmarks
  for (int i = 0; i < points_4d.cols; i++)
  {
    // Check point is in reasonable place
    cv::Mat pixels_1 = projections_1.col(i);
    cv::Point2f point_1 = cv::Point2f(
        pixels_1.at<float>(0,0),
        pixels_1.at<float>(1,0));

    cv::Mat pixels_2 = projections_2.col(i);
    cv::Point2f point_2 = cv::Point2f(
        pixels_2.at<float>(0,0),
        pixels_2.at<float>(1,0));

    cv::Mat point_4d = points_4d.col(i);

    // Validate that point reprojects into both images
    bool is_valid = (
        point_1.x > 0 &&
        point_1.x < size.width &&
        point_1.y > 0 &&
        point_1.y < size.height &&
        point_2.x > 0 &&
        point_2.x < size.width &&
        point_2.y > 0 &&
        point_2.y < size.height);

    if (is_valid)
    {
      // Convert point in mat to Point3f
      cv::Point3f temp_point = cv::Point3f(
          point_4d.at<float>(0,0),
          point_4d.at<float>(1,0),
          point_4d.at<float>(2,0));
      // Assign landmark same ID as corresponding features
      int temp_id = ids.at(i);

      Landmark temp_landmark = Landmark(
          temp_id,
          temp_point);
      out_map.insert({temp_id, temp_landmark});
    }
  }
  return out_map;
}

bool Estimator::keyframe_needed_(
    Frame incoming_frame)
{
  // Determine how many features are lost between reference
  // and this frame
  std::pair<feature_map_t, feature_map_t> feature_matches = 
    match_feature_maps(
        reference_frame_.features,
        incoming_frame.features);

  auto matched_features = feature_matches.first;
  auto initial_features = reference_frame_.features;

  double num_matched = matched_features.size();
  double num_init = initial_features.size();

  double percent_kept = (num_matched / num_init);

  int keyframe_distance = incoming_frame.id - reference_frame_.id;

  return (percent_kept < params_.keyframe_percent_threshold) || (keyframe_distance > params_.keyframe_distance_threshold);

}

Frame Estimator::localize_pnp_(
    Frame incoming_frame)
{
  std::pair<feature_map_t, landmark_map_t> hypothesis_matches = 
    map_->filter_by_features(incoming_frame.features);

  FeatureMapAsVectors hypothesis_feature_vectors = 
    unpack_feature_map(hypothesis_matches.first);

  LandmarkMapAsVectors hypothesis_landmark_vectors = 
    unpack_landmark_map(hypothesis_matches.second);

  cv::Mat rvec, R, t, mask;

  // NOTE: Do not pass in distortion coefficients if points are already
  // undistorted.
  cv::solvePnPRansac(
      hypothesis_landmark_vectors.coords,
      hypothesis_feature_vectors.coords,
      camera_->K,
      camera_->D,
      rvec,
      t,
      params_.use_extrinsic_guess,
      params_.iterations_count,
      params_.reprojection_error,
      params_.confidence,
      mask,
      params_.solve_pnp_method);

  cv::Rodrigues(rvec, R);

  Pose current_pose = Pose(R, t);

  incoming_frame.pose = current_pose;

  return incoming_frame;
}

