#include "Detector/Detector.hpp"

/*
 * This is the default (reference) implementation of a feature detector.
 * It uses goodFeaturesToTrack to detect corners.
 */

Detector::Detector()
{
  // If no params are passed, use the default parameters
  params_ = DetectorParams();
  feature_counter_ = 0;
}

Detector::Detector(DetectorParams params)
{
  params_ = params;
}

std::vector<Feature> detect_features(const cv::Mat image, const std::vector<Feature> previous_features)
{
  std::vector<cv::Point2f> temp_output;
  std::vector<Feature> output;
  cv::goodFeaturesToTrack(image, temp_output,
      params_.max_count_,
      params_.quality_level_,
      params_.min_distance_,
      cv::Mat(),
      params_.block_size_,
      params_.gradient_size_,
      params_.use_harris_detector_,
      params_.k_);

  for (cv::Point2f pt : output) {
    // Convert cv::Point2f to Feature
    Feature temp_feature(pt);
    temp_feature.id = feature_counter_++;
    output.push_back(temp_feature);
  }

  return output;
}

std::vector<Feature> detect_features(const cv::Mat image, const std::vector<Feature> previous_features, const cv::Mat mask)
{

}


// Create a params object with defaults for given detector.
// Parameters can then be changed after creation.
// NOTE: Image height/width MUST be set before this can be used.
DetectorParams::DetectorParams()
{
  config_();
}

// Set default params
void DetectorParams::config_()
{
  max_count_ = 500;
  quality_level_ = 0.01;
  min_distance_ = 10;
  block_size_ = 3;
  gradient_size_ = 3;
  use_harris_detector_ = false;
  k_ = 0.04;
}

