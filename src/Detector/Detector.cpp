#include "Detector/Detector.hpp"

DetectorParams::DetectorParams()
{
  config_();
}

void DetectorParams::config_()
{

}

Detector::Detector()
{
  params_ = DetectorParams();
}

Detector::Detector(DetectorParams params)
{
  params_ = params;
}

feature_map_t Detector::detect_features(const cv::Mat image)
{
  feature_map_t out;
  return out;
}

feature_map_t Detector::detect_features(
    const cv::Mat image, 
    const int num_current_features,
    const cv::Mat mask)
{
  feature_map_t out;
  return out;

}
