#include "Tracker/Tracker.hpp"

// Create a params object with defaults for given detector.
// Parameters are changed after creation.

TrackerParams::TrackerParams()
{
  config_();
}

void TrackerParams::config_()
{

}

/*
 * This is the default (reference) implementation of a feature tracker.
 * It uses sparse optical flow to track features into the next frame.
 */

Tracker::Tracker() 
{
  params_ = TrackerParams();
}

Tracker::Tracker(TrackerParams params) 
{
  params_ = params;
}

std::vector<Feature> Tracker::track_features(
    const std::vector<Feature> previous_features,
    const cv::Mat previous_image,
    const cv::Mat next_image)
{
  std::vector<Feature> out_vec;
  return out_vec;
}

std::vector<cv::Point2f> Tracker::unpack_feature_vector_(std::vector<Feature> features) 
{
  std::vector<cv::Point2f> out_vec;
  return out_vec;
}
