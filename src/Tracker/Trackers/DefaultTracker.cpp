#include "Tracker/Trackers/DefaultTracker.hpp"

// Create a params object with defaults for given detector.
// Parameters are changed after creation.

DefaultTrackerParams::DefaultTrackerParams()
{
  config_();
}

void DefaultTrackerParams::config_()
{
  win_size = cv::Size(21,21);
  term_criteria = cv::TermCriteria(
      cv::TermCriteria::COUNT|cv::TermCriteria::EPS, 
      30, 
      0.01);
  flags = 0;
  min_eig_threshold = 0.0001;
}

/*
 * This is the default (reference) implementation of a feature tracker.
 * It uses sparse optical flow to track features into the next frame.
 */

DefaultTracker::DefaultTracker() 
{
  params_ = DefaultTrackerParams();
}

DefaultTracker::DefaultTracker(DefaultTrackerParams params) 
{
  params_ = params;
}

feature_map_t DefaultTracker::track_features(
    feature_map_t previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
{
  // Use PyrLK optical flow to propagate features

  // 1. Unroll features into array
  FeatureMapAsVectors previous_map = unpack_feature_map(previous_features);
  std::vector<cv::Point2f> previous_points = previous_map.coords;

  // 2. Track
  // TODO: Use subpixel optimization
  std::vector<cv::Point2f> next_points;
  std::vector<uint8_t> status;
  cv::Mat err;

  cv::calcOpticalFlowPyrLK(previous_image,
      next_image,
      previous_points,
      next_points,
      status, 
      err);

  // 3. Create new feature map of features that tracked successfully
  feature_map_t out_features;

  for (size_t i = 0; i < next_points.size(); i++) {
    // If this point passses (check err/status), connect to feature
    // in previous image
    cv::Point2f next_point = next_points.at(i);
    
    if (status.at(i) != 0 && is_in_frame_(next_point, next_image)) {
      // This point succeeded
      // TODO: Check that point hasn't left frame (because apparently 
      // that's a thing?

      Feature temp_feature = Feature(
          next_point,
          previous_map.descriptors.at(i),
          previous_map.ids.at(i),
          -1,
          previous_map.ages.at(i) + 1);

      out_features.insert({temp_feature.id, temp_feature});
    }
  }

  return out_features;

}

bool DefaultTracker::is_in_frame_(cv::Point2f point, cv::Mat image)
{
  int width = image.cols;
  int height = image.rows;
  
  float x = point.x;
  float y = point.y;

  return (y >= 0 && x >= 0 && y <= height && x <= width);
}
