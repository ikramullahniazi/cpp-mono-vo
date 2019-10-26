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

std::vector<Feature> Detector::detect_features(const cv::Mat image)
{
  std::vector<Feature> out = std::vector<Feature>();
  return out;
}

std::vector<Feature> Detector::detect_features(
    const cv::Mat image, 
    const int num_current_features,
    const cv::Mat mask)
{
  std::vector<Feature> out = std::vector<Feature>();
  return out;

}
