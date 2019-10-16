#include "Detector/Detector.hpp"

// Create a params object with defaults for given detector.
// Parameters can then be changed after creation.
DetectorParams::DetectorParams()
{
  config_();
}

// Set default params
void DetectorParams::config_()
{

}


/*
 * This is the default (reference) implementation of a feature detector.
 * It uses goodFeaturesToTrack to detect corners.
 * TODO: Split this out from parent class
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

std::vector<Feature> Detector::detect_features(const cv::Mat image)
{
  std::vector<Feature> out;
  return out;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image, 
    const cv::Mat mask)
{
  std::vector<Feature> out;
  return out;

}
